void SSD1306_Driver::printToLoc(const String &s, textRect &t, int color = WHITE){
	setCursor(t.x, t.y);
	int tempTextColor = textcolor;
	setTextColor(color);

	textRect* newt = this->print(s);
	t.x = newt->x;
	t.y = newt->y;
	t.h = newt->h;
	t.w = newt->w;

	delete(newt);

	setTextColor(tempTextColor);
}