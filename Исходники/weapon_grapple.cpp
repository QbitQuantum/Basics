void CGrappleHook::Move( void ) 
{
	// Fograin92: If owner (player) is dead
	if( !myowner->IsAlive() )
	{
		Killed(pev, 0); // Remove tongue instantly
		return;
	}

	// Fograin92: Player isn't holding attack buttons
	if( !(myowner->pev->button & (IN_ATTACK|IN_ATTACK2)) )
	{
		bPullBack = true;	// Fograin92: We should pull the tongue back
	}

	// Fograin92: Animate pull-back tongue animation ONLY if we didn't hit a monster
	if(bPullBack)
	{
		UTIL_MakeVectors( myowner->pev->v_angle + myowner->pev->punchangle ); 
		Vector GunPosition = myowner->GetGunPosition();
		GunPosition = GunPosition + gpGlobals->v_up * -4 + gpGlobals->v_right * 3 + gpGlobals->v_forward * 6;

		pev->velocity = (GunPosition - pev->origin) * 10;	// Pull back the tongue tip
		float fDistance = (GunPosition - pev->origin).Length2D();	// Calculate distance between tongue tip and player
		//ALERT( at_console, "^2HLU -> ^3weapon_grapple ^2-> %f\n", fDistance );

		if (fDistance < 40)
		{
			Killed(pev, 0);
			return;
		}
		
	}
	else
	{
		// Fograin92: We did hit a monster
		if(m_iHitMonster > 0)
		{
			// Fograin92: Let's "stick" grapple tongue XYZ to target's center XYZ
			pev->origin = myHitMonster->Center();

			// Fograin92: We did hit tiny monster, let's pull it
			if(m_iHitMonster == 2)
			{
				myHitMonster->pev->movetype = MOVETYPE_FLY;	// Remove gravity effect on our pulled monster
				myHitMonster->pev->velocity = (myowner->pev->origin - myHitMonster->pev->origin) * 4;	// Pull our monster
			}

			// Fograin92: Check distance (player <-> monster)
			float fDistance = (myowner->pev->origin - myHitMonster->pev->origin).Length2D();

			// Fograin92: The monster is very close to player, let's OWN IT!
			if (fDistance < 40)
			{
				ALERT( at_console, "^2HLU -> ^3weapon_grapple ^2-> OWNED -> ^3%s\n", STRING(myHitMonster->pev->classname) );

				// Fograin92: Did we pull the gib?
				if( myHitMonster->Classify() == CLASS_GIBS )
					myHitMonster->SUB_Remove();
				else 
					myHitMonster->TakeDamage(myHitMonster->pev, myowner->pev, 10000, DMG_GENERIC);

				Killed(pev, 0);	// Fograin92: Target died, kill tongue
			}

		}
	}

	// Fograin92: If tongue (beam) exists
	if( m_pTongue )
	{
		UTIL_MakeVectors( myowner->pev->v_angle + myowner->pev->punchangle ); 
		Vector GunPosition = myowner->GetGunPosition();
		GunPosition = GunPosition + gpGlobals->v_up * -4 + gpGlobals->v_right * 3 + gpGlobals->v_forward * 6;

		m_pTongue->PointEntInit( GunPosition, this->entindex() );
	}
	else
	{
		// Fograin92: Create tongue (beam)
		m_pTongue = CBeam::BeamCreate( "sprites/_tongue.spr", 8 );
		m_pTongue->SetFlags( 0x20 );	// Solid beam
		m_pTongue->SetColor( 100, 100, 100 );
		m_pTongue->SetScrollRate( 20 );
	}

	pev->nextthink = gpGlobals->time + 0.01;
}