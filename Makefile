ROM_CODE := IRBO
PROJECT  := Forme-Fix

vfs_dir     := hooks
ovl_dir     := $(vfs_dir)/overlay
fpm_dir     := src
incl_dir    := include
build_dir   := build
linker_dir  := linker
obj_dir     := $(build_dir)/hooks
code_dir    := $(build_dir)/code
link_dir    := $(build_dir)/linker
unpack_dir  := $(build_dir)/$(ROM_CODE)
build_data  := $(build_dir)/data
tools_dir   := tools
pmc_dir     := esdb
data_dir    := data

srcs = $(wildcard $(vfs_dir)/*.c) $(wildcard $(ovl_dir)/*.c)
objs = $(addprefix $(obj_dir)/, $(notdir $(srcs:.c=.o)))
elfs = $(objs:.o=.elf)
lnks = $(link_dir)/hooks.ld
hdrs = $(wildcard $(incl_dir)/*.h) $(wildcard $(incl_dir)/overlay/*.h)
esdb = $(pmc_dir)/$(ROM_CODE).yml
y9   = $(data_dir)/y9.json

fsrcs = $(wildcard $(fpm_dir)/*.c) $(wildcard $(fpm_dir)/*.cpp)
fobjs = $(addprefix $(code_dir)/, $(notdir $(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(fsrcs)))))
felf  = $(code_dir)/fpm.elf
fsym  = $(felf:.elf=.sym)

fpm_ld = $(linker_dir)/fpm.ld

prefix_regex := FULL_COPY_[A-Za-z0-9_]+(_0x[0-9a-fA-F]+)?
hooks         = $(shell grep -E -o '$(prefix_regex)' $(srcs) | sort -u)

source = $(ROM_CODE).nds
target = $(build_dir)/$(ROM_CODE)_$(PROJECT).nds

nitro_project = $(unpack_dir)/$(ROM_CODE).json
fpm_bin       = $(unpack_dir)/overlay/main_00ED.bin

gcc     = arm-none-eabi-gcc
ld      = arm-none-eabi-ld
as      = arm-none-eabi-as
objcopy = arm-none-eabi-objcopy
objdump = arm-none-eabi-objdump
python  = python3
vpython = $(venv_dir)/bin/$(python)
ntrpck  = nitropacker

y9_tool   := $(tools_dir)/y9.py
nitro_y9  := $(tools_dir)/nitro_y9.py
esdb_tool := $(tools_dir)/esdb.py

venv_dir = $(build_dir)/venv
pyreqs   = $(tools_dir)/requirements.txt

c_flags  := -mthumb -march=armv5t -nostdlib -ffunction-sections -O2 $(addprefix -I, $(dir $(hdrs))) -Wa,-W
ld_flags := 
as_flags := 

vpath %.c   $(vfs_dir)
vpath %.c   $(ovl_dir)
vpath %.c   $(fpm_dir)
vpath %.cpp $(fpm_dir)

all: unpack $(target) repack clean_pack

unpack:
	@ echo "[<] Unpacking $(source)..."
	@ $(ntrpck) unpack -r $(source) -o $(unpack_dir)/ -p $(ROM_CODE) -d

repack:
	@ echo "[>] Packing $(target)..."
	@ $(ntrpck) pack -r $(target) -p $(nitro_project) -c

clean_pack:
	@ echo "[-] Cleaning up $(unpack_dir)..."
	@ rm -rf $(unpack_dir)

$(venv_dir):
	@ mkdir -p $@
	@ echo "[#] Creating Python virtual environment..."
	@ $(python) -m venv $(venv_dir)
	@ echo "[^] Installing requirements..."
	@ $(vpython) -m pip install -r $(pyreqs) > /dev/null

merge_y9s:
	@ echo "[%] Merging y9s..."
	@ $(vpython) $(nitro_y9) $(nitro_project) $(y9)

.PRECIOUS: $(lnks)
$(link_dir)/hooks.ld: $(hdrs) $(venv_dir) merge_y9s
	@ echo "[+] Generating $@..."
	@ mkdir -p $(dir $@)
	@ echo "SECTIONS {" > $@
	@ for hook in $(hooks); do \
		sym_ctx=$$($(vpython) $(esdb_tool) $(esdb) $$hook $(nitro_project)); \
		symb=$$(echo $$sym_ctx | cut -d " " -f1); \
		addr=$$(echo $$sym_ctx | cut -d " " -f2); \
		echo "	. = $$(( addr & -2 ));" >> $@; \
		echo "	.text.$$symb ALIGN(2) : { KEEP(*(.text.$$symb)) }" >> $@; \
	done
	@ echo "  /DISCARD/ : { *(.comment) *(.ARM.attributes) *(.note*) }" >> $@
	@ echo "}" >> $@

$(target): $(y9) $(felf) $(elfs) $(venv_dir)
	@ mkdir -p $(dir $@)

$(obj_dir)/%.elf: $(obj_dir)/%.o $(lnks) $(obj_dir)/symbols.o $(fsym)
	@ echo "[-] Linking hook $<..."
	@ $(ld) $(ld_flags) -T $(link_dir)/hooks.ld $< $(obj_dir)/symbols.o -o $@ $(addprefix -R, $(fsym))

	@ if [ -n "$(obj_hooks)" ]; then \
		echo "[&] Patching $<..."; \
	fi

	@ for hook in $(obj_hooks); do \
		echo "    * $$hook"; \
		sym_ctx=$$($(vpython) $(esdb_tool) $(esdb) $$hook $(nitro_project)); \
		addr=$$(echo $$sym_ctx | cut -d " " -f2); \
		offs=$$(echo $$sym_ctx | cut -d " " -f3); \
		offs10=$$(printf "%d" "$$offs"); \
		offs10even=$$(( offs10 & -2 )); \
		$(objcopy) -O binary --only-section=.text.$$hook $@ $(@:.elf=.bin); \
		length=$$(stat -f%z $(@:.elf=.bin)); \
		case $$(basename "$@") in \
			main_*) location="$(unpack_dir)/overlay";; \
			*) location="$(unpack_dir)";; \
		esac; \
		dd if=$(@:.elf=.bin) of=$$location/$(notdir $(@:.elf=.bin)) bs=1 seek=$$offs10even conv=notrunc status=none; \
	done

$(obj_dir)/%.o: %.c $(hdrs)
	@ echo "[+] Compiling hook $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@
	@ $(eval obj_hooks := $(shell grep -E -o '$(prefix_regex)' $< | sort -u))

$(obj_dir)/symbols.o: $(esdb)
	@ echo "[?] Assembling symbol file..."
	@ mkdir -p $(@D)
	@ $(vpython) $(esdb_tool) $(esdb) > $(obj_dir)/symbols.s
	@ $(as) $(as_flags) $(obj_dir)/symbols.s -o $@

$(fsym): $(felf)
	@ $(objcopy) --extract-symbol $< $@

$(felf): $(fobjs) $(lnks) $(obj_dir)/symbols.o
	@ echo "[-] Linking FPM $@..."
	@ mkdir -p $(@D)
	@ $(ld) $(ld_flags) -T $(fpm_ld) $(fobjs) $(obj_dir)/symbols.o -o $@
	@ $(objcopy) -O binary $@ $(fpm_bin)

$(code_dir)/%.o: %.c $(hdrs)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

$(code_dir)/%.o: %.cpp $(hdrs)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

clean:
	rm -rf $(obj_dir) $(code_dir) $(link_dir) $(unpack_dir) $(target)

purge:
	rm -rf $(build_dir)

.PHONY: all clean purge
