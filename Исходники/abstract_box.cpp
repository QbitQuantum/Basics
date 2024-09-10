void AbstractBox::paintEvent(QPaintEvent *e) {
	Painter p(this);
	auto clip = e->rect();
	auto paintTopRounded = clip.intersects(QRect(0, 0, width(), st::boxRadius));
	auto paintBottomRounded = clip.intersects(QRect(0, height() - st::boxRadius, width(), st::boxRadius));
	if (paintTopRounded || paintBottomRounded) {
		auto parts = RectPart::None | 0;
		if (paintTopRounded) parts |= RectPart::FullTop;
		if (paintBottomRounded) parts |= RectPart::FullBottom;
		App::roundRect(p, rect(), st::boxBg, BoxCorners, nullptr, parts);
	}
	auto other = e->region().intersected(QRect(0, st::boxRadius, width(), height() - 2 * st::boxRadius));
	if (!other.isEmpty()) {
		for (auto rect : other.rects()) {
			p.fillRect(rect, st::boxBg);
		}
	}
	if (!_additionalTitle.isEmpty() && clip.intersects(QRect(0, 0, width(), titleHeight()))) {
		paintAdditionalTitle(p);
	}
}