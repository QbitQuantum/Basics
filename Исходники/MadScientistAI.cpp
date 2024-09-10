MadScientistAI::MadScientistAI() : AI_Mgr()
{
	m_fHearingDist	= 0.0f;
	m_fSensingDist	= 200.0f;
	m_fSmellingDist	= 0.0f;
	m_fSeeingDist	= 1000.0f;

	m_fWalkSpeed	= 75.0f;
	m_fRunSpeed		= 180.0f;

	m_fAIMass		= AI_DEFAULT_MASS;

	m_nAIStrength	= 5;

	m_nState = STATE_Idle; 
	m_nLastState = STATE_Idle; 
	m_dwFlags = 0;

	m_bCabal = DTRUE;

	// [blg]
	m_fAIHitPoints   = 30;
	m_fAIRandomHP    = 0;
	m_fAIArmorPoints = 0;

	_mbscpy((unsigned char*)m_szAIState, (const unsigned char*)"IDLE");
}