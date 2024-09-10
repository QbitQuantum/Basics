bool guiRenderer2D::on_expose_event(GdkEventExpose* event) {

	Glib::RefPtr<Gdk::Window> window = get_window();
	if(window) {
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		if(event) {
			// clip to the area indicated by the expose event so that we only
			// redraw the portion of the window that needs to be redrawn
			//printf("event->area.x: %d, event->area.y: %d, event->area.width: %d, event->area.height: %d\n", event->area.x, event->area.y, event->area.width, event->area.height );
			cr->rectangle(event->area.x, event->area.y,	event->area.width, event->area.height);
			cr->clip();
		}

		// Background
		// cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->set_source_rgb(1.0, 1.0, 1.0);
		cr->paint();

		if(m_isRendering && m_layoutAvailable) {
			Gtk::Allocation allocation = get_allocation();
			int width = allocation.get_width();
			int height = allocation.get_height();

			if(width != m_widgetWidth || height != m_widgetHeight ) { // Allocation changed
				rescaleSensorLayout(width, height);
			}

			drawMatrices(cr, width, height, false);
		}
	}

	return true;
}