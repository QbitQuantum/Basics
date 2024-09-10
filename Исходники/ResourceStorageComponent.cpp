float ResourceStorageComponent::GetStoredFraction() {
	// TODO: Add TeamComponent and/or Utility::Team.
	team_t team = entity.oldEnt->buildableTeam;

	if (!level.team[team].acquiredBuildPoints) return 1.0f;

	// The stored fraction is equal to the acquired fraction.
	float storedFraction = acquiredBuildPoints / level.team[team].acquiredBuildPoints;

	if (storedFraction < 0.0f || storedFraction > 1.0f + LINE_DISTANCE_EPSILON) {
		resourceStorageLogger.Warn(
			"A resource storage stores an invalid fraction of all build points: %.1f", storedFraction
		);
	}

	return storedFraction;
}