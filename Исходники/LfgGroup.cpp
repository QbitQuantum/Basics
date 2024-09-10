void LfgGroup::TeleportPlayer(Player *plr, DungeonInfo *dungeonInfo, uint32 originalDungeonId, bool newPlr)
{
    if(newPlr)
    {
        plr->m_lookingForGroup.queuedDungeons.clear(); // must be before remove grom group
        if (Group *group = plr->GetGroup())
        {
            if (!group->isLfgGroup())
            {
                group->RemoveMember(plr->GetGUID(), 0);
                if (group->GetMembersCount() == 0)
                    group->Disband(true);
            }
            plr->SetGroup(NULL);
        }

        plr->UnbindInstance(dungeonInfo->start_map, m_dungeonInfo->isHeroic() ? DUNGEON_DIFFICULTY_HEROIC : DUNGEON_DIFFICULTY_NORMAL);
        plr->ResetInstances(INSTANCE_RESET_GROUP_JOIN,false);
        plr->ResetInstances(INSTANCE_RESET_GROUP_JOIN,true);
        plr->ResetInstances(INSTANCE_RESET_ALL, true);
        plr->ResetInstances(INSTANCE_RESET_ALL, false);

        if (plr->getLevel() >= LEVELREQUIREMENT_HEROIC)
        {
            if (plr->GetDungeonDifficulty() != GetDungeonDifficulty())
                plr->SetDungeonDifficulty(GetDungeonDifficulty());
            if (plr->GetRaidDifficulty() != GetRaidDifficulty())
                plr->SetRaidDifficulty(GetRaidDifficulty());
        }
        plr->SetGroup(this, 0);
        plr->SetGroupInvite(NULL);

        uint32 taxi_start = 0;
        uint32 taxi_end = 0;
        uint32 mount_spell = 0;
        WorldLocation joinLoc;
        if (!plr->m_taxi.empty())
        {
           taxi_start = plr->m_taxi.GetTaxiSource();
           taxi_end = plr->m_taxi.GetTaxiDestination();
           joinLoc = WorldLocation(plr->GetMapId(), plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetOrientation());
        }
        else
        {
            // Mount spell id storing
            if (plr->IsMounted())
            {
                Unit::AuraList const& auras = plr->GetAurasByType(SPELL_AURA_MOUNTED);
                if (!auras.empty())
                    mount_spell = (*auras.begin())->GetId();
            }
            if(!mount_spell && plr->getClass() == CLASS_DRUID)
            {
                Unit::AuraList const& auras = plr->GetAurasByType(SPELL_AURA_MOD_SHAPESHIFT);
                if (!auras.empty())
                    mount_spell = (*auras.begin())->GetId();
            }
            //Nearest graveyard if in dungeon
            if (plr->GetMap()->IsDungeon())
            {
                if (const WorldSafeLocsEntry* entry = sObjectMgr.GetClosestGraveYard(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetMapId(), plr->GetTeam()))
                    joinLoc = WorldLocation(entry->map_id, entry->x, entry->y, entry->z, 0.f);
                else
                    joinLoc = plr->GetLocation();
            }
            else
                joinLoc = plr->GetLocation();
        }
        CharacterDatabase.PExecute("DELETE FROM group_member WHERE memberGuid='%u'", GUID_LOPART(plr->GetGUID()));
        CharacterDatabase.PExecute("INSERT INTO group_member(groupId,memberGuid,assistant,subgroup,lfg_join_x,lfg_join_y,lfg_join_z,lfg_join_o,lfg_join_map,taxi_start,taxi_end,mount_spell) "
            "VALUES('%u','%u','%u','%u','%f','%f','%f','%f','%u','%u','%u','%u')",
            m_Id, GUID_LOPART(plr->GetGUID()), 0, 1, joinLoc.x(), joinLoc.y(), joinLoc.z(), joinLoc.orientation, joinLoc.mapid, taxi_start, taxi_end, mount_spell);

        //Set info to player
        plr->m_lookingForGroup.joinLoc = joinLoc;
        plr->m_lookingForGroup.taxi_start = taxi_start;
        plr->m_lookingForGroup.taxi_end = taxi_end;
        plr->m_lookingForGroup.mount_spell = mount_spell;
        plr->m_lookingForGroup.roles = GetPlayerRole(plr->GetGUID());

        if (IsRandom())
            plr->CastSpell(plr, LFG_RANDOM_COOLDOWN, true);
    }

    // resurrect the player
    if (!plr->isAlive())
    {
        plr->ResurrectPlayer(1.0f);
        plr->SpawnCorpseBones();
    }
    // stop taxi flight at port
    if (plr->isInFlight())
    {
        plr->GetMotionMaster()->MovementExpired(false);
        plr->GetMotionMaster()->Clear(false, true);
        plr->GetMotionMaster()->MoveIdle();
        plr->m_taxi.ClearTaxiDestinations();
    }
    
    plr->ScheduleDelayedOperation(DELAYED_LFG_ENTER_DUNGEON);
    plr->ScheduleDelayedOperation(DELAYED_SAVE_PLAYER);
    plr->ScheduleDelayedOperation(DELAYED_LFG_CLEAR_LOCKS);

    if(IsMixed())
    {
        plr->m_lookingForGroup.SetMixedDungeon(dungeonInfo->start_map);
        if(newPlr)
            plr->setFaction(sWorld.getConfig(CONFIG_UINT32_TEAM_BG_FACTION_BLUE));
    }

    if (IsInDungeon())
    {
        if(newPlr)
        {
            for (GroupReference *itr = GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player *player = itr->getSource();
                if (!player  || player->GetMapId() != GetDungeonInfo()->map)
                    continue;

                plr->TeleportTo(player->GetLocation());
                return;
            }
        }
        plr->TeleportTo(dungeonInfo->start_map, dungeonInfo->start_x, dungeonInfo->start_y, dungeonInfo->start_z, dungeonInfo->start_o);
        return;
    }

    //Must re-add player to reset id...
    Map *map = plr->GetMap();
    if(map->GetId() == dungeonInfo->start_map)
    {
        map->Remove(plr, false);
        map->Add(plr);
    }
    
    plr->TeleportTo(dungeonInfo->start_map, dungeonInfo->start_x,
        dungeonInfo->start_y, dungeonInfo->start_z, dungeonInfo->start_o);
}