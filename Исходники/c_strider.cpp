//-----------------------------------------------------------------------------
// Purpose: 
// Input  : &origin - 
//			&normal - 
//			scale - 
//-----------------------------------------------------------------------------
void StriderBlood( const Vector &origin, const Vector &normal, float scale )
{
	VPROF_BUDGET( "StriderBlood", VPROF_BUDGETGROUP_PARTICLE_RENDERING );
	
	Vector	offset;
	
	CSmartPtr<CSplashParticle> pSimple = CSplashParticle::Create( "splish" );
	pSimple->SetSortOrigin( origin );

	Vector	color[3];
	color[0] = color[1] = color[2] = Vector( 1, 1, 1 );

	float	colorRamp;

	int i;
	float	flScale = scale / 8.0f;

	PMaterialHandle	hMaterial = ParticleMgr()->GetPMaterial( "effects/slime1" );

	float	length = 0.1f;
	Vector	vForward, vRight, vUp;
	Vector	offDir;

	TrailParticle	*tParticle;

	CSmartPtr<CTrailParticles> sparkEmitter = CTrailParticles::Create( "splash" );

	if ( !sparkEmitter )
		return;

	sparkEmitter->SetSortOrigin( origin );
	sparkEmitter->m_ParticleCollision.SetGravity( 800.0f );
	sparkEmitter->SetFlag( bitsPARTICLE_TRAIL_VELOCITY_DAMPEN );
	sparkEmitter->SetVelocityDampen( 2.0f );

	//Dump out drops
	for ( i = 0; i < 64; i++ )
	{
		offset = origin;
		offset[0] += random->RandomFloat( -16.0f, 16.0f ) * flScale;
		offset[1] += random->RandomFloat( -16.0f, 16.0f ) * flScale;

		tParticle = (TrailParticle *) sparkEmitter->AddParticle( sizeof(TrailParticle), hMaterial, offset );

		if ( tParticle == NULL )
			break;

		tParticle->m_flLifetime	= 0.0f;
		tParticle->m_flDieTime	= 1.0f;

		offDir = normal + RandomVector( -1.0f, 1.0f );

		tParticle->m_vecVelocity = offDir * random->RandomFloat( BLOOD_MIN_SPEED * flScale * 2.0f, BLOOD_MAX_SPEED * flScale * 2.0f );
		tParticle->m_vecVelocity[2] += random->RandomFloat( 8.0f, 32.0f ) * flScale;

		tParticle->m_flWidth		= random->RandomFloat( 12.0f, 16.0f ) * flScale;
		tParticle->m_flLength		= random->RandomFloat( length*0.5f, length ) * flScale;

		colorRamp = random->RandomFloat( 0.5f, 2.0f );

		int randomColor = random->RandomInt( 0, 2 );

		tParticle->m_color.r = min( 1.0f, color[randomColor].x * colorRamp ) * 255;
		tParticle->m_color.g = min( 1.0f, color[randomColor].y * colorRamp ) * 255;
		tParticle->m_color.b = min( 1.0f, color[randomColor].z * colorRamp ) * 255;
		tParticle->m_color.a = 255;
	}
}