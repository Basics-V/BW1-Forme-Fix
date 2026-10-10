#include "fpm.h"

// Hook our forme fix function
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FieldEncount_CreateWildPkm_0x3a(void) {
    __asm__ volatile (
        "MOV R0,R6\n\t"         // R0=>PartyPkm* wildPkm
        "LDRB R1,[R4,#0x5]\n\t" // R1=>u32 forme
        "BL HandleFormeUpdate\n\t"
        "NOP\n\t"
    );
}
