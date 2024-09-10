void Dialog::draw(Canvas& can) {
	using namespace DialogSettings;
	SDL_Rect r{0, 0, bounds.w, bounds.h};
	if (borderSz > 0) {
		can.setColor(colBorder);
		can.fillRect(r);
		shrinkRect(r, borderSz);
		can.setColor(colBg);
		can.fillRect(r);
		can.setRelViewport(r);
		layout.draw(can);
		can.clearViewport();
	}
	else {
		can.setColor(colBg);
		can.fillRect(r);
		layout.draw(can);
	}
}