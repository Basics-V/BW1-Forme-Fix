ROM_CODE := IRBO
PROJECT  := Forme-Fix

vfs_dir   := src
ovl_dir   := $(vfs_dir)/overlay
incl_dir  := include
build_dir := build
obj_dir   := $(build_dir)/code

srcs = $(wildcard $(vfs_dir)/*.c) $(wildcard $(ovl_dir)/*.c)
objs = $(addprefix $(obj_dir)/, $(notdir $(srcs:.c=.o)))
hdrs = $(wildcard $(incl_dir)/*.h) $(wildcard $(incl_dir)/overlay/*.c)

target = $(build_dir)/$(ROM_CODE)_$(PROJECT).elf

gcc     := arm-none-eabi-gcc
ld      := arm-none-eabi-ld
objdump := arm-none-eabi-objdump

lds := $(wildcard *.ld)

c_flags  := -mthumb -march=armv5t -nostdlib -O2 $(addprefix -I, $(dir $(hdrs)))
ld_flags := $(addprefix -T, $(lds))

vpath %.c $(vfs_dir)
vpath %.c $(ovl_dir)

all: $(target)

$(target): $(objs)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) $(ld_flags) -o $@ $^

$(obj_dir)/%.o: %.c $(hdrs)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -c $< -o $@

verify: all
	@ $(objdump) -d $(target)

clean:
	rm -rf $(build_dir)

.PHONY: all verify clean
