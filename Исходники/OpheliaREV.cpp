OpheliaREV::OpheliaREV() : AI_Mgr()
{
	m_fHearingDist	= 1500.0f;
	m_fSensingDist	= 200.0f;
	m_fSmellingDist	= 0.0f;
	m_fSeeingDist	= 1500.0f;

	m_fWalkSpeed	= 75.0f;
	m_fRunSpeed		= 180.0f;
	m_fRollSpeed	= 105.0f;
	m_fJumpSpeed	= 400.0f;

	m_fAIMass		= AI_DEFAULT_MASS;

	m_nAIStrength	= 5;

	m_nState = STATE_Idle; 
	m_nLastState = STATE_Idle; 
	m_dwFlags = FLAG_CRAWL | FLAG_JUMP | FLAG_DODGE;

	m_bCabal = DTRUE;

	// [blg]
	m_fAIHitPoints   = 400;
	m_fAIRandomHP    = 0;
	m_fAIArmorPoints = 400;

	_mbscpy((unsigned char*)m_szAIState, (const unsigned char*)"PASSIVE");
	_mbscpy((unsigned char*)m_szAIWeapon[0], (const unsigned char*)"TESLA");
	_mbscpy((unsigned char*)m_szAIWeapon[1], (const unsigned char*)"SNIPER");

	m_fAIBullets  = 500;
	m_fAIBMG	  = 100;
	m_fAIShells   = 150;
	m_fAIGrenades = 50;
	m_fAIRockets  = 100;
	m_fAIFlares   = 100;
	m_fAICells    = 500;
	m_fAICharges  = 500;
	m_fAIFuel	  = 500;
}