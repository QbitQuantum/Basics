// TODO: Move this to the client side.
void AlienBuildableComponent::CreepRecede(int timeDelta) {
	alienBuildableLogger.Debug("Starting creep recede.");

	G_AddEvent(entity.oldEnt, EV_BUILD_DESTROY, 0);

	if (entity.oldEnt->spawned) {
		entity.oldEnt->s.time = -level.time;
	} else {
		entity.oldEnt->s.time = -(level.time - (int)(
			(float)CREEP_SCALEDOWN_TIME *
			(1.0f - ((float)(level.time - entity.oldEnt->creationTime) /
					 (float)BG_Buildable(entity.oldEnt->s.modelindex)->buildTime)))
		);
	}

	// Remove buildable when done.
	GetBuildableComponent().REGISTER_THINKER(Remove, ThinkingComponent::SCHEDULER_AFTER, CREEP_SCALEDOWN_TIME);
	GetBuildableComponent().GetThinkingComponent().UnregisterActiveThinker();
}