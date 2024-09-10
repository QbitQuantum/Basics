void AbstractBox::paintTitle(Painter &p, const QString &title, const QString &additional) {
	p.setFont(st::boxTitleFont);
	if (_blueTitle) {
		p.fillRect(0, 0, width(), st::boxTitleHeight, st::boxBlueTitleBg->b);
		p.setPen(st::white);

		int32 titleWidth = st::boxTitleFont->width(title);
		p.drawTextLeft(st::boxBlueTitlePosition.x(), st::boxBlueTitlePosition.y(), width(), title, titleWidth);

		if (!additional.isEmpty()) {
			p.setFont(st::boxTextFont);
			p.setPen(st::boxBlueTitleAdditionalFg);
			p.drawTextLeft(st::boxBlueTitlePosition.x() + titleWidth + st::boxBlueTitleAdditionalSkip, st::boxBlueTitlePosition.y(), width(), additional);
		}
	} else {
		p.setPen(st::boxTitleFg);
		p.drawTextLeft(st::boxTitlePosition.x(), st::boxTitlePosition.y(), width(), title);
	}
}