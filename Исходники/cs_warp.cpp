    static bool HandleWarpCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        char* arg1 = strtok((char*)args, " ");
        char* arg2 = strtok(NULL, " ");

        if (!arg1 || !arg2)
        return false;

        char dir = arg1[0];
        float value = float(atof(arg2));
        float x = player->GetPositionX();
        float y = player->GetPositionY();
        float z = player->GetPositionZ();
        float o = player->GetOrientation();
		 uint32 mapid = player->GetMapId();
        Map const* map = sMapMgr->CreateBaseMap(mapid);
        z = std::max(map->GetHeight(x, y, MAX_HEIGHT), map->GetWaterLevel(x, y));

    switch (dir)
    {
	case 'l': // left
        {
			x = x + cos(o+(M_PI/2))*value;
           y = y + sin(o+(M_PI/2))*value;

           player->TeleportTo(mapid, x, y, z, o);
        }
        break;
    case 'r': // right
        {
			x = x + cos(o-(M_PI/2))*value;
           y = y + sin(o-(M_PI/2))*value;

           player->TeleportTo(mapid, x, y, z, o);
        }
        break;
    case 'f': // forward
        {
			x = x + cosf(o)*value;
           y = y + sinf(o)*value;

           player->TeleportTo(mapid, x, y, z, o);
        }
        break;
    case 'u': // up
		{
           player->TeleportTo(mapid, x, y, z + value, o);
		}
        break;
	 case 'd': // down
		{
           player->TeleportTo(mapid, x, y, z - value, o);
		}
        break;
    case 'o': //orientation
        {
			o = Position::NormalizeOrientation((value * M_PI_F/180.0f)+ o);

           player->TeleportTo(mapid, x, y, z, o);
        }
        break;
    }
    return true;
  };