Color Color::inverted() const {

	Color c = *this;
	c.invert();
	return c;
}