//-----------------------------------------------------------------------------
// Purpose: 
// Input  : &origin - 
//			&normal - 
//			scale - 
//			r - 
//			g - 
//			b - 
//			flags - 
//-----------------------------------------------------------------------------
void FX_BloodSpray( const Vector &origin, const Vector &normal, float scale, unsigned char r, unsigned char g, unsigned char b, int flags )
{
	if ( UTIL_IsLowViolence() )
		return;

	//debugoverlay->AddLineOverlay( origin, origin + normal * 72, 255, 255, 255, true, 10 ); 

	Vector offset;
	float spread	= 0.2f;
	
	//Find area ambient light color and use it to tint smoke
	Vector worldLight = WorldGetLightForPoint( origin, true );
	Vector color = Vector( (float)(worldLight[0] * r) / 255.0f, (float)(worldLight[1] * g) / 255.0f, (float)(worldLight[2] * b) / 255.0f );
	float colorRamp;

	int i;

	Vector	offDir;

	Vector right;
	Vector up;

	if (normal != Vector(0, 0, 1) )
	{
		right = normal.Cross( Vector(0, 0, 1) );
		up = right.Cross( normal );
	}
	else
	{
		right = Vector(0, 0, 1);
		up = right.Cross( normal );
	}

	//
	// Dump out drops
	//
	if (flags & FX_BLOODSPRAY_DROPS)
	{
		TrailParticle *tParticle;

		CSmartPtr<CTrailParticles> pTrailEmitter = CTrailParticles::Create( "blooddrops" );
		if ( !pTrailEmitter )
			return;

		pTrailEmitter->SetSortOrigin( origin );

		// Partial gravity on blood drops.
		pTrailEmitter->SetGravity( 600.0 ); 

		pTrailEmitter->GetBinding().SetBBox( origin - Vector( 32, 32, 32 ), origin + Vector( 32, 32, 32 ) );
		pTrailEmitter->SetFlag( bitsPARTICLE_TRAIL_VELOCITY_DAMPEN );
		pTrailEmitter->SetVelocityDampen( 0.2f );

		PMaterialHandle	hMaterial = ParticleMgr()->GetPMaterial( "effects/blood_drop" );

		//
		// Long stringy drops of blood.
		//
		for ( i = 0; i < 14; i++ )
		{
			// Originate from within a circle 'scale' inches in diameter.
			offset = origin;
			offset += right * random->RandomFloat( -0.5f, 0.5f ) * scale;
			offset += up * random->RandomFloat( -0.5f, 0.5f ) * scale;

			tParticle = (TrailParticle *) pTrailEmitter->AddParticle( sizeof(TrailParticle), hMaterial, offset );

			if ( tParticle == NULL )
				break;

			tParticle->m_flLifetime	= 0.0f;

			offDir = normal + RandomVector( -0.3f, 0.3f );

			tParticle->m_vecVelocity = offDir * random->RandomFloat( 4.0f * scale, 40.0f * scale );
			tParticle->m_vecVelocity[2] += random->RandomFloat( 4.0f, 16.0f ) * scale;

			tParticle->m_flWidth		= random->RandomFloat( 0.125f, 0.275f ) * scale;
			tParticle->m_flLength		= random->RandomFloat( 0.02f, 0.03f ) * scale;
			tParticle->m_flDieTime		= random->RandomFloat( 0.5f, 1.0f );

			FloatToColor32( tParticle->m_color, color[0], color[1], color[2], 1.0f );
		}

		//
		// Shorter droplets.
		//
		for ( i = 0; i < 24; i++ )
		{
			// Originate from within a circle 'scale' inches in diameter.
			offset = origin;
			offset += right * random->RandomFloat( -0.5f, 0.5f ) * scale;
			offset += up * random->RandomFloat( -0.5f, 0.5f ) * scale;

			tParticle = (TrailParticle *) pTrailEmitter->AddParticle( sizeof(TrailParticle), hMaterial, offset );

			if ( tParticle == NULL )
				break;

			tParticle->m_flLifetime	= 0.0f;

			offDir = normal + RandomVector( -1.0f, 1.0f );
			offDir[2] += random->RandomFloat(0, 1.0f);

			tParticle->m_vecVelocity = offDir * random->RandomFloat( 2.0f * scale, 25.0f * scale );
			tParticle->m_vecVelocity[2] += random->RandomFloat( 4.0f, 16.0f ) * scale;

			tParticle->m_flWidth		= random->RandomFloat( 0.25f, 0.375f ) * scale;
			tParticle->m_flLength		= random->RandomFloat( 0.0025f, 0.005f ) * scale;
			tParticle->m_flDieTime		= random->RandomFloat( 0.5f, 1.0f );

			FloatToColor32( tParticle->m_color, color[0], color[1], color[2], 1.0f );
		}
	}

	if ((flags & FX_BLOODSPRAY_GORE) || (flags & FX_BLOODSPRAY_CLOUD))
	{
		CSmartPtr<CBloodSprayEmitter> pSimple = CBloodSprayEmitter::Create( "bloodgore" );
		if ( !pSimple )
			return;

		pSimple->SetSortOrigin( origin );
		pSimple->SetGravity( 0 );

		PMaterialHandle	hMaterial;

		//
		// Tight blossom of blood at the center.
		//
		if (flags & FX_BLOODSPRAY_GORE)
		{
			hMaterial = ParticleMgr()->GetPMaterial( "effects/blood_gore" );

			SimpleParticle *pParticle;

			for ( i = 0; i < 6; i++ )
			{
				// Originate from within a circle 'scale' inches in diameter.
				offset = origin + ( 0.5 * scale * normal );
				offset += right * random->RandomFloat( -0.5f, 0.5f ) * scale;
				offset += up * random->RandomFloat( -0.5f, 0.5f ) * scale;

				pParticle = (SimpleParticle *) pSimple->AddParticle( sizeof( SimpleParticle ), hMaterial, offset );

				if ( pParticle != NULL )
				{
					pParticle->m_flLifetime = 0.0f;
					pParticle->m_flDieTime	= 0.3f;

					spread = 0.2f;
					pParticle->m_vecVelocity.Random( -spread, spread );
					pParticle->m_vecVelocity += normal * random->RandomInt( 10, 100 );
					//VectorNormalize( pParticle->m_vecVelocity );

					colorRamp = random->RandomFloat( 0.75f, 1.25f );

					pParticle->m_uchColor[0]	= MIN( 1.0f, color[0] * colorRamp ) * 255.0f;
					pParticle->m_uchColor[1]	= MIN( 1.0f, color[1] * colorRamp ) * 255.0f;
					pParticle->m_uchColor[2]	= MIN( 1.0f, color[2] * colorRamp ) * 255.0f;
					
					pParticle->m_uchStartSize	= random->RandomFloat( scale * 0.25, scale );
					pParticle->m_uchEndSize		= pParticle->m_uchStartSize * 2;
					
					pParticle->m_uchStartAlpha	= random->RandomInt( 200, 255 );
					pParticle->m_uchEndAlpha	= 0;
					
					pParticle->m_flRoll			= random->RandomInt( 0, 360 );
					pParticle->m_flRollDelta	= 0.0f;
				}
			}
		}

		//
		// Diffuse cloud just in front of the exit wound.
		//
		if (flags & FX_BLOODSPRAY_CLOUD)
		{
			hMaterial = ParticleMgr()->GetPMaterial( "effects/blood_puff" );

			SimpleParticle *pParticle;

			for ( i = 0; i < 6; i++ )
			{
				// Originate from within a circle '2 * scale' inches in diameter.
				offset = origin + ( scale * normal );
				offset += right * random->RandomFloat( -1, 1 ) * scale;
				offset += up * random->RandomFloat( -1, 1 ) * scale;

				pParticle = (SimpleParticle *) pSimple->AddParticle( sizeof( SimpleParticle ), hMaterial, offset );

				if ( pParticle != NULL )
				{
					pParticle->m_flLifetime = 0.0f;
					pParticle->m_flDieTime	= random->RandomFloat( 0.5f, 0.8f);

					spread = 0.5f;
					pParticle->m_vecVelocity.Random( -spread, spread );
					pParticle->m_vecVelocity += normal * random->RandomInt( 100, 200 );

					colorRamp = random->RandomFloat( 0.75f, 1.25f );

					pParticle->m_uchColor[0]	= MIN( 1.0f, color[0] * colorRamp ) * 255.0f;
					pParticle->m_uchColor[1]	= MIN( 1.0f, color[1] * colorRamp ) * 255.0f;
					pParticle->m_uchColor[2]	= MIN( 1.0f, color[2] * colorRamp ) * 255.0f;
					
					pParticle->m_uchStartSize	= random->RandomFloat( scale * 1.5f, scale * 2.0f );
					pParticle->m_uchEndSize		= pParticle->m_uchStartSize * 4;
					
					pParticle->m_uchStartAlpha	= random->RandomInt( 80, 128 );
					pParticle->m_uchEndAlpha	= 0;
					
					pParticle->m_flRoll			= random->RandomInt( 0, 360 );
					pParticle->m_flRollDelta	= 0.0f;
				}
			}
		}
	}

	// TODO: Play a sound?
	//CLocalPlayerFilter filter;
	//C_BaseEntity::EmitSound( filter, SOUND_FROM_WORLD, CHAN_VOICE, "Physics.WaterSplash", 1.0, ATTN_NORM, 0, 100, &origin );
}