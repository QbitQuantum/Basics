Entity* TurretComponent::FindEntityTarget(std::function<bool(Entity&, Entity&)> CompareTargets) {
	// Delete old target.
	RemoveTarget();

	// Search best target.
	// TODO: Iterate over all valid targets, do not assume they have to be clients.
	ForEntities<ClientComponent>([&](Entity& candidate, ClientComponent& clientComponent) {
		if (TargetValid(candidate, true)) {
			if (!target || CompareTargets(candidate, *target->entity)) {
				target = candidate.oldEnt;
			}
		}
	});

	if (target) {
		// TODO: Increase tracked-by counter for a new target.

		turretLogger.Verbose("Target acquired.");
	}

	return target ? target->entity : nullptr;
}