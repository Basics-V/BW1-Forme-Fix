// Hook our evolution fix function
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_EvolutionProcUpdate_0x320(void) {
    __asm__ volatile (
        "BL HandleFormeEvolution\n\t"
    );
}
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_EvolutionDisplayLoad_0x52(void) {
    __asm__ volatile (
        "BL HandleFormeEvolution\n\t"
    );
}
