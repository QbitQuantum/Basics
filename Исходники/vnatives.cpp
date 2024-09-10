static cell_t SlapPlayer(IPluginContext *pContext, const cell_t *params)
{
	static bool s_slap_supported = false;
	static bool s_slap_setup = false;
	static ICallWrapper *s_teleport = NULL;
	static int s_health_offs = 0;
	static int s_sound_count = 0;
	static int s_frag_offs = 0;

	if (!s_slap_setup)
	{
		int tries = 0;

		s_slap_setup = true;

		if (IsTeleportSupported())
		{
			tries++;
		}
		if (IsGetVelocitySupported())
		{
			tries++;
		}

		/* Setup health */
		if (g_pGameConf->GetOffset("m_iHealth", &s_health_offs) && s_health_offs)
		{
			tries++;
		}

		if (tries == 3)
		{
			s_slap_supported = true;

			const char *key;
			if ((key = g_pGameConf->GetKeyValue("SlapSoundCount")) != NULL)
			{
				s_sound_count = atoi(key);
			}
		}
	}

	if (!s_slap_supported)
	{
		return pContext->ThrowNativeError("This function is not supported on this mod");
	}

	/* First check if the client is valid */
	int client = params[1];
	IGamePlayer *player = playerhelpers->GetGamePlayer(client);
	if (!player)
	{
		return pContext->ThrowNativeError("Client %d is not valid", client);
	} else if (!player->IsInGame()) {
		return pContext->ThrowNativeError("Client %d is not in game", client);
	}

	edict_t *pEdict = player->GetEdict();
	CBaseEntity *pEntity = pEdict->GetUnknown()->GetBaseEntity();

	/* See if we should be taking away health */
	bool should_slay = false;
	if (params[2])
	{
#if SOURCE_ENGINE != SE_DARKMESSIAH
		int *health = (int *)((char *)pEntity + s_health_offs);

		if (*health - params[2] <= 0)
		{
			*health = 1;
			should_slay = true;
		} else {
			*health -= params[2];
		}
#else
		float *health = (float *)((char *)pEntity + s_health_offs);

		if (*health - (float)params[2] <= 0)
		{
			*health = 1.0f;
			should_slay = true;
		} else {
			*health -= (float)params[2];
		}
#endif
	}

	/* Teleport in a random direction - thank you, Mani!*/
	Vector velocity;
	GetVelocity(pEntity, &velocity, NULL);
	velocity.x += ((rand() % 180) + 50) * (((rand() % 2) == 1) ?  -1 : 1);
	velocity.y += ((rand() % 180) + 50) * (((rand() % 2) == 1) ?  -1 : 1);
	velocity.z += rand() % 200 + 100;
	Teleport(pEntity, NULL, NULL, &velocity);

	/* Play a random sound */
	if (params[3] && s_sound_count > 0)
	{
		char name[48];
		const char *sound_name;
		cell_t player_list[256], total_players = 0;
		int maxClients = playerhelpers->GetMaxClients();

		int r = (rand() % s_sound_count) + 1;
		snprintf(name, sizeof(name), "SlapSound%d", r);

		if ((sound_name = g_pGameConf->GetKeyValue(name)) != NULL)
		{
			IGamePlayer *other;
			for (int i=1; i<=maxClients; i++)
			{
				other = playerhelpers->GetGamePlayer(i);
				if (other->IsInGame())
				{
					player_list[total_players++] = i;
				}
			}

			const Vector & pos = pEdict->GetCollideable()->GetCollisionOrigin();
			CellRecipientFilter rf;
			rf.SetToReliable(true);
			rf.Initialize(player_list, total_players);
			engsound->EmitSound(rf, client, CHAN_AUTO, sound_name, VOL_NORM, ATTN_NORM, 0, PITCH_NORM, &pos);
		}
	}

	if (!s_frag_offs)
	{
		const char *frag_prop = g_pGameConf->GetKeyValue("m_iFrags");
		if (frag_prop)
		{
			datamap_t *pMap = gamehelpers->GetDataMap(pEntity);
			typedescription_t *pType = gamehelpers->FindInDataMap(pMap, frag_prop);
			if (pType != NULL)
			{
				s_frag_offs = pType->fieldOffset[TD_OFFSET_NORMAL];
			}
		}
		if (!s_frag_offs)
		{
			s_frag_offs = -1;
		}
	}

	int old_frags = 0;
	if (s_frag_offs > 0)
	{
		old_frags = *(int *)((char *)pEntity + s_frag_offs);
	}
	
	/* Force suicide */
	if (should_slay)
	{
		pluginhelpers->ClientCommand(pEdict, "kill\n");
	}

	if (s_frag_offs > 0)
	{
		*(int *)((char *)pEntity + s_frag_offs) = old_frags;
	}

	return 1;
}