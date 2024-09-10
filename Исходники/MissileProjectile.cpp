CMissileProjectile::CMissileProjectile(
		const float3& pos, const float3& speed,
		CUnit* owner,
		float areaOfEffect, float maxSpeed, int ttl,
		CUnit* target, const WeaponDef* weaponDef,
		float3 targetPos)
	: CWeaponProjectile(pos, speed, owner, target, targetPos, weaponDef, NULL, ttl)
	, maxSpeed(maxSpeed)
	, areaOfEffect(areaOfEffect)
	, age(0)
	, oldSmoke(pos)
	, target(target)
	, decoyTarget(NULL)
	, drawTrail(true)
	, numParts(0)
	, targPos(targetPos)
	, isWobbling(weaponDef? (weaponDef->wobble > 0): false)
	, wobbleDir(ZeroVector)
	, wobbleTime(1)
	, wobbleDif(ZeroVector)
	, isDancing(weaponDef? (weaponDef->dance > 0): false)
	, danceTime(1)
	, danceMove(ZeroVector)
	, danceCenter(ZeroVector)
	, extraHeightTime(0)
{
	projectileType = WEAPON_MISSILE_PROJECTILE;
	curSpeed = speed.Length();
	dir = speed / curSpeed;
	oldDir = dir;

	if (target) {
		AddDeathDependence(target);
	}

	SetRadius(0.0f);

	if (weaponDef) {
		model = LoadModel(weaponDef);
		if (model) {
			SetRadius(model->radius);
		}
	}

	drawRadius = radius + maxSpeed * 8;

	float3 camDir = (pos - camera->pos).Normalize();
	if ((camera->pos.distance(pos) * 0.2f + (1 - fabs(camDir.dot(dir))) * 3000) < 200) {
		drawTrail = false;
	}

	castShadow = true;

#ifdef TRACE_SYNC
	tracefile << "New missile: ";
	tracefile << pos.x << " " << pos.y << " " << pos.z << " " << speed.x << " " << speed.y << " " << speed.z << "\n";
#endif

	if (target) {
		target->IncomingMissile(this);
	}

	if ((weaponDef) && (weaponDef->trajectoryHeight > 0)) {
		float dist = pos.distance(targPos);
		extraHeight = (dist * weaponDef->trajectoryHeight);

		if (dist < maxSpeed) {
			dist = maxSpeed;
		}

		extraHeightTime = (int)(dist / maxSpeed);
		extraHeightDecay = extraHeight / extraHeightTime;
	}


	cegID = gCEG->Load(explGenHandler, cegTag);
}