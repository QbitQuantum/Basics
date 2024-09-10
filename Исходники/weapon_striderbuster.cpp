//-----------------------------------------------------------------------------
// Purpose: Stick to an entity (using hierarchy if we can)
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CWeaponStriderBuster::StickToEntity( CBaseEntity *pOther )
{
	// Make sure the object is travelling fast enough to stick
	if ( m_flCollisionSpeedSqr > 50 && !m_bNoseDiving )
	{
		// See if this is a valid strider bit
		if ( ShouldStickToEntity( pOther ) )
		{
			// Attempt to constraint to it
			if ( CreateConstraintToObject( pOther ) )
			{
				// Only works for striders, at the moment
				CBaseEntity *pFollowParent = pOther->GetOwnerEntity();
				if ( pFollowParent == NULL )
					return false;

				// Allows us to identify our constrained object later
				SetOwnerEntity( pFollowParent );

				// Make a sound
				EmitSound( "Weapon_StriderBuster.StickToEntity" );
				
				DispatchParticleEffect( "striderbuster_attach", GetAbsOrigin(), GetAbsAngles(), NULL );

				if( striderbuster_use_particle_flare.GetBool() )
				{
					// We don't have to save any pointers or handles to this because it's parented to the buster.
					// So it will die when the buster dies. Yay.
					CParticleSystem *pFlare = (CParticleSystem *) CreateEntityByName( "info_particle_system" );
					
					if ( pFlare != NULL )
					{
						pFlare->KeyValue( "start_active", "1" );
						pFlare->KeyValue( "effect_name", "striderbuster_attached_pulse" );
						pFlare->SetParent( this );
						pFlare->SetLocalOrigin( vec3_origin );
						DispatchSpawn( pFlare );
						pFlare->Activate();
					}
				}
				else
				{
					// Create a glow sprite
					m_hGlowSprite = CSprite::SpriteCreate( "sprites/orangeflare1.vmt", GetLocalOrigin(), false );

					Assert( m_hGlowSprite );
					if ( m_hGlowSprite != NULL )
					{
						m_hGlowSprite->TurnOn();
						m_hGlowSprite->SetTransparency( kRenderWorldGlow, 255, 255, 255, 255, kRenderFxNoDissipation );
						m_hGlowSprite->SetAbsOrigin( GetAbsOrigin() );
						m_hGlowSprite->SetScale( 5.0f );
						m_hGlowSprite->m_nRenderFX = kRenderFxStrobeFaster;
						m_hGlowSprite->SetGlowProxySize( 16.0f );
						m_hGlowSprite->SetParent( this );
					}
				}

				// Stop touching things
				SetTouch( NULL );

				// Must be a strider
				CNPC_Strider *pStrider = dynamic_cast<CNPC_Strider *>(pFollowParent);
				if ( pStrider == NULL )
					return false;

				// Notify the strider we're attaching to him
				pStrider->StriderBusterAttached( this );
				
				m_OnAttachToStrider.FireOutput( this, this );

				// Start the ping sound.
				SetContextThink( &CWeaponStriderBuster::BusterPingThink, gpGlobals->curtime + BUSTER_PING_SOUND_FREQ, s_pBusterPingThinkContext );
				
				// Don't autodelete this one!
				WeaponManager_RemoveManaged( this );

				return true;
			}

			return false;
		}
	}

	return false;
}