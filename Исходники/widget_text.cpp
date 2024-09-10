void WidgetText::draw(Canvas& can) {
	SDL_Rect r{0, 0, bounds.w, bounds.h};
	if (drawBg) {
		can.setColor(colBg);
		can.fillRect(r);
	}
	if (tex != nullptr) {
		r.w = std::min(bounds.w, texSz.first);
		r.h = std::min(bounds.h, texSz.second);
		can.draw(tex, &r);
	}
}