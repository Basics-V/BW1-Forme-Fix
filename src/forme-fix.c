// forme-fix.c
// Authors: MCMi460, FrostFalcon

#include "wbtypes.h"

#include "pml/poke_party.h"
#include "util.h"

// Recalculate stats, abilities, and moves
// when generating a wild Pokémon with a separate forme
void HandleFormeUpdate(PartyPkm* wildPkm, u32 forme) {
    PokeParty_ChangeForme(wildPkm, forme);
    PokeParty_SetDefaultMoves(wildPkm);
}
