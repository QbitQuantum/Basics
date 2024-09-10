CLightningProjectile::CLightningProjectile(
		const float3& pos, const float3& end,
		CUnit* owner,
		const float3& color,
		const WeaponDef* weaponDef,
		int ttl, CWeapon* weap)
	: CWeaponProjectile(pos, ZeroVector, owner, NULL, ZeroVector, weaponDef, NULL, ttl)
	, color(color)
	, endPos(end)
	, weapon(weap)
{
	projectileType = WEAPON_LIGHTNING_PROJECTILE;
	checkCol = false;
	drawRadius = pos.distance(endPos);

	displacements[0] = 0.0f;
	for (size_t d = 1; d < displacements_size; ++d) {
		displacements[d]  = (gs->randFloat() - 0.5f) * drawRadius * 0.05f;
	}

	displacements2[0] = 0.0f;
	for (size_t d = 1; d < displacements_size; ++d) {
		displacements2[d] = (gs->randFloat() - 0.5f) * drawRadius * 0.05f;
	}

	if (weapon) {
		AddDeathDependence(weapon);
	}

#ifdef TRACE_SYNC
	tracefile << "New lightning: ";
	tracefile << pos.x << " " << pos.y << " " << pos.z << " " << end.x << " " << end.y << " " << end.z << "\n";
#endif

	cegID = gCEG->Load(explGenHandler, cegTag);
}