CivilianAI::CivilianAI() : AI_Mgr()
{
	m_fHearingDist	= 2000.0f;
	m_fSensingDist	= 200.0f;
	m_fSmellingDist	= 0.0f;
	m_fSeeingDist	= 2000.0f;

	m_fWalkSpeed	= 75.0f;
	m_fRunSpeed		= 180.0f;
	m_fRollSpeed	= 3.5f;

	m_fAIMass		= AI_DEFAULT_MASS;

	m_nAIStrength	= 5;

	m_nState = STATE_Idle; 
	m_nLastState = STATE_Idle; 
	m_dwFlags = FLAG_ALWAYSRECOIL;

	m_bMale = DTRUE;
	m_bCabal = DTRUE;

	// [blg]
	m_fAIHitPoints   = 30;
	m_fAIRandomHP    = 0;

	m_fAICharges	 = 100.0f;		//for Coleman's wacky scientist

	_mbscpy((unsigned char*)m_szAIState, (const unsigned char*)"IDLE");

	m_bMale = DTRUE;
	m_bLabTech = DFALSE;
	m_bScared = DFALSE;
	m_bSororitySkin = DFALSE;
}