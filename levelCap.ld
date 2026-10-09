OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
    . = 0x21C3BD4;
    .shellosHandler : {
        *(.shellosHandler)
    }
    . = 0x21C3C30;
    .basculinHandler : {
        *(.basculinHandler)
    }
    . = 0x21A96F2;
    .FieldEncount_CreateWildPkm_0x3a : {
        *(.FieldEncount_CreateWildPkm_0x3a)
    }
    . = 0x21C3950;
    .breeding_0x5c : {
        *(.breeding_0x5c)
    }
}
