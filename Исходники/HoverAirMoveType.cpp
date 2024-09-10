bool CHoverAirMoveType::Update()
{
	const float3 lastPos = owner->pos;
	const float4 lastSpd = owner->speed;

	AAirMoveType::Update();

	if ((owner->IsStunned() && !owner->IsCrashing()) || owner->beingBuilt) {
		wantedSpeed = ZeroVector;

		UpdateAirPhysics();
		return (HandleCollisions(collide && !owner->beingBuilt && (padStatus == PAD_STATUS_FLYING) && (aircraftState != AIRCRAFT_TAKEOFF)));
	}

	// allow us to stop if wanted (changes aircraft state)
	if (wantToStop)
		ExecuteStop();

	if (aircraftState != AIRCRAFT_CRASHING) {
		if (owner->fpsControlPlayer != NULL) {
			SetState(AIRCRAFT_FLYING);

			const FPSUnitController& con = owner->fpsControlPlayer->fpsController;

			const float3 forward = con.viewDir;
			const float3 right = forward.cross(UpVector);
			const float3 nextPos = lastPos + owner->speed;

			float3 flatForward = forward;
			flatForward.Normalize2D();

			wantedSpeed = ZeroVector;

			if (con.forward) wantedSpeed += flatForward;
			if (con.back   ) wantedSpeed -= flatForward;
			if (con.right  ) wantedSpeed += right;
			if (con.left   ) wantedSpeed -= right;

			wantedSpeed.Normalize();
			wantedSpeed *= maxSpeed;

			if (!nextPos.IsInBounds()) {
				owner->SetVelocityAndSpeed(ZeroVector);
			}

			UpdateAirPhysics();
			wantedHeading = GetHeadingFromVector(flatForward.x, flatForward.z);
		}

		if (reservedPad != NULL) {
			MoveToRepairPad();

			if (padStatus >= PAD_STATUS_LANDING) {
				flyState = FLY_LANDING;
			}
		}
	}

	switch (aircraftState) {
		case AIRCRAFT_LANDED:
			UpdateLanded();
			break;
		case AIRCRAFT_TAKEOFF:
			UpdateTakeoff();
			break;
		case AIRCRAFT_FLYING:
			UpdateFlying();
			break;
		case AIRCRAFT_LANDING:
			UpdateLanding();
			break;
		case AIRCRAFT_HOVERING:
			UpdateHovering();
			break;
		case AIRCRAFT_CRASHING: {
			UpdateAirPhysics();

			if ((ground->GetHeightAboveWater(owner->pos.x, owner->pos.z) + 5.0f + owner->radius) > owner->pos.y) {
				owner->ClearPhysicalStateBit(CSolidObject::PSTATE_BIT_CRASHING);
				owner->KillUnit(NULL, true, false);
			} else {
				#define SPIN_DIR(o) ((o->id & 1) * 2 - 1)
				wantedHeading = GetHeadingFromVector(owner->rightdir.x * SPIN_DIR(owner), owner->rightdir.z * SPIN_DIR(owner));
				wantedHeight = 0.0f;
				#undef SPIN_DIR
			}

			new CSmokeProjectile(owner->midPos, gs->randVector() * 0.08f, 100 + gs->randFloat() * 50, 5, 0.2f, owner, 0.4f);
		} break;
	}

	if (lastSpd == ZeroVector && owner->speed != ZeroVector) { owner->script->StartMoving(false); }
	if (lastSpd != ZeroVector && owner->speed == ZeroVector) { owner->script->StopMoving(); }

	// Banking requires deltaSpeed.y = 0
	deltaSpeed = owner->speed - lastSpd;
	deltaSpeed.y = 0.0f;

	// Turn and bank and move; update dirs
	UpdateHeading();
	UpdateBanking(aircraftState == AIRCRAFT_HOVERING);

	return (HandleCollisions(collide && !owner->beingBuilt && (padStatus == PAD_STATUS_FLYING) && (aircraftState != AIRCRAFT_TAKEOFF)));
}