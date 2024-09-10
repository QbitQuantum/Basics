void CMapManager::SendMapInformation ( CPlayer& Player )
{
    CTimeUsMarker < 20 > marker;
    marker.Set ( "Start" );

    // Start an entity list packet
    CEntityAddPacket EntityPacket;    

    // Add the dummys to the packet
    list < CDummy* > ::const_iterator iterDummys = m_pGroups->IterBegin ();
    for ( ; iterDummys != m_pGroups->IterEnd () ; iterDummys++ )
    {
        CDummy* pDummy = *iterDummys;
        if ( pDummy != m_pRootElement )
        {
            EntityPacket.Add ( pDummy );
        }
    }

    marker.Set ( "Dummys" );

    // Add the objects to the packet
    CObjectListType::const_iterator iterObjects = m_pObjectManager->IterBegin ();
    for ( ; iterObjects != m_pObjectManager->IterEnd (); iterObjects++ )
    {
        EntityPacket.Add ( *iterObjects );
    }

    marker.Set ( "Objects" );

    // Add the pickups to the packet
    list < CPickup* > ::const_iterator iterPickups = m_pPickupManager->IterBegin ();
    for ( ; iterPickups != m_pPickupManager->IterEnd (); iterPickups++ )
    {
        EntityPacket.Add ( *iterPickups );
    }

    marker.Set ( "Pickups" );

    // Add the vehicles to the packet
    list < CVehicle* > ::const_iterator iterVehicles = m_pVehicleManager->IterBegin ();
    for ( ; iterVehicles != m_pVehicleManager->IterEnd (); iterVehicles++ )
    {
        EntityPacket.Add ( *iterVehicles );
    }

    marker.Set ( "Vehicles" );

    // Add the teams to the packet
    list < CTeam* > ::const_iterator iterTeams = m_pTeamManager->IterBegin ();
    for ( ; iterTeams != m_pTeamManager->IterEnd (); iterTeams++ )
    {
        EntityPacket.Add ( *iterTeams );
    }

    marker.Set ( "Teams" );

    // Add the peds to the packet
    list < CPed* > ::const_iterator iterPeds = m_pPedManager->IterBegin ();
    for ( ; iterPeds != m_pPedManager->IterEnd (); iterPeds++ )
    {
        EntityPacket.Add ( *iterPeds );
    }

    marker.Set ( "Peds" );

    // Add the colshapes to the packet
    vector < CColShape* > ::const_iterator iterColShapes = m_pColManager->IterBegin ();
    for ( ; iterColShapes != m_pColManager->IterEnd (); iterColShapes++ )
    {
        CColShape * pColShape = *iterColShapes;
        if ( !pColShape->IsPartnered () )
        {
            EntityPacket.Add ( *iterColShapes );
        }
    }

    marker.Set ( "ColShapes" );

    // Add the water polys to the packet
    CWaterManager* pWaterManager = g_pGame->GetWaterManager ();
    list < CWater* > ::const_iterator iterWater = pWaterManager->IterBegin ();
    for ( ; iterWater != pWaterManager->IterEnd (); iterWater++ )
    {
        CWater* pWater = *iterWater;
        EntityPacket.Add ( pWater );
    }

    marker.Set ( "Water" );

    // Send it
    Player.Send ( EntityPacket );

    marker.Set ( "SendEntityPacket" );

    // Send per-player entities
    SendPerPlayerEntities ( Player );

    marker.Set ( "SendPerPlayerEntities" );

    // Send the trailer attachments
    CVehicle* pVehicle;
    CVehicle* pTowedVehicle;
    iterVehicles = m_pVehicleManager->IterBegin ();
    for ( ; iterVehicles != m_pVehicleManager->IterEnd (); iterVehicles++ )
    {
        pVehicle = *iterVehicles;
        pTowedVehicle = pVehicle->GetTowedVehicle ( );

        if ( pTowedVehicle )
        {
            CVehicleTrailerPacket AttachPacket ( pVehicle, pTowedVehicle, true );
            Player.Send ( AttachPacket );
        }
    }

    marker.Set ( "SendAttachPackets" );

    // Add debug info if wanted
    if ( CPerfStatDebugInfo::GetSingleton ()->IsActive ( "SendMapInformation" ) )
        CPerfStatDebugInfo::GetSingleton ()->AddLine ( "SendMapInformation", marker.GetString () );
}