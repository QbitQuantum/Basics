void WorldSession::HandleTaxiNextDestinationOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received CMSG_MOVE_SPLINE_DONE");

    MovementInfo movementInfo;                              // used only for proper packet read

    recv_data >> movementInfo;
    recv_data >> Unused<uint32>();                          // unk

    // in taxi flight packet received at the end of current path in far (multi-node) flight

    uint32 curDest = GetPlayer()->m_taxi.GetTaxiDestination();
    if (!curDest)
        return;

    TaxiNodesEntry const* curDestNode = sTaxiNodesStore.LookupEntry(curDest);

    // far teleport case
    if (curDestNode && curDestNode->map_id != GetPlayer()->GetMapId())
    {
        if (GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        {
            // short preparations to continue flight
            FlightPathMovementGenerator* flight = (FlightPathMovementGenerator*)(GetPlayer()->GetMotionMaster()->top());

            flight->SetCurrentNodeAfterTeleport();
            TaxiPathNodeEntry const& node = flight->GetPath()[flight->GetCurrentNode()];
            flight->SkipCurrentNode();

            GetPlayer()->TeleportTo(curDestNode->map_id, node.x, node.y, node.z, GetPlayer()->GetOrientation());
        }
        return;
    }

    uint32 destinationnode = GetPlayer()->m_taxi.NextTaxiDestination();
    if (destinationnode > 0)                              // if more destinations to go
    {
        // current source node for next destination
        uint32 sourcenode = GetPlayer()->m_taxi.GetTaxiSource();

        // Add to taximask middle hubs in taxicheat mode (to prevent having player with disabled taxicheat and not having back flight path)
        if (GetPlayer()->isTaxiCheater())
        {
            if (GetPlayer()->m_taxi.SetTaximaskNode(sourcenode))
            {
                WorldPacket data(SMSG_NEW_TAXI_PATH, 0);
                _player->GetSession()->SendPacket(&data);
            }
        }

        DEBUG_LOG("WORLD: Taxi has to go from %u to %u", sourcenode, destinationnode);

        uint16 MountId = sObjectMgr.GetTaxiMount(sourcenode, GetPlayer()->GetTeam());

        uint32 path, cost;
        sObjectMgr.GetTaxiPath(sourcenode, destinationnode, path, cost);

        if (path && MountId)
            SendDoFlight(MountId, path, 1);               // skip start fly node
        else
            GetPlayer()->m_taxi.ClearTaxiDestinations();    // clear problematic path and next

        return;
    }
    else
    {
        GetPlayer()->m_taxi.ClearTaxiDestinations();        // not destinations, clear source node

         // has taxi flight just finished reset fall information to avoid receiving fall damage
        GetPlayer()->SetFallInformation(0, movementInfo.GetPos()->GetPositionZ());
    }
    GetPlayer()->CleanupAfterTaxiFlight();
}