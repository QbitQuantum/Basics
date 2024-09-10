void
RandomMovementGenerator<Creature>::_setRandomLocation(Creature &creature)
{
    float X,Y,Z,z,nx,ny,nz,ori,dist;

    creature.GetHomePosition(X, Y, Z, ori);

    z = creature.GetPositionZ();
    Map const* map = creature.GetBaseMap();

    // For 2D/3D system selection
    //bool is_land_ok  = creature.canWalk();
    //bool is_water_ok = creature.canSwim();
    bool is_air_ok   = creature.canFly();

    for (uint32 i = 0; ; ++i)
    {
        const float angle = (float)rand_norm()*static_cast<float>(M_PI*2);
        const float range = (float)rand_norm()*wander_distance;
        const float distanceX = range * cos(angle);
        const float distanceY = range * sin(angle);

        nx = X + distanceX;
        ny = Y + distanceY;

        // prevent invalid coordinates generation
        Trinity::NormalizeMapCoord(nx);
        Trinity::NormalizeMapCoord(ny);

        dist = (nx - X)*(nx - X) + (ny - Y)*(ny - Y);

        if (i == 5)
        {
            nz = Z;
            break;
        }

        if (is_air_ok) // 3D system above ground and above water (flying mode)
        {
            const float distanceZ = (float)(rand_norm()) * sqrtf(dist)/2; // Limit height change
            nz = Z + distanceZ;
            float tz = map->GetHeight(nx, ny, nz-2.0f, false); // Map check only, vmap needed here but need to alter vmaps checks for height.
            float wz = map->GetWaterLevel(nx, ny);
            if (tz >= nz || wz >= nz)
                continue; // Problem here, we must fly above the ground and water, not under. Let's try on next tick
        }
        //else if (is_water_ok) // 3D system under water and above ground (swimming mode)
        else // 2D only
        {
            dist = dist >= 100.0f ? 10.0f : sqrtf(dist); // 10.0 is the max that vmap high can check (MAX_CAN_FALL_DISTANCE)

            // The fastest way to get an accurate result 90% of the time.
            // Better result can be obtained like 99% accuracy with a ray light, but the cost is too high and the code is too long.
            nz = map->GetHeight(nx,ny,Z+dist-2.0f,false); // Map check
            if (fabs(nz-Z)>dist)
            {
                nz = map->GetHeight(nx,ny,Z-2.0f,true); // Vmap Horizontal or above
                if (fabs(nz-Z)>dist)
                {
                    nz = map->GetHeight(nx,ny,Z+dist-2.0f,true); // Vmap Higher
                    if (fabs(nz-Z)>dist)
                        continue; // let's forget this bad coords where a z cannot be find and retry at next tick
                }
            }
        }
        break;
    }

    Traveller<Creature> traveller(creature);
    creature.SetOrientation(creature.GetAngle(nx,ny));
    i_destinationHolder.SetDestination(traveller, nx, ny, nz);
    creature.addUnitState(UNIT_STAT_ROAMING);
    if (is_air_ok)
    {
        i_nextMoveTime.Reset(i_destinationHolder.GetTotalTravelTime());
    }
    //else if (is_water_ok) // Swimming mode to be done with more than this check
    else
    {
        i_nextMoveTime.Reset(urand(500+i_destinationHolder.GetTotalTravelTime(),5000+i_destinationHolder.GetTotalTravelTime()));
        creature.AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
    }

    //Call for creature group update
    if (creature.GetFormation() && creature.GetFormation()->getLeader() == &creature)
    {
        creature.GetFormation()->LeaderMoveTo(nx, ny, nz);
    }
}