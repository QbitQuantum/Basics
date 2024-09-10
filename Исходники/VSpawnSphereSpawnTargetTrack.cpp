//-----------------------------------------------------------------------------
// 
// VSpawnSphereSpawnTargetTrack::despawnTargets();
// 
// Despawn all of the objects spawned by this track.
// 
//-----------------------------------------------------------------------------
void VSpawnSphereSpawnTargetTrack::despawnTargets( void )
{
    while( mSpawnList.size() > 0 )
    {
        // Fetch the Last Object
        SimObject *object = mSpawnList.last();
        // Remove it.
        mSpawnList.popObject();

        // Delete the Object.
        object->deleteObject();
    }
}