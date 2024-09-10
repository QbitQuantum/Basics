Ladder::Ladder(float x, float y, float w, float h, const Sprites *s) {
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}