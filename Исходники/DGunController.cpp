// problems: giving reclaim order on moving target causes commander
// to walk (messing up subsequent dgun order if target still moving)
// and does not take commander torso rotation time into account
//
void CDGunController::TrackAttackTarget(unsigned int currentFrame) {
	if (currentFrame - state.targetSelectionFrame == 5) {
		// five sim-frames have passed since selecting target, attack
		const UnitDef* udef = ai->cb->GetUnitDef(state.targetID);

		const float3 curTargetPos = ai->cb->GetUnitPos(state.targetID);              // current target position
		const float3 commanderPos = ai->cb->GetUnitPos(commanderID);                 // current commander position

		const float3 targetDif    = (commanderPos - curTargetPos);
		const float  targetDist   = targetDif.Length();                              // distance to target
		const float3 targetVel    = (curTargetPos - state.oldTargetPos);

		float3 targetMoveDir   = targetVel;
		float  targetMoveSpeed = 0.0f;

		if (targetVel != ZeroVector) {
			targetMoveSpeed = targetVel.Length() / 5.0f;                             // target speed per sim-frame during tracking interval
			targetMoveDir   = targetVel / (targetMoveSpeed * 5.0f);                  // target direction of movement
		}

		const float  dgunDelay    = targetDist / commanderWD->projectilespeed;       // sim-frames needed for dgun to reach target position
		const float3 leadPos      = targetMoveDir * (targetMoveSpeed * dgunDelay);
		const float3 dgunPos      = curTargetPos + leadPos;                          // position where target will be in <dgunDelay> frames
		const float  maxRange     = ai->cb->GetUnitMaxRange(commanderID);

		bool haveClearShot = true;
		int orderType = -1;

		AIHCTraceRay rayData = {
			commanderPos,
			targetDif / targetDist, // direction
			maxRange,
			commanderID,
			-1,
			0
		};

		ai->cb->HandleCommand(AIHCTraceRayId, &rayData);

		if (rayData.hitUID != -1) {
			// note: still fails when allied structure is between us and enemy
			// can also fail if enemy is in front of allied structure and both
			// are within the d-gun's range
			haveClearShot = (ai->cb->GetUnitAllyTeam(rayData.hitUID) != ai->cb->GetMyAllyTeam());

			// TODO: get DGun weapon properties & check if it can pass through
			// a unit, if yes then allow executing the code below
			if(haveClearShot) {
				// check if there is a unit next to hit unit on DGun path...
				const float3 enemyPos = ai->cb->GetUnitPos(rayData.hitUID);
				const float segmentLeft = maxRange - commanderPos.distance(enemyPos);

				if(segmentLeft > 0.0) {
					AIHCTraceRay rayData2 = {
						enemyPos,
						targetDif / targetDist,
						segmentLeft,
						rayData.hitUID,
						-1,
						0
					};

					ai->cb->HandleCommand(AIHCTraceRayId, &rayData2);

					if(rayData2.hitUID != -1) {
						haveClearShot = (ai->cb->GetUnitAllyTeam(rayData2.hitUID) != ai->cb->GetMyAllyTeam());
					}
				}
			}
		}

		// multiply by 0.9 to ensure commander does not have to walk
		if ((commanderPos - dgunPos).Length() < maxRange * 0.9f) {
			bool canDGun =
				(ai->cb->GetEnergy() >= DGUN_MIN_ENERGY_LEVEL)
				&& haveClearShot
				&& (udef != NULL && !udef->weapons.empty());

			if(canDGun) {
				IssueOrder(dgunPos, orderType = CMD_DGUN, 0);
			} else {
				bool bDanger = ai->tm->ThreatAtThisPoint(commanderPos/*curTargetPos*/) > ai->tm->GetAverageThreat();
				if(bDanger) {
					state.Reset(currentFrame, true);
				} else {
					if (ai->cb->GetUnitHealth(state.targetID) < ai->cb->GetUnitMaxHealth(state.targetID) * 0.5f) {
						IssueOrder(state.targetID, orderType = CMD_RECLAIM, 0);
					} else {
						IssueOrder(state.targetID, orderType = CMD_CAPTURE, 0);
					}
				}
			}

			if (orderType == CMD_DGUN   ) { state.dgunOrderFrame    = ai->cb->GetCurrentFrame(); }
			if (orderType == CMD_RECLAIM) { state.reclaimOrderFrame = ai->cb->GetCurrentFrame(); }
			if (orderType == CMD_CAPTURE) { state.captureOrderFrame = ai->cb->GetCurrentFrame(); }
		} else {
			state.Reset(currentFrame, true);
		}
	}

	state.Reset(currentFrame, false);
}