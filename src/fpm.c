// fpm.c - fixed program module
// Authors: MCMi460

#include "arm9.h"
#include "util.h"

__attribute__((target("thumb")))
void HandleFormeUpdate(PartyPkm* wildPkm, unsigned int forme) {
    PokeParty_ChangeForme(wildPkm, forme);
    PokeParty_SetDefaultMoves(wildPkm);
}
