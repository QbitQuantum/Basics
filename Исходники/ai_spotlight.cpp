//------------------------------------------------------------------------------
// Purpose:
//------------------------------------------------------------------------------
void CAI_Spotlight::UpdateSpotlightEndpoint( void )
{
	if ( !m_hSpotlight )
	{
		CreateSpotlightEntities();
	}

	Vector vecStartPoint, vecEndPoint;
	vecStartPoint = m_hSpotlight->GetAbsStartPos();
	ComputeEndpoint( vecStartPoint, &vecEndPoint );

	// If I'm not facing the spotlight turn it off 
	Vector vecSpotDir;
	VectorSubtract( vecEndPoint, vecStartPoint, vecSpotDir );
	float flBeamLength = VectorNormalize(vecSpotDir);
	
	m_hSpotlightTarget->SetAbsOrigin( vecEndPoint );
	m_hSpotlightTarget->SetAbsVelocity( vec3_origin );
	m_hSpotlightTarget->m_vSpotlightOrg = vecStartPoint;
	m_hSpotlightTarget->m_vSpotlightDir = vecSpotDir;

	// Avoid sudden change in where beam fades out when cross disconinuities
	m_flSpotlightCurLength = Lerp( 0.20f, m_flSpotlightCurLength, flBeamLength );

	// Fade out spotlight end if past max length.  
	if (m_flSpotlightCurLength > 2*m_flSpotlightMaxLength)
	{
		m_hSpotlightTarget->SetRenderColorA( 0 );
		m_hSpotlight->SetFadeLength(m_flSpotlightMaxLength);
	}
	else if (m_flSpotlightCurLength > m_flSpotlightMaxLength)		
	{
		m_hSpotlightTarget->SetRenderColorA( (1-((m_flSpotlightCurLength-m_flSpotlightMaxLength)/m_flSpotlightMaxLength)) );
		m_hSpotlight->SetFadeLength(m_flSpotlightMaxLength);
	}
	else
	{
		m_hSpotlightTarget->SetRenderColorA( 1.0 );
		m_hSpotlight->SetFadeLength(m_flSpotlightCurLength);
	}

	// Adjust end width to keep beam width constant
	float flNewWidth = SPOTLIGHT_WIDTH * ( flBeamLength / m_flSpotlightMaxLength );
	
	flNewWidth = min( 100, flNewWidth );

	m_hSpotlight->SetWidth(flNewWidth);
	m_hSpotlight->SetEndWidth(flNewWidth);

	// Adjust width of light on the end.  
	if ( FBitSet (m_nFlags, AI_SPOTLIGHT_NO_DLIGHTS) )
	{
		m_hSpotlightTarget->m_flLightScale = 0.0;
	}
	else
	{
		m_hSpotlightTarget->m_flLightScale = flNewWidth;
	}
}