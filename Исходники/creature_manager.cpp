void CreatureManager::draw(Canvas& can) {
	for (auto c : creatures) {
		c->draw(can);
		c->getHealthBar()->draw(can);
#if defined(DEBUG_CREATURE_BOUNDS) && DEBUG_CREATURE_BOUNDS
		// draw overlay over each creature
		auto rect = c->getBounds();
		auto oldColor = can.getColorState();
		can.setColor(DEBUG_CREATURE_BOUNDS_COLOR, getAlpha<DEBUG_CREATURE_BOUNDS_ALPHA>());
		can.fillRect(rect);
		can.setColorState(oldColor);
#endif // DEBUG_CREATURE_BOUNDS
	}
}