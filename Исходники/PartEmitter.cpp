CPartEmitter::CPartEmitter(CBGame* inGame, CBScriptHolder* Owner) : CBObject(inGame)
{
	m_Width = m_Height = 0;

	SetRectEmpty(&m_Border);
	m_BorderThicknessLeft = m_BorderThicknessRight = m_BorderThicknessTop = m_BorderThicknessBottom = 0;

	m_Angle1 = m_Angle2 = 0;

	m_Velocity1 = m_Velocity2 = 0.0f;
	m_VelocityZBased = false;

	m_Scale1 = m_Scale2 = 100.0f;
	m_ScaleZBased = false;

	m_MaxParticles = 100;

	m_LifeTime1 = m_LifeTime2 = 1000;
	m_LifeTimeZBased = false;

	m_LastGenTime = 0;
	m_GenInterval = 0;
	m_GenAmount = 1;

	m_OverheadTime = 0;
	m_Running = false;

	m_MaxBatches = 0;
	m_BatchesGenerated = 0;

	m_FadeInTime = m_FadeOutTime = 0;

	m_Alpha1 = m_Alpha2 = 255;
	m_AlphaTimeBased = false;

	m_Rotation1 = m_Rotation2 = 0.0f;
	m_AngVelocity1 = m_AngVelocity2 = 0.0f;

	m_GrowthRate1 = m_GrowthRate2 = 0.0f;
	m_ExponentialGrowth = false;

	m_UseRegion = false;

	m_EmitEvent = NULL;
	m_Owner = Owner;
}