void IgnitableComponent::ConsiderSpread(int timeDelta) {
	if (!onFire) return;

	ForEntities<IgnitableComponent>([&](Entity &other, IgnitableComponent &ignitable){
		if (&other == &entity) return;

		// TODO: Use LocationComponent.
		float chance = 1.0f - G_Distance(entity.oldEnt, other.oldEnt) / SPREAD_RADIUS;

		if (chance <= 0.0f) return; // distance > spread radius

		if (random() < chance) {
			if (G_LineOfSight(entity.oldEnt, other.oldEnt) && other.Ignite(fireStarter)) {
				fireLogger.Debug("(Re-)Ignited a neighbour (chance was %.0f%%)", chance * 100.0f);
			} else {
				fireLogger.Debug("Tried to ignite a non-ignitable or non-LOS neighbour (chance was %.0f%%)",
								 chance * 100.0f);
			}
		} else {
			fireLogger.Debug("Didn't try to ignite a neighbour (chance was %.0f%%)", chance * 100.0f);
		}
	});
}