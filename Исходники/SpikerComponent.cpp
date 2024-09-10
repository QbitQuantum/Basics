bool SpikerComponent::Fire() {
	gentity_t *self = entity.oldEnt;
	// Check if still resting.
	if (restUntil > level.time) {
		logger.Verbose("Spiker #%i wanted to fire but wasn't ready.", entity.oldEnt->s.number);

		return false;
	} else {
		logger.Verbose("Spiker #%i is firing!", entity.oldEnt->s.number);
	}

	// Play shooting animation.
	G_SetBuildableAnim(self, BANIM_ATTACK1, false);
	GetBuildableComponent().ProtectAnimation(5000);

	// TODO: Add a particle effect.
	//G_AddEvent(self, EV_ALIEN_SPIKER, DirToByte(self->s.origin2));

	// Calculate total perimeter of all spike rows to allow for a more even spike distribution.
	// A "row" is a group of missile launch directions with a common base altitude (angle measured
	// from the Spiker's horizon to its zenith) which is slightly adjusted for each new missile in
	// the row (at most halfway to the base altitude of a neighbouring row).
	float totalPerimeter = 0.0f;
	for (int row = 0; row < MISSILEROWS; row++) {
		float rowAltitude = (((float)row + 0.5f) * M_PI_2) / (float)MISSILEROWS;
		float rowPerimeter = 2.0f * M_PI * cos(rowAltitude);
		totalPerimeter += rowPerimeter;
	}

	// TODO: Use new vector library.
	vec3_t dir, zenith, rotAxis;

	// As rotation axis for setting the altitude, any vector perpendicular to the zenith works.
	VectorCopy(self->s.origin2, zenith);
	PerpendicularVector(rotAxis, zenith);

	// Distribute and launch missiles.
	for (int row = 0; row < MISSILEROWS; row++) {
		// Set the base altitude and get the perimeter for the current row.
		float rowAltitude = (((float)row + 0.5f) * M_PI_2) / (float)MISSILEROWS;
		float rowPerimeter = 2.0f * M_PI * cos(rowAltitude);

		// Attempt to distribute spikes with equal expected angular distance on all rows.
		int spikes = (int)round(((float)MISSILES * rowPerimeter) / totalPerimeter);

		// Launch missiles in the current row.
		for (int spike = 0; spike < spikes; spike++) {
			float spikeAltitude = rowAltitude + (0.5f * crandom() * M_PI_2 / (float)MISSILEROWS);
			float spikeAzimuth = 2.0f * M_PI * (((float)spike + 0.5f * crandom()) / (float)spikes);

			// Set launch direction altitude.
			RotatePointAroundVector(dir, rotAxis, zenith, RAD2DEG(M_PI_2 - spikeAltitude));

			// Set launch direction azimuth.
			RotatePointAroundVector(dir, zenith, dir, RAD2DEG(spikeAzimuth));

			// Trace in the shooting direction and do not shoot spikes that are likely to harm
			// friendly entities.
			bool fire = SafeToShoot(Vec3::Load(dir));

			logger.Debug("Spiker #%d %s: Row %d/%d: Spike %2d/%2d: "
				"( Alt %2.0f°, Az %3.0f° → %.2f, %.2f, %.2f )", self->s.number,
				fire ? "fires" : "skips", row + 1, MISSILEROWS, spike + 1, spikes,
				RAD2DEG(spikeAltitude), RAD2DEG(spikeAzimuth), dir[0], dir[1], dir[2]);

			if (!fire) {
				continue;
			}

			G_SpawnMissile(
				MIS_SPIKER, self, self->s.origin, dir, nullptr, G_FreeEntity,
				level.time + (int)(1000.0f * SPIKE_RANGE / (float)BG_Missile(MIS_SPIKER)->speed));
		}
	}

	restUntil = level.time + COOLDOWN;
	RegisterSlowThinker();

	return true;
}