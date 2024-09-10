DBOOL DeathShroud::InitialUpdate(DVector *pMovement)
{
	m_pServerDE = BaseClass::GetServerDE();
	if (!m_pServerDE) return DFALSE;

    if(m_bLoadAnims)
	{
	    m_Anim_Sound.SetAnimationIndexes(m_hObject);
		m_Anim_Sound.GenerateHitSpheres(m_hObject);
	    m_Anim_Sound.SetSoundRoot("sounds\\enemies\\DeathShroud");
		m_bLoadAnims = DFALSE;
	}

	m_InventoryMgr.AddDamageMultiplier(0.5f);	

	AI_Mgr::InitStatics(&m_Anim_Sound);

	//play ambient looping sound
	PlaySoundInfo playSoundInfo;
	PLAYSOUNDINFO_INIT( playSoundInfo );

	playSoundInfo.m_dwFlags = PLAYSOUND_3D | PLAYSOUND_ATTACHED | PLAYSOUND_GETHANDLE | PLAYSOUND_REVERB;
	playSoundInfo.m_dwFlags |= PLAYSOUND_LOOP | PLAYSOUND_CTRL_VOL;
	
	_mbsncpy((unsigned char*)playSoundInfo.m_szSoundName, (const unsigned char*)"sounds\\enemies\\deathshroud\\de_loop_2.wav", _MAX_PATH );
	playSoundInfo.m_hObject = m_hObject;
	playSoundInfo.m_nPriority = SOUNDPRIORITY_AI_MEDIUM;
	playSoundInfo.m_fOuterRadius = 1000;
	playSoundInfo.m_fInnerRadius = 1000 * 0.1f;
	playSoundInfo.m_nVolume = 50;
	
	g_pServerDE->PlaySound( &playSoundInfo );
	m_hLoopSound = playSoundInfo.m_hSound;

	//fade the deathshroud
	DVector vColor;
	DFLOAT fAlpha = 0.0f;

	m_pServerDE->GetObjectColor(m_hObject,&vColor.x, &vColor.y, &vColor.z, &fAlpha);
	fAlpha = 0.90f;
	m_pServerDE->SetObjectColor(m_hObject,vColor.x,vColor.y,vColor.z, fAlpha);

	return DTRUE;
}