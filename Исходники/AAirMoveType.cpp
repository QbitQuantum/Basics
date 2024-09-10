bool AAirMoveType::CanLandOnPad(const float3& padPos) const {
	// once distance to pad becomes smaller than current braking distance, switch states
	// (but do not allow state-switch until the aircraft is heading ~directly toward pad)
	// braking distance is 0.5*a*t*t where t is v/a --> 0.5*a*((v*v)/(a*a)) --> 0.5*v*v*(1/a)
	// FIXME:
	//   apply N-frame lookahead when deciding to switch state for strafing aircraft
	//   (see comments in StrafeAirMoveType::UpdateLanding, overshooting prevention)
	//   the lookahead is roughly based on the time to descend to pad-target altitude
	const float3 flatFrontDir = (float3(owner->frontdir)).Normalize2D();

	const float brakingDistSq = Square(0.5f * owner->speed.SqLength2D() / decRate);
	const float descendDistSq = Square(maxSpeed * ((owner->pos.y - padPos.y) / altitudeRate)) * owner->unitDef->IsStrafingAirUnit();

	if (padPos.SqDistance2D(owner->pos) > std::max(brakingDistSq, descendDistSq))
		return false;

	if (owner->unitDef->IsStrafingAirUnit()) {
		// horizontal guide
		if (flatFrontDir.dot((padPos - owner->pos).SafeNormalize2D()) < 0.985f)
			return false;
		// vertical guide
		if (flatFrontDir.dot((padPos - owner->pos).SafeNormalize()) < 0.707f)
			return false;
	}

	return true;
}