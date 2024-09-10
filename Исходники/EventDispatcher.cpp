void EventDispatcher::run() {
	SimulationConfig& config = state.config();
	discrete_time::Clock& clock = state.clock();
	RandomService<int>* random = ServiceLocator::instance().findRandomService();
	Event evt(random->next(state.customerInterArrivalTimeDist()));
	evt.setHandler(new CustomerArrivalHandler(random->next(state.customerGarmentDropoffCntDist())));
	pendingQueue.push(evt);
	while (!pendingQueue.empty() && clock.now() < config.simDuration) {
		Event evt = pendingQueue.min();
		pendingQueue.pop();
		clock.advanceTo(evt.time());
		if (clock.now() < config.simDuration) {
			evt.execute(state);
			processConditionalEvents();
		}
	}
}