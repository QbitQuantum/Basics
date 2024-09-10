void UnreadBar::paint(Painter &p, int y, int w) const {
	const auto bottom = y + height();
	y += marginTop();
	p.fillRect(
		0,
		y,
		w,
		height() - marginTop() - st::lineWidth,
		st::historyUnreadBarBg);
	p.fillRect(
		0,
		bottom - st::lineWidth,
		w,
		st::lineWidth,
		st::historyUnreadBarBorder);
	p.setFont(st::historyUnreadBarFont);
	p.setPen(st::historyUnreadBarFg);

	int left = st::msgServiceMargin.left();
	int maxwidth = w;
	if (Adaptive::ChatWide()) {
		maxwidth = qMin(
			maxwidth,
			st::msgMaxWidth
				+ 2 * st::msgPhotoSkip
				+ 2 * st::msgMargin.left());
	}
	w = maxwidth;

	const auto skip = st::historyUnreadBarHeight
		- 2 * st::lineWidth
		- st::historyUnreadBarFont->height;
	p.drawText(
		(w - width) / 2,
		y + (skip / 2) + st::historyUnreadBarFont->ascent,
		text);
}