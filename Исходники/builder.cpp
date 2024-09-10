bool CBuilder::StartBuild(BuildInfo& buildInfo, CFeature*& feature, bool& waitStance)
{
	StopBuild(false);
	TempHoldFire(-1);

	buildInfo.pos = CGameHelper::Pos2BuildPos(buildInfo, true);

	// Pass -1 as allyteam to behave like we have maphack.
	// This is needed to prevent building on top of cloaked stuff.
	const CGameHelper::BuildSquareStatus tbs = CGameHelper::TestUnitBuildSquare(buildInfo, feature, -1, true);

	switch (tbs) {
		case CGameHelper::BUILDSQUARE_OPEN:
			break;

		case CGameHelper::BUILDSQUARE_BLOCKED:
		case CGameHelper::BUILDSQUARE_OCCUPIED: {
			// the ground is blocked at the position we want
			// to build at; check if the blocking object is
			// of the same type as our buildee (which means
			// another builder has already started it)
			// note: even if construction has already started,
			// the buildee is *not* guaranteed to be the unit
			// closest to us
			CSolidObject* o = groundBlockingObjectMap->GroundBlocked(buildInfo.pos);
			CUnit* u = NULL;

			if (o != NULL) {
				u = dynamic_cast<CUnit*>(o);
			} else {
				// <pos> might map to a non-blocking portion
				// of the buildee's yardmap, fallback check
				u = CGameHelper::GetClosestFriendlyUnit(NULL, buildInfo.pos, buildDistance, allyteam);
			}

			if (u != NULL && CanAssistUnit(u, buildInfo.def)) {
				curBuild = u;
				AddDeathDependence(u, DEPENDENCE_BUILD);
				ScriptStartBuilding(u->pos, false);
				return true;
			}

			return false;
		}

		case CGameHelper::BUILDSQUARE_RECLAIMABLE:
			// caller should handle this
			return false;
	}

	if ((waitStance = !ScriptStartBuilding(buildInfo.pos, true))) {
		return false;
	}

	const UnitDef* buildeeDef = buildInfo.def;
	const UnitLoadParams buildeeParams = {buildeeDef, this, buildInfo.pos, ZeroVector, -1, team, buildInfo.buildFacing, true, false};

	CUnit* buildee = unitLoader->LoadUnit(buildeeParams);

	// floating structures don't terraform the seabed
	const float groundheight = CGround::GetHeightReal(buildee->pos.x, buildee->pos.z);
	const bool onWater = (buildeeDef->floatOnWater && groundheight <= 0.0f);

	if (mapDamage->disabled || !buildeeDef->levelGround || onWater ||
	    buildeeDef->IsAirUnit() || !buildeeDef->IsImmobileUnit()
	) {
		// skip the terraforming job
		buildee->terraformLeft = 0;
		buildee->groundLevelled = true;
	} else {
		tx1 = (int)max(    0.0f, (buildee->pos.x - (buildeeDef->xsize * 0.5f * SQUARE_SIZE)) / SQUARE_SIZE);
		tx2 =      min(gs->mapx,             tx1 +  buildeeDef->xsize                                     );
		tz1 = (int)max(    0.0f, (buildee->pos.z - (buildeeDef->zsize * 0.5f * SQUARE_SIZE)) / SQUARE_SIZE);
		tz2 =      min(gs->mapy,             tz1 +  buildeeDef->zsize                                     );

		buildee->terraformLeft = CalculateBuildTerraformCost(buildInfo);
		buildee->groundLevelled = false;

		terraforming    = true;
		terraformType   = Terraform_Building;
		terraformRadius = (tx2 - tx1) * SQUARE_SIZE;
		terraformCenter = buildee->pos;
	}

	if (!this->unitDef->canBeAssisted) {
		buildee->soloBuilder = this;
		buildee->AddDeathDependence(this, DEPENDENCE_BUILDER);
	}

	AddDeathDependence(buildee, DEPENDENCE_BUILD);
	curBuild = buildee;

	/* The ground isn't going to be terraformed.
	 * When the building is completed, it'll 'pop'
	 * into the correct height for the (un-flattened)
	 * terrain it's on.
	 *
	 * To prevent this visual artifact, put the building
	 * at the 'right' height to begin with.
	 */
	curBuild->moveType->SlowUpdate();
	return true;
}