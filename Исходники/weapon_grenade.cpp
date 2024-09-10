//-----------------------------------------------------------------------------
// Purpose: Throw a primed grenade with timeleft of (gpGlobals->curtime - m_flPrimedTime)
//-----------------------------------------------------------------------------
void CGEWeaponGrenade::ThrowGrenade( float throwforce )
{
	CBaseCombatCharacter *pOwner = GetOwner();
	if ( !pOwner )
		return;

	// Remove the grenade from our ammo pool
	pOwner->RemoveAmmo( 1, m_iPrimaryAmmoType );

#ifndef CLIENT_DLL
	Vector	vecEye = pOwner->EyePosition();

	Vector	vForward, vRight;
	AngleVectors( pOwner->EyeAngles(), &vForward, &vRight, NULL );

	Vector vecSrc = vecEye + vForward * 18.0f + vRight * 8.0f;
	CheckThrowPosition( vecEye, vecSrc );
	vForward[2] += 0.1f;

	Vector vecThrow;
	pOwner->GetVelocity( &vecThrow, NULL );
	vecThrow += vForward * throwforce;

	// Convert us into a bot player :-D
	if ( pOwner->IsNPC() )
	{
		CNPC_GEBase *pNPC = (CNPC_GEBase*) pOwner;
		if ( pNPC->GetBotPlayer() )
			pOwner = pNPC->GetBotPlayer();
	}

	CGEGrenade *pGrenade = (CGEGrenade *)CBaseEntity::Create( "npc_grenade", vecSrc, vec3_angle, NULL );

	if ( pGrenade )
	{
		pGrenade->SetThrower( pOwner );
		pGrenade->SetOwnerEntity( pOwner );
		pGrenade->SetVelocity( vecThrow, AngularImpulse(600,random->RandomInt(-1000,1000),0) );

		pGrenade->SetDamage( GetGEWpnData().m_iDamage );
		pGrenade->SetDamageRadius( GetGEWpnData().m_flDamageRadius );
		pGrenade->SetSourceWeapon(this);
		
		if (throwforce == GE_GRENADE_THROW_FORCE / 5) // For acheivement tracking.
			pGrenade->m_bDroppedOnDeath = true;

		// The timer is whatever is left over from the primed time + our fuse minus our 
		// current time to give us an absolute time in seconds
		pGrenade->SetTimer( (m_flPrimedTime + GE_GRENADE_FUSE_TIME) - gpGlobals->curtime );

		// Tell the owner what we threw to implement anti-spamming
		if ( pOwner->IsPlayer() )
			ToGEMPPlayer(pOwner)->AddThrownObject( pGrenade );
	}
#endif

	m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();
	m_flTimeWeaponIdle = gpGlobals->curtime + GE_GRENADE_IDLE_DELAY;
	m_bDrawNext = true;

	WeaponSound( SINGLE );
}