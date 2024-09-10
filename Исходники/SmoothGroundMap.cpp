void SmoothGroundMap::Extract(glm::vec2 position, Image& brush)
{
	glm::ivec2 size = brush.size();
	glm::ivec2 origin = ToGroundmapCoordinate(position) - size / 2;

	for (int x = 0; x < size.x; ++x)
		for (int y = 0; y < size.y; ++y)
			brush.SetPixel(x, y, _image->GetPixel(origin.x + x, origin.y + y));
}