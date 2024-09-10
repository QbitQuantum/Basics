void C_SDKPlayer::ClientThink()
{
	UpdateSoundEvents();

	// Pass on through to the base class.
	BaseClass::ClientThink();

	bool bFoundViewTarget = false;
	
	Vector vForward;
	AngleVectors( GetLocalAngles(), &vForward );

	for( int iClient = 1; iClient <= gpGlobals->maxClients; ++iClient )
	{
		CBaseEntity *pEnt = UTIL_PlayerByIndex( iClient );
		if(!pEnt || !pEnt->IsPlayer())
			continue;

		if ( pEnt->entindex() == entindex() )
			continue;

		Vector vTargetOrigin = pEnt->GetAbsOrigin();
		Vector vMyOrigin =  GetAbsOrigin();

		Vector vDir = vTargetOrigin - vMyOrigin;
		
		if ( vDir.Length() > 128 ) 
			continue;

		VectorNormalize( vDir );

		if ( DotProduct( vForward, vDir ) < 0.0f )
			 continue;

		m_vLookAtTarget = pEnt->EyePosition();
		bFoundViewTarget = true;
		break;
	}

	if ( bFoundViewTarget == false )
	{
		m_vLookAtTarget = GetAbsOrigin() + vForward * 512;
	}

	UpdateIDTarget();

	// Avoidance
	if ( gpGlobals->curtime >= m_fNextThinkPushAway )
	{
		PerformObstaclePushaway( this );
		m_fNextThinkPushAway =  gpGlobals->curtime + PUSHAWAY_THINK_INTERVAL;
	}

	if (Q_strcmp(m_szColorCorrectionFile, cl_colorcorrection_file.GetString()))
	{
		if (m_hColorCorrection != INVALID_CLIENT_CCHANDLE)
			g_pColorCorrectionMgr->RemoveColorCorrection(m_hColorCorrection);

		m_hColorCorrection = g_pColorCorrectionMgr->AddColorCorrection(VarArgs("materials/correction/%s.raw", cl_colorcorrection_file.GetString()));
		Q_strncpy(m_szColorCorrectionFile, cl_colorcorrection_file.GetString(), sizeof(m_szColorCorrectionFile));
	}

	g_pColorCorrectionMgr->SetColorCorrectionWeight(m_hColorCorrection, cl_colorcorrection_weight.GetFloat());
}