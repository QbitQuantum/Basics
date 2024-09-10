void xlui::line_edit::mouse_press_event(xlui::mouse_event &event) {
	_selection = false;

	int32_t width = 0;
	int32_t count = 0;
	xlui::string text = _text;
	uint32_t pos  = event.get_position().get_x();

	m_iCursorPos = pos;
//	xlui::string_dimension dim(_font, this);
	xlui::font_metric dim(_font);

	do {
		width = dim.get_width(text);
		m_iCursorPos = width;
		count = text.get_character_count();
		text = text.mid(0, count - 1);
		count = text.get_character_count();
	} while(pos < width && count > 0);

	if(pos < width) {
		m_iCursorPos = 0;
	} else {
		++count;
	}

	m_SelectionStart.set_x(m_iCursorPos);
	m_SelectionStart.set_y(event.get_position().get_y());

	m_iActualCursor = count;

	set_focus();

	stop_timer(m_iTimerId);
	m_iTimerId = start_timer(500);
	update();
}