float Vec2i::distancef(int x, int y) const
{
	return sqrtf(powf(((float)x_-(float)x), 2.0f) + pow(((float)y_-(float)y), 2.0f));
}