// fpm.c - fixed program module
// Authors: MCMi460, HelloOO7, PlatinumMaster

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
        // IRAO: 0x2213D40
        // IRBO: 0x2213D20
        // IRAI: 0x2213C40
        // Take the greatest, IRAO, for multiregional support
        // 0x2213D40 + MODULE_SIZE = NEW_HEAP_START
        ".word " STR(0x2213D40 + MODULE_SIZE)
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_g_OvlMax(void) {
    __asm__ volatile (
        ".word 0x7FFFFFFF"
    );
}
