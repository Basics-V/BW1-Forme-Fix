#pragma once
#include "util.h"

// Data structures
typedef struct PartyPkm       PartyPkm;

// Hardcoded addresses
#define ADDR_PartyPokemon_GetParam     0x2017E1D
#define ADDR_PokeParty_ChangeForme     0x2017989
#define ADDR_PokeParty_SetDefaultMoves 0x2017FA8

// Inline assembly to match addresses w/ symbols
__asm__(
    ".global PartyPokemon_GetParam\n\t"
    ".type PartyPokemon_GetParam, %function\n\t"
    "PartyPokemon_GetParam = " STR(ADDR_PartyPokemon_GetParam) "\n\t"

    ".global PokeParty_ChangeForme\n\t"
    ".type PokeParty_ChangeForme, %function\n\t"
    "PokeParty_ChangeForme = " STR(ADDR_PokeParty_ChangeForme) "\n\t"

    ".global PokeParty_SetDefaultMoves\n\t"
    ".type PokeParty_SetDefaultMoves, %function\n\t"
    "PokeParty_SetDefaultMoves = " STR(ADDR_PokeParty_SetDefaultMoves) "\n\t"
);

extern unsigned int PartyPokemon_GetParam(PartyPkm*, unsigned int, void*);
extern void PokeParty_ChangeForme(PartyPkm*, unsigned int);
extern void PokeParty_SetDefaultMoves(PartyPkm*);
