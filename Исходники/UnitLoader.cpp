void CUnitLoader::GiveUnits(const std::string& objectName, float3 pos, int amount, int team, int featureAllyTeam)
{
    const CTeam* receivingTeam = teamHandler->Team(team);

    if (objectName == "all") {
        unsigned int numRequestedUnits = unitDefHandler->unitDefs.size() - 1; /// defid=0 is not valid
        unsigned int currentNumUnits = receivingTeam->units.size();

        // make sure team unit-limit is not exceeded
        if ((currentNumUnits + numRequestedUnits) > receivingTeam->maxUnits) {
            numRequestedUnits = receivingTeam->maxUnits - currentNumUnits;
        }

        // make sure square is entirely on the map
        const int sqSize = math::ceil(math::sqrt((float) numRequestedUnits));
        const float sqHalfMapSize = sqSize / 2 * 10 * SQUARE_SIZE;

        pos.x = std::max(sqHalfMapSize, std::min(pos.x, float3::maxxpos - sqHalfMapSize - 1));
        pos.z = std::max(sqHalfMapSize, std::min(pos.z, float3::maxzpos - sqHalfMapSize - 1));

        for (int a = 1; a <= numRequestedUnits; ++a) {
            Watchdog::ClearPrimaryTimers(); // the other thread may be waiting for a mutex held by this one, triggering hang detection
            const float px = pos.x + (a % sqSize - sqSize / 2) * 10 * SQUARE_SIZE;
            const float pz = pos.z + (a / sqSize - sqSize / 2) * 10 * SQUARE_SIZE;
            const float3 unitPos = float3(px, ground->GetHeightReal(px, pz), pz);
            const UnitDef* unitDef = unitDefHandler->GetUnitDefByID(a);

            if (unitDef != NULL) {
                const CUnit* unit = LoadUnit(unitDef, unitPos, team, false, 0, NULL);

                if (unit != NULL) {
                    FlattenGround(unit);
                }
            }
        }
    } else {
        unsigned int numRequestedUnits = amount;
        unsigned int currentNumUnits = receivingTeam->units.size();

        if (receivingTeam->AtUnitLimit()) {
            LOG_L(L_WARNING,
                  "[%s] unable to give more units to team %d (current: %u, team limit: %u, global limit: %u)",
                  __FUNCTION__, team, currentNumUnits, receivingTeam->maxUnits, uh->MaxUnits()
                 );
            return;
        }

        // make sure team unit-limit is not exceeded
        if ((currentNumUnits + numRequestedUnits) > receivingTeam->maxUnits) {
            numRequestedUnits = receivingTeam->maxUnits - currentNumUnits;
        }

        const UnitDef* unitDef = unitDefHandler->GetUnitDefByName(objectName);
        const FeatureDef* featureDef = featureHandler->GetFeatureDef(objectName, false);

        if (unitDef == NULL && featureDef == NULL) {
            LOG_L(L_WARNING, "[%s] %s is not a valid object-name", __FUNCTION__, objectName.c_str());
            return;
        }

        if (unitDef != NULL) {
            const int xsize = unitDef->xsize;
            const int zsize = unitDef->zsize;
            const int squareSize = math::ceil(math::sqrt((float) numRequestedUnits));
            const float3 squarePos = float3(
                                         pos.x - (((squareSize - 1) * xsize * SQUARE_SIZE) / 2),
                                         pos.y,
                                         pos.z - (((squareSize - 1) * zsize * SQUARE_SIZE) / 2)
                                     );

            int total = numRequestedUnits;

            for (int z = 0; z < squareSize; ++z) {
                for (int x = 0; x < squareSize && total > 0; ++x) {
                    const float px = squarePos.x + x * xsize * SQUARE_SIZE;
                    const float pz = squarePos.z + z * zsize * SQUARE_SIZE;

                    const float3 unitPos = float3(px, ground->GetHeightReal(px, pz), pz);
                    Watchdog::ClearPrimaryTimers();
                    const CUnit* unit = LoadUnit(unitDef, unitPos, team, false, 0, NULL);

                    if (unit != NULL) {
                        FlattenGround(unit);
                    }

                    --total;
                }
            }

            LOG("[%s] spawned %i %s unit(s) for team %i",
                __FUNCTION__, numRequestedUnits, objectName.c_str(), team);
        }

        if (featureDef != NULL) {
            if (featureAllyTeam < 0) {
                team = -1; // default to world features
            }

            const int xsize = featureDef->xsize;
            const int zsize = featureDef->zsize;
            const int squareSize = math::ceil(math::sqrt((float) numRequestedUnits));
            const float3 squarePos = float3(
                                         pos.x - (((squareSize - 1) * xsize * SQUARE_SIZE) / 2),
                                         pos.y,
                                         pos.z - (((squareSize - 1) * zsize * SQUARE_SIZE) / 2)
                                     );

            int total = amount; // FIXME -- feature count limit?

            for (int z = 0; z < squareSize; ++z) {
                for (int x = 0; x < squareSize && total > 0; ++x) {
                    const float px = squarePos.x + x * xsize * SQUARE_SIZE;
                    const float pz = squarePos.z + z * zsize * SQUARE_SIZE;
                    const float3 featurePos = float3(px, ground->GetHeightReal(px, pz), pz);

                    Watchdog::ClearPrimaryTimers();
                    CFeature* feature = new CFeature();
                    // Initialize() adds the feature to the FeatureHandler -> no memory-leak
                    feature->Initialize(featurePos, featureDef, 0, 0, team, featureAllyTeam, NULL);

                    --total;
                }
            }

            LOG("[%s] spawned %i %s feature(s) for team %i",
                __FUNCTION__, numRequestedUnits, objectName.c_str(), team);
        }
    }
}