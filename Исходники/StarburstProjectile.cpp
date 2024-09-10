CStarburstProjectile::CStarburstProjectile(const ProjectileParams& params,
        float areaOfEffect, float maxSpeed, float tracking, int uptime, float maxRange, float3 aimError)
    : CWeaponProjectile(params)
    , tracking(tracking)
    , maxSpeed(maxSpeed)
    , acceleration(0.f)
    , areaOfEffect(areaOfEffect)
    , age(0)
    , oldSmoke(pos)
    , aimError(aimError)
    , drawTrail(true)
    , numParts(0)
    , doturn(true)
    , curCallback(NULL)
    , missileAge(0)
    , distanceToTravel(maxRange)
    , curTracerPart(0)
{
    projectileType = WEAPON_STARBURST_PROJECTILE;
    this->uptime = uptime;

    if (weaponDef) {
        if (weaponDef->flighttime == 0) {
            ttl = (int) std::min(3000.0f, uptime + weaponDef->range / maxSpeed + 100);
        } else {
            ttl = weaponDef->flighttime;
        }
    }

    maxGoodDif = math::cos(tracking * 0.6f);
    curSpeed = speed.Length();
    dir = speed / curSpeed;
    oldSmokeDir = dir;

    const float3 camDir = (pos - camera->pos).ANormalize();
    const float camDist = (camera->pos.distance(pos) * 0.2f) + ((1.0f - math::fabs(camDir.dot(dir))) * 3000);

    drawTrail = (camDist >= 200.0f);
    drawRadius = maxSpeed * 8.0f;

    for (int a = 0; a < NUM_TRACER_PARTS; ++a) {
        tracerParts[a].dir = dir;
        tracerParts[a].pos = pos;
        tracerParts[a].speedf = curSpeed;

        tracerParts[a].ageMods.resize(std::floor((curSpeed + 0.6f) / TRACER_PARTS_STEP), 1.0f);
    }
    castShadow = true;

#ifdef TRACE_SYNC
    tracefile << "[" << __FUNCTION__ << "] ";
    tracefile << pos.x << " " << pos.y << " " << pos.z << " " << speed.x << " " << speed.y << " " << speed.z << "\n";
#endif

    cegID = gCEG->Load(explGenHandler, (weaponDef != NULL)? weaponDef->cegTag: "");
}