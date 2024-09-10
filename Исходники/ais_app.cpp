void RecentEntriesView<AISRecentEntries>::draw(
	const Entry& entry,
	const Rect& target_rect,
	Painter& painter,
	const Style& style,
	const bool is_selected
) {
	const auto& draw_style = is_selected ? style.invert() : style;

	std::string line = ais::format::mmsi(entry.mmsi) + " ";
	if( !entry.name.empty() ) {
		line += entry.name;
	} else {
		line += entry.call_sign;
	}

	line.resize(target_rect.width() / 8, ' ');
	painter.draw_string(target_rect.pos, draw_style, line);
}