void CGEPropDynamic::Materialize(void)
{
	//A more lightweight and optional func_rebreakable materalize function 
	CreateVPhysics();

	if (m_bRobustSpawn)
	{
		// iterate on all entities in the vicinity.
		CBaseEntity *pEntity;
		Vector max = CollisionProp()->OBBMaxs();
		for (CEntitySphereQuery sphere(GetAbsOrigin(), max.NormalizeInPlace()); (pEntity = sphere.GetCurrentEntity()) != NULL; sphere.NextEntity())
		{
			if (pEntity == this || pEntity->GetSolid() == SOLID_NONE || pEntity->GetSolid() == SOLID_BSP || pEntity->GetSolidFlags() & FSOLID_NOT_SOLID || pEntity->GetMoveType() & MOVETYPE_NONE)
				continue;

			// Ignore props that can't move
			if (pEntity->VPhysicsGetObject() && !pEntity->VPhysicsGetObject()->IsMoveable())
				continue;

			// Prevent respawn if we are blocked by anything and try again in 1 second
			if (Intersects(pEntity))
			{
				SetSolid(SOLID_NONE);
				AddSolidFlags(FSOLID_NOT_SOLID);
				VPhysicsDestroyObject();
				SetNextThink(gpGlobals->curtime + 1.0f);
				return;
			}
		}
	}

	m_iHealth = m_iHealthOverride;

	if (m_iHealth > 0)
		m_takedamage = DAMAGE_YES;

	RemoveEffects(EF_NODRAW);
	RemoveSolidFlags(FSOLID_NOT_SOLID);

	m_bUsingBrokenSkin = false;

	if (m_bUseRandomSkins)
		PickNewSkin();
	else
		m_nSkin = m_iStartingSkin;

	SetRenderColor(m_col32basecolor.r, m_col32basecolor.g, m_col32basecolor.b);

	m_Respawn.FireOutput(this, this);
}