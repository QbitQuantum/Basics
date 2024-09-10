void CObjectSync::StopSync ( CObject* pObject )
{
    // Tell the player that used to sync it
    CPlayer* pSyncer = pObject->GetSyncer ();
    pSyncer->Send ( CObjectStopSyncPacket ( pObject ) );

    // Unmark him as the syncing player
    pObject->SetSyncer ( NULL );

    // Call the onElementStopSync event
    CLuaArguments Arguments;
    Arguments.PushElement ( pSyncer );  // Old syncer
    pObject->CallEvent ( "onElementStopSync", Arguments );
}