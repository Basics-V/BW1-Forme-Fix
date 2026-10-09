#pragma once
#include "util.h"

#include "ARM9.h"

/* Struct declarations */
typedef struct DayCareParents DayCareParents;
typedef struct EggPkm         EggPkm;

/* Data type definitions */
struct DayCareParents {
    PartyPkm* Father;
    PartyPkm* Mother;
};
struct EggPkm {
    unsigned int Species;
    unsigned int Forme;
    // ... truncated definition
};

// Hardcoded addresses
#define ADDR_checkSecondPokemonDitto2 0x21C3C5D

// Inline assembly to match addresses w/ symbols
__asm__(
    ".global checkSecondPokemonDitto2\n\t"
    ".type checkSecondPokemonDitto2, %function\n\t"
    "checkSecondPokemonDitto2 = " STR(ADDR_checkSecondPokemonDitto2) "\n\t"
);

PartyPkm* checkSecondPokemonDitto2(DayCareParents*);

// Compiled/defined functions
void shellosHandler(DayCareParents*, EggPkm*);
void basculinHandler(PartyPkm*, unsigned int);
