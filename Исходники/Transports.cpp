// Return true, only if transport has correct position!
bool MOTransport::SetPosition(WorldLocation const& loc, bool teleport)
{
    // prevent crash when a bad coord is sent by the client
    if (!MaNGOS::IsValidMapCoord(loc.getX(), loc.getY(), loc.getZ(), loc.getO()))
    {
        DEBUG_FILTER_LOG(LOG_FILTER_TRANSPORT_MOVES, "Transport::SetPosition(%f, %f, %f, %f, %d) bad coordinates for transport %s!", loc.getX(), loc.getY(), loc.getZ(), loc.getO(), teleport, GetName());
        return false;
    }

    if (teleport || GetMapId() != loc.GetMapId())
    {
        Map* oldMap = GetMap();
        Map* newMap = sMapMgr.CreateMap(loc.GetMapId(), this);

        if (!newMap)
        {
            sLog.outError("Transport::SetPosition cannot create map %u for transport %s!", loc.GetMapId(), GetName());
            return false;
        }

        if (oldMap != newMap)
        {
            // Transport inserted in current map ActiveObjects list
            if (!GetTransportKit()->GetPassengers().empty())
            {
                DEBUG_FILTER_LOG(LOG_FILTER_TRANSPORT_MOVES,"Transport::SetPosition %s notify passengers (count " SIZEFMTD ") for change map from %u to %u",GetObjectGuid().GetString().c_str(), GetTransportKit()->GetPassengers().size(), GetPosition().GetMapId(), loc.GetMapId());
                GetTransportKit()->CallForAllPassengers(NotifyMapChangeBegin(oldMap, GetPosition(), loc));
            }

            oldMap->Remove((GameObject*)this, false);

            SkipUpdate(true);

            SetMap(newMap);

            Relocate(loc);
            SetLocationMapId(loc.GetMapId());
            SetLocationInstanceId(loc.GetInstanceId());

            newMap->Add((GameObject*)this);

            // Transport inserted in current map ActiveObjects list
            if (!GetTransportKit()->GetPassengers().empty())
            {
                DEBUG_FILTER_LOG(LOG_FILTER_TRANSPORT_MOVES,"Transport::SetPosition %s notify passengers (count " SIZEFMTD ") for finished change map to %u",GetObjectGuid().GetString().c_str(), GetTransportKit()->GetPassengers().size(), loc.GetMapId());
                GetTransportKit()->CallForAllPassengers(NotifyMapChangeEnd(newMap,loc));
            }

            DEBUG_FILTER_LOG(LOG_FILTER_TRANSPORT_MOVES, "Transport::SetPosition %s teleported to (%f, %f, %f, %f)", GetObjectGuid().GetString().c_str(), loc.x, loc.y, loc.z, loc.orientation);
            return true;
        }
        else if (!(GetPosition() == loc))
            GetMap()->Relocation((GameObject*)this, loc);
    }
    else if (!(GetPosition() == loc))
        GetMap()->Relocation((GameObject*)this, loc);


    return false;
}