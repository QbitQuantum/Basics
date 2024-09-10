void manageEvents() {
	Common::EventManager *eventMan = g_system->getEventManager();

	uint32 nextFrame = g_system->getMillis() + g_cine->getTimerDelay();
	do {
		Common::Event event;
		while (eventMan->pollEvent(event)) {
			processEvent(event);
		}
		g_system->updateScreen();
		g_system->delayMillis(20);
	} while (g_system->getMillis() < nextFrame);

	g_sound->update();
	mouseData.left = mouseLeft;
	mouseData.right = mouseRight;
	mouseLeft = 0;
	mouseRight = 0;
}