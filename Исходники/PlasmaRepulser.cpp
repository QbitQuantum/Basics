void CPlasmaRepulser::NewProjectile(CWeaponProjectile* p)
{
	// PlasmaRepulser instances are created if type == "Shield",
	// but projectiles are removed from incomingProjectiles only
	// if def->interceptor || def->isShield --> dangling pointers
	// due to isShield being a separate tag (in 91.0)
	assert(weaponDef->isShield);

	if (weaponDef->smartShield && p->owner() && teamHandler->AlliedTeams(p->owner()->team, owner->team)) {
		return;
	}

	float3 dir = p->speed;
	if (p->GetTargetPos() != ZeroVector) {
		// assume projectile will travel roughly in the direction of its targetpos
		dir = p->GetTargetPos() - p->pos;
	}

	dir.y = 0.0f;
	dir.SafeNormalize();

	const float3 dif = owner->pos - p->pos;

	if (weaponDef->exteriorShield && (dif.SqLength() < sqRadius)) {
		return;
	}

	const float closeLength = std::max(0.0f, dif.dot(dir));
	const float3 closeVect = dif - dir * closeLength;
	const float closeDist = closeVect.SqLength2D();

	// TODO: this isn't good enough in case shield is mounted on a mobile unit,
	//       and this unit moves relatively fast compared to the projectile.
	// it should probably be: radius + closeLength / |projectile->speed| * |owner->speed|,
	// but this still doesn't solve anything for e.g. teleporting shields.
	if (closeDist < Square(radius * 1.5f)) {
		incomingProjectiles[p->id] = p;
		AddDeathDependence(p, DEPENDENCE_REPULSED);
	}
}