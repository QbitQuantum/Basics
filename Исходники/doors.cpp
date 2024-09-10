//-----------------------------------------------------------------------------
// Purpose: Starts the door going to its "up" position (simply ToggleData->vecPosition2).
//-----------------------------------------------------------------------------
void CBaseDoor::DoorGoUp( void )
{
	edict_t	*pevActivator;

	UpdateAreaPortals( true );
	// It could be going-down, if blocked.
	ASSERT(m_toggle_state == TS_AT_BOTTOM || m_toggle_state == TS_GOING_DOWN);

	// emit door moving and stop sounds on CHAN_STATIC so that the multicast doesn't
	// filter them out and leave a client stuck with looping door sounds!
	if ( !HasSpawnFlags(SF_DOOR_SILENT ) )
	{
		// If we're not moving already, start the moving noise
		if ( m_toggle_state != TS_GOING_UP && m_toggle_state != TS_GOING_DOWN )
		{
			StartMovingSound();
		}
	}

	m_toggle_state = TS_GOING_UP;
	
	SetMoveDone( &CBaseDoor::DoorHitTop );
	if ( IsRotatingDoor() )		// !!! BUGBUG Triggered doors don't work with this yet
	{
		float	sign = 1.0;

		if ( m_hActivator != NULL )
		{
			pevActivator = m_hActivator->edict();
			
			if ( !HasSpawnFlags( SF_DOOR_ONEWAY ) && m_vecMoveAng.y ) 		// Y axis rotation, move away from the player
			{
				// Positive is CCW, negative is CW, so make 'sign' 1 or -1 based on which way we want to open.
				// Important note:  All doors face East at all times, and twist their local angle to open.
				//					So you can't look at the door's facing to determine which way to open.

				Vector nearestPoint;
				CollisionProp()->CalcNearestPoint( m_hActivator->GetAbsOrigin(), &nearestPoint );
				Vector activatorToNearestPoint = nearestPoint - m_hActivator->GetAbsOrigin();
				activatorToNearestPoint.z = 0;

				Vector activatorToOrigin = GetAbsOrigin() - m_hActivator->GetAbsOrigin();
				activatorToOrigin.z = 0;

				// Point right hand at door hinge, curl hand towards closest spot on door, if thumb
				// is up, open door CW.  -- Department of Basic Cross Product Understanding for Noobs
				Vector cross = activatorToOrigin.Cross( activatorToNearestPoint );

				if( cross.z > 0.0f )
				{
					sign = -1.0f;	
				}
			}
		}
		AngularMove(m_vecAngle2*sign, m_flSpeed);
	}
	else
	{
		LinearMove(m_vecPosition2, m_flSpeed);
	}

	//Fire our open ouput
	m_OnOpen.FireOutput( this, this );
}