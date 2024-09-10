void GazeTracker::boundToScreenCoordinates(Point &estimate) {
	int numMonitors = Gdk::Screen::get_default()->get_n_monitors();
	Gdk::Rectangle monitorGeometry;
	Glib::RefPtr<Gdk::Screen> screen = Gdk::Display::get_default()->get_default_screen();

	// Geometry of main monitor
	screen->get_monitor_geometry(numMonitors - 1, monitorGeometry);

	// If x or y coordinates are outside screen boundaries, correct them
	if (estimate.x < monitorGeometry.get_x()) {
		estimate.x = monitorGeometry.get_x();
	}

	if (estimate.y < monitorGeometry.get_y()) {
		estimate.y = monitorGeometry.get_y();
	}

	if (estimate.x >= monitorGeometry.get_x() + monitorGeometry.get_width()) {
		estimate.x = monitorGeometry.get_x() + monitorGeometry.get_width();
	}

	if (estimate.y >= monitorGeometry.get_y() + monitorGeometry.get_height()) {
		estimate.y = monitorGeometry.get_y() + monitorGeometry.get_height();
	}
}