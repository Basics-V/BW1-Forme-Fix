#pragma once
#include "util.h"

// Data structures
typedef struct PartyPkm       PartyPkm;

// Hardcoded addresses
#define ADDR_PokeParty_ChangeForme     0x2017989
#define ADDR_PokeParty_SetDefaultMoves 0x201D005

// Inline assembly to match addresses w/ symbols
__asm__(
    ".global PokeParty_ChangeForme\n\t"
    ".type PokeParty_ChangeForme, %function\n\t"
    "PokeParty_ChangeForme = " STR(ADDR_PokeParty_ChangeForme) "\n\t"

    ".global PokeParty_SetDefaultMoves\n\t"
    ".type PokeParty_SetDefaultMoves, %function\n\t"
    "PokeParty_SetDefaultMoves = " STR(ADDR_PokeParty_SetDefaultMoves) "\n\t"
);

extern void PokeParty_ChangeForme(PartyPkm*, unsigned int);
extern void PokeParty_SetDefaultMoves(PartyPkm*);
