static void Target_mouseMoved(float x, float y) {
	struct mouseEvent event;
	
	event.position = VECTOR2f(x, y);
	EventDispatcher_dispatchEvent(screenManager->eventDispatcher, ATOM(EVENT_MOUSE_MOVED), &event);
}