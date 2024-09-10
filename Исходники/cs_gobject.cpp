    //move selected object
    static bool HandleGameObjectMoveCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_guid|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        ObjectGuid::LowType guidLow = strtoull(id, nullptr, 10);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* toX = strtok(NULL, " ");
        char* toY = strtok(NULL, " ");
        char* toZ = strtok(NULL, " ");

        float x, y, z;
        if (!toX)
        {
            Player* player = handler->GetSession()->GetPlayer();
            player->GetPosition(x, y, z);
        }
        else
        {
            if (!toY || !toZ)
                return false;

            x = (float)atof(toX);
            y = (float)atof(toY);
            z = (float)atof(toZ);

            if (!MapManager::IsValidMapCoord(object->GetMapId(), x, y, z))
            {
                handler->PSendSysMessage(LANG_INVALID_TARGET_COORD, x, y, object->GetMapId());
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        object->DestroyForNearbyPlayers();
        object->RelocateStationaryPosition(x, y, z, object->GetOrientation());
        object->GetMap()->GameObjectRelocation(object, x, y, z, object->GetOrientation());

        object->SaveToDB();

        handler->PSendSysMessage(LANG_COMMAND_MOVEOBJMESSAGE, object->GetSpawnId(), object->GetGOInfo()->name.c_str(), object->GetGUID().ToString().c_str());

        return true;
    }