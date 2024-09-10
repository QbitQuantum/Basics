void CNPC_Dog::ThrowObject( const char *pAttachmentName )
{
	if ( m_hPhysicsEnt )
	{
		m_bHasObject = false;

		IPhysicsObject *pPhysObj = m_hPhysicsEnt->VPhysicsGetObject();

		if ( pPhysObj )
		{
			Vector vGunPos;
			QAngle angGunAngles;

			AngularImpulse angVelocity = RandomAngularImpulse( -250 , -250 ) / pPhysObj->GetMass();

			InvalidateBoneCache();

			int iAttachment = LookupAttachment( pAttachmentName );

			if ( iAttachment == 0 )
				 iAttachment = m_iPhysGunAttachment;
			
			GetAttachment( iAttachment, vGunPos, angGunAngles );

			pPhysObj->Wake();

			if ( pPhysObj->GetShadowController() )
			{
				m_hPhysicsEnt->SetParent( NULL );
				m_hPhysicsEnt->SetMoveType( (MoveType_t)m_iContainerMoveType );
				m_hPhysicsEnt->SetOwnerEntity( this );

				pPhysObj->RemoveShadowController();
				pPhysObj->SetPosition( m_hPhysicsEnt->GetLocalOrigin(), m_hPhysicsEnt->GetLocalAngles(), true );

				pPhysObj->RecheckCollisionFilter();
				pPhysObj->RecheckContactPoints();
			}
				
			if ( m_hThrowTarget == NULL )
			#ifdef SecobMod__Enable_Fixed_Multiplayer_AI
				m_hThrowTarget = UTIL_GetNearestVisiblePlayer(this); 
			#else
				m_hThrowTarget = AI_GetSinglePlayer();
			#endif //SecobMod__Enable_Fixed_Multiplayer_AI

			Vector vThrowDirection;

			if ( m_hThrowTarget )
			{
				Vector vThrowOrigin = m_hThrowTarget->GetAbsOrigin();
				
				if ( m_hThrowTarget->IsPlayer() )
					 vThrowOrigin = vThrowOrigin + Vector( random->RandomFloat( -128, 128 ), random->RandomFloat( -128, 128 ), 0 );

				Vector vecToss = VecCheckToss( this, vGunPos, vThrowOrigin, m_flThrowArcModifier, 1.0f, true );

				if( vecToss == vec3_origin )
				{
					// Fix up an impossible throw so dog will at least toss the box in the target's general direction instead of dropping it.
					// Also toss it up in the air so it will fall down and break. (Just throw the box up at a 45 degree angle)
					Vector forward, up;
					GetVectors( &forward, NULL, &up );

					vecToss = forward + up;
					VectorNormalize( vecToss );

					vecToss *= pPhysObj->GetMass() * 30.0f;
				}

				vThrowDirection = vecToss + ( m_hThrowTarget->GetSmoothedVelocity() / 2 );
							
				Vector vLinearDrag;

				Vector unitVel = vThrowDirection;
				VectorNormalize( unitVel );

				float flTest = 1000 / vThrowDirection.Length();

				float flDrag = pPhysObj->CalculateLinearDrag( vThrowDirection );
				vThrowDirection = vThrowDirection + ( unitVel * ( flDrag * flDrag ) ) / flTest;
			
				pPhysObj->SetVelocity( &vThrowDirection, &angVelocity );
				
				m_flTimeToCatch = gpGlobals->curtime + dog_max_wait_time.GetFloat();

				//Don't start pulling until the object is away from me.
				//We base the time on the throw velocity.
				m_flTimeToPull = gpGlobals->curtime + ( 1000 / vThrowDirection.Length() );
			}

			//Fire Output!
			m_OnThrow.FireOutput( this, this );

			ClearBeams();
			
			if ( m_bBeamEffects == true )
			{
				EmitSound( "Weapon_PhysCannon.Launch" );
				
				CBeam *pBeam = CBeam::BeamCreate(  "sprites/orangelight1.vmt", 1.8 );

				if ( pBeam != NULL )
				{
					pBeam->PointEntInit( m_hPhysicsEnt->WorldSpaceCenter(), this );
					pBeam->SetEndAttachment( m_iPhysGunAttachment );
					pBeam->SetWidth( 6.4 );
					pBeam->SetEndWidth( 12.8 );					
					pBeam->SetBrightness( 255 );
					pBeam->SetColor( 255, 255, 255 );
					pBeam->LiveForTime( 0.2f );
					pBeam->RelinkBeam();
					pBeam->SetNoise( 2 );
				}
			
				Vector	shotDir = ( m_hPhysicsEnt->WorldSpaceCenter() - vGunPos );
				VectorNormalize( shotDir );

				CPVSFilter filter( m_hPhysicsEnt->WorldSpaceCenter() );
				te->GaussExplosion( filter, 0.0f, m_hPhysicsEnt->WorldSpaceCenter() - ( shotDir * 4.0f ), RandomVector(-1.0f, 1.0f), 0 );
			}
		}
	}
}