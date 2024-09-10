static cell_t EmitSound(IPluginContext *pContext, const cell_t *params)
{
	cell_t *addr, *pl_addr;

	CellRecipientFilter crf;
	pContext->LocalToPhysAddr(params[1], &pl_addr);
	crf.Initialize(pl_addr, params[2]);

	char *sample;
	pContext->LocalToString(params[3], &sample);
	
	int entity = params[4];
	int channel = params[5];
	int level = params[6];
	int flags = params[7];
	float vol = sp_ctof(params[8]);
	int pitch = params[9];
	int speakerentity = params[10];

	Vector *pOrigin = NULL, origin;
	Vector *pDir = NULL, dir;

	pContext->LocalToPhysAddr(params[11], &addr);
	if (addr != pContext->GetNullRef(SP_NULL_VECTOR))
	{
		pOrigin = &origin;
		origin.x = sp_ctof(addr[0]);
		origin.y = sp_ctof(addr[1]);
		origin.z = sp_ctof(addr[2]);
	}

	pContext->LocalToPhysAddr(params[12], &addr);
	if (addr != pContext->GetNullRef(SP_NULL_VECTOR))
	{
		pDir = &dir;
		dir.x = sp_ctof(addr[0]);
		dir.y = sp_ctof(addr[1]);
		dir.z = sp_ctof(addr[2]);
	}

	bool updatePos = params[13] ? true : false;
	float soundtime = sp_ctof(params[14]);

	CUtlVector<Vector> *pOrigVec = NULL;
	CUtlVector<Vector> origvec;
	if (params[0] > 14)
	{
		pOrigVec = &origvec;
		for (cell_t i = 15; i <= params[0]; i++)
		{
			Vector vec;
			pContext->LocalToPhysAddr(params[i], &addr);
			vec.x = sp_ctof(addr[0]);
			vec.y = sp_ctof(addr[1]);
			vec.z = sp_ctof(addr[2]);
			origvec.AddToTail(vec);
		}
	}

	/* If we're going to a "local player" and this is a dedicated server,
	 * intelligently redirect each sound.
	 */

	if (entity == -2 && engine->IsDedicatedServer())
	{
		for (cell_t i=0; i<params[2]; i++)
		{
			cell_t player[1];
			player[0] = pl_addr[i];
			crf.Reset();
			crf.Initialize(player, 1);
			if (g_InSoundHook)
			{
				SH_CALL(enginesoundPatch, 
					static_cast<void (IEngineSound::*)(IRecipientFilter &, int, int, const char*, float, 
					soundlevel_t, int, int, const Vector *, const Vector *, CUtlVector<Vector> *, bool, float, int)>
					(&IEngineSound::EmitSound))
					(crf, 
					player[0], 
					channel, 
					sample, 
					vol, 
					(soundlevel_t)level, 
					flags, 
					pitch, 
					pOrigin,
					pDir,
					pOrigVec,
					updatePos,
					soundtime,
					speakerentity);
			}
			else
			{
				engsound->EmitSound(crf, 
					player[0], 
					channel, 
					sample, 
					vol, 
					(soundlevel_t)level, 
					flags, 
					pitch, 
					pOrigin,
					pDir,
					pOrigVec,
					updatePos,
					soundtime,
					speakerentity);
			}
		}
	} else {
		if (g_InSoundHook)
		{
			SH_CALL(enginesoundPatch, 
				static_cast<void (IEngineSound::*)(IRecipientFilter &, int, int, const char*, float, 
				soundlevel_t, int, int, const Vector *, const Vector *, CUtlVector<Vector> *, bool, float, int)>
				(&IEngineSound::EmitSound))
				(crf, 
				entity, 
				channel, 
				sample, 
				vol, 
				(soundlevel_t)level, 
				flags, 
				pitch, 
				pOrigin,
				pDir,
				pOrigVec,
				updatePos,
				soundtime,
				speakerentity);
		}
		else
		{
			engsound->EmitSound(crf, 
				entity, 
				channel, 
				sample, 
				vol, 
				(soundlevel_t)level, 
				flags, 
				pitch, 
				pOrigin,
				pDir,
				pOrigVec,
				updatePos,
				soundtime,
				speakerentity);
		}
	}

	return 1;
}