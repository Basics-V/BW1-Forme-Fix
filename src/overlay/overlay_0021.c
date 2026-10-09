#include "ARM9.h"
#include "overlay_0021.h"

// Rewritten parent forme handler to replace our stolen code
__attribute__((section(".shellosHandler"), target("thumb"), used))
void shellosHandler(DayCareParents* dayCareParents, EggPkm* eggPkm) {
    // Fetch the appropriate parent's species
    PartyPkm* parent = checkSecondPokemonDitto2(dayCareParents);
    unsigned int species = PartyPokemon_GetParam(parent, 5, NULL);

    // Inherit forme of the parent if Pokemon is not Rotom
    if (species != 479)
        eggPkm->Forme = PartyPokemon_GetParam(parent, 0x6F, NULL);
}

// Overwritten parent form inheritor function (donor code)
__attribute__((section(".basculinHandler"), target("thumb"), used))
void basculinHandler(PartyPkm* wildPkm, unsigned int forme) {
    PokeParty_ChangeForme(wildPkm, forme);
    PokeParty_SetDefaultMoves(wildPkm);
}

// Hook our forme fix function
__attribute__((naked, section(".FieldEncount_CreateWildPkm_0x3a"), target("thumb"), aligned(2)))
void FieldEncount_CreateWildPkm_0x3a(void) {
    __asm__ volatile (
        ".thumb\n\t"
        "MOV R0,R6\n\t"         // R0=>PartyPkm* wildPkm
        "LDRB R1,[R4,#0x5]\n\t" // R1=>u32 forme
        "BL basculinHandler\n\t"
        "NOP\n\t"
    );
}

// NOP the unused breeding calls
__attribute__((naked, section(".breeding_0x5c"), target("thumb"), aligned(2)))
void breeding_0x5c(void) {
    __asm__ volatile (
        ".thumb\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
        "NOP\n\t"
    );
}
