void BackgroundRow::paintEvent(QPaintEvent *e) {
	Painter p(this);

	bool radial = false;
	float64 radialOpacity = 0;
	if (_radial.animating()) {
		_radial.step(getms());
		radial = _radial.animating();
		radialOpacity = _radial.opacity();
	}
	if (radial) {
		auto backThumb = App::main() ? App::main()->newBackgroundThumb() : ImagePtr();
		if (backThumb->isNull()) {
			p.drawPixmap(0, 0, _background);
		} else {
			const QPixmap &pix = App::main()->newBackgroundThumb()->pixBlurred(st::settingsBackgroundSize);
			p.drawPixmap(0, 0, st::settingsBackgroundSize, st::settingsBackgroundSize, pix, 0, (pix.height() - st::settingsBackgroundSize) / 2, st::settingsBackgroundSize, st::settingsBackgroundSize);
		}

		auto outer = radialRect();
		QRect inner(QPoint(outer.x() + (outer.width() - st::radialSize.width()) / 2, outer.y() + (outer.height() - st::radialSize.height()) / 2), st::radialSize);
		p.setPen(Qt::NoPen);
		p.setBrush(st::black);
		p.setOpacity(radialOpacity * st::radialBgOpacity);

		p.setRenderHint(QPainter::HighQualityAntialiasing);
		p.drawEllipse(inner);
		p.setRenderHint(QPainter::HighQualityAntialiasing, false);

		p.setOpacity(1);
		QRect arc(inner.marginsRemoved(QMargins(st::radialLine, st::radialLine, st::radialLine, st::radialLine)));
		_radial.draw(p, arc, st::radialLine, st::white);
	} else {
		p.drawPixmap(0, 0, _background);
	}
}