#include "arm9.h"
#include "fpm.h"
#include "util.h"

// PMC/Interface/PMC_AsmInterface.s
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_bwInjectBootCode(void) {
    __asm__ volatile (
        "PUSH {LR}\n\t"
        "BL GFLAppInit\n\t"
        "MOVS R0, #0\n\t"
        "LDR R1, OVL_237\n\t"
        "BL sys_load_overlay\n\t"
        "POP {PC}\n\t"

        "OVL_237: .word 237\n\t"
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_main_0x6(void) {
    __asm__ volatile (
        "BL bwInjectBootCode\n\t"
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_GetUserMemRegionDefaultStart_0xB0(void) {
    __asm__ volatile (
        // 0x2213D20 + 0x8000 = 0x221BD20
        ".word " STR(0x2213D20 + MODULE_SIZE)
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_g_OvlMax(void) {
    __asm__ volatile (
        ".word 0x7FFFFFFF"
    );
}
