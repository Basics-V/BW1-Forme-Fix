#include "wbtypes.h"

// Data structures
typedef struct PartyPkm PartyPkm;

extern void PokeParty_ChangeForme(PartyPkm*, u32);
extern void PokeParty_SetDefaultMoves(PartyPkm*);
extern void setChangedPkmSpecies(PartyPkm*, u32);
extern u32 PML_PersonalGetParamSingle(u32, u32, u32);
