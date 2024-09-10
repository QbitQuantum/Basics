//-----------------------------------------------------------------------------
// Purpose: Fades lookup weight from CurWeight->0.0 
//-----------------------------------------------------------------------------
void CColorCorrection::FadeOutThink( void )
{
	// Check for conditions where we shouldn't fade out
	if ( m_flFadeOutDuration <= 0 || // not set to fade out
			m_flCurWeight <= 0.0f || // already faded out
					   m_bEnabled || // fade in/out mutex
		   m_flMaxWeight == 0.0f  || // min==max
	 m_flStartFadeOutWeight <= 0.0f )// already at min weight
	{
		SetNextThink ( TICK_NEVER_THINK, s_pFadeOutContextThink );
		return;
	}

	// If we started fading out without fully fading in, use a truncated duration
    float flTimeToFade = m_flFadeOutDuration;
	if ( m_flStartFadeOutWeight < m_flMaxWeight )
	{	
		float flWeightRatio		= m_flStartFadeOutWeight / m_flMaxWeight;
		flWeightRatio = clamp ( flWeightRatio, 0.01f, 1.0f );
		flTimeToFade			= m_flFadeOutDuration * flWeightRatio;
	}	
	
	Assert ( flTimeToFade > 0.0f );
	float flFadeRatio = (gpGlobals->curtime - m_flTimeStartFadeOut) / flTimeToFade;
	flFadeRatio = clamp ( flFadeRatio, 0.0f, 1.0f );
	m_flStartFadeOutWeight = clamp ( m_flStartFadeOutWeight, 0.0f, 1.0f );

	m_flCurWeight = Lerp( 1.0f - flFadeRatio, 0.0f, m_flStartFadeOutWeight );

	SetNextThink( gpGlobals->curtime + COLOR_CORRECTION_ENT_THINK_RATE, s_pFadeOutContextThink );
}