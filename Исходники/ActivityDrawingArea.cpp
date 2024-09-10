void ActivityDrawingArea::invalidateWindow() {
	Gdk::Rectangle lRect = this->get_allocation();
	this->get_window()->invalidate_rect(Gdk::Rectangle(0, 0, lRect.get_width(), lRect.get_height()), false);
}