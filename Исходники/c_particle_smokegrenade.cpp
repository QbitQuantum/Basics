//-----------------------------------------------------------------------------
// This is called after sending this entity's recording state
//-----------------------------------------------------------------------------
void C_ParticleSmokeGrenade::CleanupToolRecordingState( KeyValues *msg )
{
	if ( !ToolsEnabled() )
		return;

	BaseClass::CleanupToolRecordingState( msg );
	m_SmokeTrail.CleanupToolRecordingState( msg );

	// Generally, this is used to allow the entity to clean up
	// allocated state it put into the message, but here we're going
	// to use it to send particle system messages because we
	// know the grenade has been recorded at this point
	if ( !clienttools->IsInRecordingMode() )
		return;
	
	// NOTE: Particle system destruction message will be sent by the particle effect itself.
	if ( m_bVolumeFilled && GetToolParticleEffectId() == TOOLPARTICLESYSTEMID_INVALID )
	{
		// Needed for retriggering of the smoke grenade
		m_bVolumeFilled = false;

		int nId = AllocateToolParticleEffectId();

		KeyValues *msg = new KeyValues( "ParticleSystem_Create" );
		msg->SetString( "name", "C_ParticleSmokeGrenade" );
		msg->SetInt( "id", nId );
		msg->SetFloat( "time", gpGlobals->curtime );

		KeyValues *pEmitter = msg->FindKey( "DmeSpriteEmitter", true );
		pEmitter->SetInt( "count", NUM_PARTICLES_PER_DIMENSION * NUM_PARTICLES_PER_DIMENSION * NUM_PARTICLES_PER_DIMENSION );
		pEmitter->SetFloat( "duration", 0 );
		pEmitter->SetString( "material", "particle/particle_smokegrenade1" );
		pEmitter->SetInt( "active", true );

		KeyValues *pInitializers = pEmitter->FindKey( "initializers", true );

		KeyValues *pPosition = pInitializers->FindKey( "DmeVoxelPositionInitializer", true );
		pPosition->SetFloat( "centerx", m_SmokeBasePos.x );
		pPosition->SetFloat( "centery", m_SmokeBasePos.y );
		pPosition->SetFloat( "centerz", m_SmokeBasePos.z );
		pPosition->SetFloat( "particlesPerDimension", m_xCount );
		pPosition->SetFloat( "particleSpacing", m_SpacingRadius );

		KeyValues *pLifetime = pInitializers->FindKey( "DmeRandomLifetimeInitializer", true );
		pLifetime->SetFloat( "minLifetime", m_FadeEndTime );
 		pLifetime->SetFloat( "maxLifetime", m_FadeEndTime );

		KeyValues *pVelocity = pInitializers->FindKey( "DmeAttachmentVelocityInitializer", true );
		pVelocity->SetPtr( "entindex", (void*)entindex() );
 		pVelocity->SetFloat( "minRandomSpeed", 10 );
 		pVelocity->SetFloat( "maxRandomSpeed", 20 );

		KeyValues *pRoll = pInitializers->FindKey( "DmeRandomRollInitializer", true );
		pRoll->SetFloat( "minRoll", -6.0f );
 		pRoll->SetFloat( "maxRoll", 6.0f );

		KeyValues *pRollSpeed = pInitializers->FindKey( "DmeRandomRollSpeedInitializer", true );
		pRollSpeed->SetFloat( "minRollSpeed", -ROTATION_SPEED );
 		pRollSpeed->SetFloat( "maxRollSpeed", ROTATION_SPEED );

		KeyValues *pColor = pInitializers->FindKey( "DmeRandomInterpolatedColorInitializer", true );
		Color c1( 
			clamp( m_MinColor.x * 255.0f, 0, 255 ),
			clamp( m_MinColor.y * 255.0f, 0, 255 ),
			clamp( m_MinColor.z * 255.0f, 0, 255 ), 255 );
		Color c2( 
			clamp( m_MaxColor.x * 255.0f, 0, 255 ),
			clamp( m_MaxColor.y * 255.0f, 0, 255 ),
			clamp( m_MaxColor.z * 255.0f, 0, 255 ), 255 );
		pColor->SetColor( "color1", c1 );
		pColor->SetColor( "color2", c2 );

		KeyValues *pAlpha = pInitializers->FindKey( "DmeRandomAlphaInitializer", true );
		pAlpha->SetInt( "minStartAlpha", 255 );
		pAlpha->SetInt( "maxStartAlpha", 255 );
		pAlpha->SetInt( "minEndAlpha", 0 );
		pAlpha->SetInt( "maxEndAlpha", 0 );

		KeyValues *pSize = pInitializers->FindKey( "DmeRandomSizeInitializer", true );
		pSize->SetFloat( "minStartSize", SMOKEPARTICLE_SIZE );
		pSize->SetFloat( "maxStartSize", SMOKEPARTICLE_SIZE );
		pSize->SetFloat( "minEndSize", SMOKEPARTICLE_SIZE );
		pSize->SetFloat( "maxEndSize", SMOKEPARTICLE_SIZE );

		pInitializers->FindKey( "DmeSolidKillInitializer", true );

		KeyValues *pUpdaters = pEmitter->FindKey( "updaters", true );

		pUpdaters->FindKey( "DmeRollUpdater", true );
		pUpdaters->FindKey( "DmeColorUpdater", true );

		KeyValues *pAlphaCosineUpdater = pUpdaters->FindKey( "DmeAlphaCosineUpdater", true );
		pAlphaCosineUpdater->SetFloat( "duration", m_FadeEndTime - m_FadeStartTime );
		
		pUpdaters->FindKey( "DmeColorDynamicLightUpdater", true );

		KeyValues *pSmokeGrenadeUpdater = pUpdaters->FindKey( "DmeSmokeGrenadeUpdater", true );
 		pSmokeGrenadeUpdater->SetFloat( "centerx", m_SmokeBasePos.x );
		pSmokeGrenadeUpdater->SetFloat( "centery", m_SmokeBasePos.y );
		pSmokeGrenadeUpdater->SetFloat( "centerz", m_SmokeBasePos.z );
		pSmokeGrenadeUpdater->SetFloat( "particlesPerDimension", m_xCount );
		pSmokeGrenadeUpdater->SetFloat( "particleSpacing", m_SpacingRadius );
		pSmokeGrenadeUpdater->SetFloat( "radiusExpandTime", SMOKESPHERE_EXPAND_TIME );
		pSmokeGrenadeUpdater->SetFloat( "cutoffFraction", 0.7f );

		ToolFramework_PostToolMessage( HTOOLHANDLE_INVALID, msg );
		msg->deleteThis();
	}
}