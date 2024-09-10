void WorldSession::BuildPartyMemberStatsChangedPacket(Player* player, WorldPacket& data)
{
    uint32 mask = player->GetGroupUpdateFlag();

    if (mask & GROUP_UPDATE_FLAG_POWER_TYPE)                // if update power type, update current/max power also
        mask |= (GROUP_UPDATE_FLAG_CUR_POWER | GROUP_UPDATE_FLAG_MAX_POWER);

    if (mask & GROUP_UPDATE_FLAG_PET_POWER_TYPE)            // same for pets
        mask |= (GROUP_UPDATE_FLAG_PET_CUR_POWER | GROUP_UPDATE_FLAG_PET_MAX_POWER);

    uint32 byteCount = 0;
    for (int i = 1; i < GROUP_UPDATE_FLAGS_COUNT; ++i)
        if (mask & (1 << i))
            byteCount += GroupUpdateLength[i];

    data.Initialize(SMSG_PARTY_MEMBER_STATS, 8 + 4 + byteCount);
    data << player->GetPackGUID();
    data << uint32(mask);

    if (mask & GROUP_UPDATE_FLAG_STATUS)
        data << uint16(GetGroupMemberStatus(player));

    if (mask & GROUP_UPDATE_FLAG_CUR_HP)
        data << uint32(player->GetHealth());

    if (mask & GROUP_UPDATE_FLAG_MAX_HP)
        data << uint32(player->GetMaxHealth());

    Powers powerType = player->GetPowerType();
    if (mask & GROUP_UPDATE_FLAG_POWER_TYPE)
        data << uint8(powerType);

    if (mask & GROUP_UPDATE_FLAG_CUR_POWER)
        data << uint16(player->GetPower(powerType));

    if (mask & GROUP_UPDATE_FLAG_MAX_POWER)
        data << uint16(player->GetMaxPower(powerType));

    if (mask & GROUP_UPDATE_FLAG_LEVEL)
        data << uint16(player->getLevel());

    if (mask & GROUP_UPDATE_FLAG_ZONE)
        data << uint16(player->GetZoneId());

    if (mask & GROUP_UPDATE_FLAG_POSITION)
        data << uint16(player->GetPositionX()) << uint16(player->GetPositionY());

    if (mask & GROUP_UPDATE_FLAG_AURAS)
    {
        const uint64& auramask = player->GetAuraUpdateMask();
        data << uint64(auramask);
        for (uint32 i = 0; i < MAX_AURAS; ++i)
        {
            if (auramask & (uint64(1) << i))
            {
                data << uint32(player->GetVisibleAura(i));
                data << uint8(1);
            }
        }
    }

    Pet* pet = player->GetPet();
    if (mask & GROUP_UPDATE_FLAG_PET_GUID)
        data << (pet ? pet->GetObjectGuid() : ObjectGuid());

    if (mask & GROUP_UPDATE_FLAG_PET_NAME)
    {
        if (pet)
            data << pet->GetName();
        else
            data << uint8(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_MODEL_ID)
    {
        if (pet)
            data << uint16(pet->GetDisplayId());
        else
            data << uint16(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_CUR_HP)
    {
        if (pet)
            data << uint32(pet->GetHealth());
        else
            data << uint32(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_MAX_HP)
    {
        if (pet)
            data << uint32(pet->GetMaxHealth());
        else
            data << uint32(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_POWER_TYPE)
    {
        if (pet)
            data << uint8(pet->GetPowerType());
        else
            data << uint8(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_CUR_POWER)
    {
        if (pet)
            data << uint16(pet->GetPower(pet->GetPowerType()));
        else
            data << uint16(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_MAX_POWER)
    {
        if (pet)
            data << uint16(pet->GetMaxPower(pet->GetPowerType()));
        else
            data << uint16(0);
    }

    if (mask & GROUP_UPDATE_FLAG_PET_AURAS)
    {
        if (pet)
        {
            const uint64& auramask = pet->GetAuraUpdateMask();
            data << uint64(auramask);
            for (uint32 i = 0; i < MAX_AURAS; ++i)
            {
                if (auramask & (uint64(1) << i))
                {
                    data << uint32(pet->GetVisibleAura(i));
                    data << uint8(1);
                }
            }
        }
        else
            data << uint64(0);
    }

    if (mask & GROUP_UPDATE_FLAG_VEHICLE_SEAT)
    {
        if (player->GetTransportInfo())
            data << uint32(((Unit*)player->GetTransportInfo()->GetTransport())->GetVehicleInfo()->GetVehicleEntry()->m_seatID[player->GetTransportInfo()->GetTransportSeat()]);
        else
            data << uint32(0);
    }
}