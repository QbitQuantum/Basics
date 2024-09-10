/*
================
rvEffect::Event_EarthQuake
================
*/
void rvEffect::Event_EarthQuake ( float requiresLOS ) {
    float quakeChance;

    if ( !spawnArgs.GetFloat("quakeChance", "0", quakeChance) ) {
        return;
    }

    if ( rvRandom::flrand(0, 1.0f) > quakeChance ) {
        // failed its activation roll
        return;
    }

    if ( requiresLOS ) {
        // if the player doesn't have line of sight to this fx, don't do anything
        trace_t		trace;
        idPlayer	*player = gameLocal.GetLocalPlayer();
        idVec3		viewOrigin;
        idMat3		viewAxis;

        player->GetViewPos(viewOrigin, viewAxis);
// RAVEN BEGIN
// ddynerman: multiple collision worlds
        gameLocal.TracePoint( this, trace, viewOrigin, GetPhysics()->GetOrigin(), MASK_OPAQUE, player );
// RAVEN END
        if (trace.fraction < 1.0f)
        {
            // something blocked LOS
            return;
        }
    }

    // activate this effect now
    ProcessEvent ( &EV_Activate, gameLocal.entities[ENTITYNUM_WORLD] );
}