bool CASW_Shieldbug::BlockedDamage( const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr )
{
// 	if (IsMeleeAttacking())
// 	{
// 		if (asw_debug_shieldbug.GetBool())
// 			Msg("Not blocking as I'm meleeing\n");
// 		return false;
// 	}

	if ( ptr->hitgroup == HITGROUP_BONE_SHIELD )
		return true;

#if 0
	Vector sparkNormal;
	Vector vecDamagePos = info.GetDamagePosition();
	if ( info.GetAttacker() && vecDamagePos != vec3_origin )
	{
		vecDamagePos = info.GetAttacker()->GetAbsOrigin();	// use the attacker's position when determining block, to stop marines shooting through gaps and hurting the sbug from any angle
	}

	if ( vecDamagePos == vec3_origin )		// don't block non-locational damage (i.e. fire burning)
		return false;

	// if we're in the middle of meleeing, don't block damage
	if ( IsMeleeAttacking() )
	{
#ifdef GAME_DLL
		if ( asw_debug_shieldbug.GetBool() )
		{
			Msg( "Not blocking as I'm meleeing\n" );
		}
#endif
		return false;
	}

	sparkNormal = vecDamagePos - GetAbsOrigin();	// should be head pos
	VectorNormalize( sparkNormal );
	Vector vecFacing;
	AngleVectors( GetAbsAngles(), &vecFacing );
	vecFacing.z = 0;
	VectorNormalize( vecFacing );
	sparkNormal.z = 0;
	VectorNormalize( sparkNormal );
	float dot = vecFacing.Dot( sparkNormal );

#ifdef GAME_DLL
	if ( asw_debug_shieldbug.GetBool() )
	{
		Msg("Defending dot %f\n", dot);
	}
	if (dot > 0)
	{
		if ( asw_debug_shieldbug.GetBool() )
		{
			Msg( "  blocked damage\n" );
		}
		return true;
	}
	if ( asw_debug_shieldbug.GetBool() )
	{
		Msg( "  Not blocked dmg\n" );
	}
#else
	if ( dot > 0 )
	{
		return true;
	}
#endif

#endif
	return false;
}