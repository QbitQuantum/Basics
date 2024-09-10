int SpriteBatch::add(float x, float y, float a, float sx, float sy, float ox, float oy, float kx, float ky, int index /*= -1*/)
{
	// Only do this if there's a free slot.
	if ((index == -1 && next >= size) || index < -1 || index >= size)
		return -1;

	// Needed for colors.
	memcpy(sprite, image->getVertices(), sizeof(vertex)*4);

	// Transform.
	Matrix t;
	t.setTransformation(x, y, a, sx, sy, ox, oy, kx, ky);
	t.transform(sprite, sprite, 4);

	if (color)
		setColorv(sprite, *color);

	addv(sprite, (index == -1 ? next : index));

	// Increment counter.
	if (index == -1)
		return next++;
	return index;
}