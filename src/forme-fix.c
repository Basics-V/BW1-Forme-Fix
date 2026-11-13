// forme-fix.c
// Authors: MCMi460, FrostFalcon, hzla

#include "wbtypes.h"

#include "pml/poke_party.h"
#include "util.h"

// Recalculate stats, abilities, and moves
// when generating a wild Pokémon with a separate forme
void HandleFormeUpdate(PartyPkm* wildPkm, u32 forme) {
    PokeParty_ChangeForme(wildPkm, forme);
    PokeParty_SetDefaultMoves(wildPkm);
}

// Set the correct next forme in evolution
// Credits: hzla
void HandleFormeEvolution(PartyPkm* partyPkm, u32 personalID) {
    if (personalID < 649) {
        setChangedPkmSpecies(partyPkm, personalID);
        return;
    }

    for (u32 species = 1; species <= 649; species++) {
        u32 formeCnt = PML_PersonalGetParamSingle(species, 0, 0x20);
        if (formeCnt == 1 || formeCnt > 31) continue;
        u32 firstForme = PML_PersonalGetParamSingle(species, 0, 0x1e);
        if (firstForme == 0) continue;

        u32 offset = personalID - firstForme;
        if (personalID >= firstForme && offset < formeCnt - 1) {
            PokeParty_ChangeForme(partyPkm, 0);
            setChangedPkmSpecies(partyPkm, species);
            PokeParty_ChangeForme(partyPkm, offset + 1);
            return;
        }
    }
    setChangedPkmSpecies(partyPkm, personalID);
}
