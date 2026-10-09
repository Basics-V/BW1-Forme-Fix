#pragma once
#include "util.h"

#include "ARM9.h"

/* Struct declarations */
typedef struct DayCareParents DayCareParents;

/* Data type definitions */
struct DayCareParents {
    PartyPkm* Father;
    PartyPkm* Mother;
};

// Compiled/defined functions
void shellosHandler(DayCareParents*, void*);
void basculinHandler(PartyPkm*, unsigned int);
