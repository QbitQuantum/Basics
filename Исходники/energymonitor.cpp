void EnergyMonitor::draw(const Common::Rect &r) {
	Common::Rect r2 = r.findIntersectingRect(_levelRect);

	if (!r2.isEmpty()) {
		Graphics::Surface *screen = ((PegasusEngine *)g_engine)->_gfx->getWorkArea();
		screen->fillRect(r2, _barColor);
	}
}