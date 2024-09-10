//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CAntlionGrub::CreateGlow( void )
{
	// Create the glow sprite
	m_hGlowSprite = CSprite::SpriteCreate( "sprites/grubflare1.vmt", GetLocalOrigin(), false );
	Assert( m_hGlowSprite );
	if ( m_hGlowSprite == NULL )
		return;

	m_hGlowSprite->TurnOn();
	m_hGlowSprite->SetTransparency( kRenderWorldGlow, 156, 169, 121, 164, kRenderFxNoDissipation );
	m_hGlowSprite->SetScale( 0.5f );
	m_hGlowSprite->SetGlowProxySize( 16.0f );
	int nAttachment = LookupAttachment( "glow" );
	m_hGlowSprite->SetParent( this, nAttachment );
	m_hGlowSprite->SetLocalOrigin( vec3_origin );
	
	// Don't uselessly animate, we're a static sprite!
	m_hGlowSprite->SetThink( NULL );
	m_hGlowSprite->SetNextThink( TICK_NEVER_THINK );
}