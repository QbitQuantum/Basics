void RecentEntriesView<TPMSRecentEntries>::draw(
	const Entry& entry,
	const Rect& target_rect,
	Painter& painter,
	const Style& style,
	const bool is_selected
) {
	const auto& draw_style = is_selected ? style.invert() : style;

	std::string line = tpms::format::type(entry.type) + " " + tpms::format::id(entry.id);

	if( entry.last_pressure.is_valid() ) {
		line += " " + tpms::format::pressure(entry.last_pressure.value());
	} else {
		line += " " "   ";
	}

	if( entry.last_temperature.is_valid() ) {
		line += " " + tpms::format::temperature(entry.last_temperature.value());
	} else {
		line += " " "   ";
	}

	if( entry.received_count > 999 ) {
		line += " +++";
	} else {
		line += " " + to_string_dec_uint(entry.received_count, 3);
	}

	line.resize(target_rect.width() / 8, ' ');
	painter.draw_string(target_rect.pos, draw_style, line);
}