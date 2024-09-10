void CalendarBox::Inner::paintRows(Painter &p, QRect clip) {
	p.setFont(st::calendarDaysFont);
	auto ms = getms();
	auto y = rowsTop();
	auto index = -_context->daysShift();
	auto highlightedIndex = _context->highlightedIndex();
	for (auto row = 0, rowsCount = _context->rowsCount(), daysCount = _context->daysCount()
		; row != rowsCount
		; ++row, y += st::calendarCellSize.height()) {
		auto x = rowsLeft();
		if (!myrtlrect(x, y, st::calendarCellSize.width() * kDaysInWeek, st::calendarCellSize.height()).intersects(clip)) {
			index += kDaysInWeek;
			continue;
		}
		for (auto col = 0; col != kDaysInWeek; ++col, ++index, x += st::calendarCellSize.width()) {
			auto rect = myrtlrect(x, y, st::calendarCellSize.width(), st::calendarCellSize.height());
			auto grayedOut = (index < 0 || index >= daysCount || !rect.intersects(clip));
			auto highlighted = (index == highlightedIndex);
			auto enabled = _context->isEnabled(index);
			auto innerLeft = x + (st::calendarCellSize.width() - st::calendarCellInner) / 2;
			auto innerTop = y + (st::calendarCellSize.height() - st::calendarCellInner) / 2;
			if (highlighted) {
				PainterHighQualityEnabler hq(p);
				p.setPen(Qt::NoPen);
				p.setBrush(grayedOut ? st::windowBgOver : st::dialogsBgActive);
				p.drawEllipse(myrtlrect(innerLeft, innerTop, st::calendarCellInner, st::calendarCellInner));
				p.setBrush(Qt::NoBrush);
			}
			auto it = _ripples.find(index);
			if (it != _ripples.cend()) {
				auto colorOverride = [highlighted, grayedOut] {
					if (highlighted) {
						return grayedOut ? st::windowBgRipple : st::dialogsRippleBgActive;
					}
					return st::windowBgOver;
				};
				it->second->paint(p, innerLeft, innerTop, width(), ms, &(colorOverride()->c));
				if (it->second->empty()) {
					_ripples.erase(it);
				}
			}
			if (highlighted) {
				p.setPen(grayedOut ? st::windowSubTextFg : st::dialogsNameFgActive);
			} else if (enabled) {
				p.setPen(grayedOut ? st::windowSubTextFg : st::boxTextFg);
			} else {
				p.setPen(st::windowSubTextFg);
			}
			p.drawText(rect, _context->labelFromIndex(index), style::al_center);
		}
	}
}