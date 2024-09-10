	Polygon Quad::asPolygon() const
	{
		const auto [xMin, xMax] = std::minmax({ p0.x, p1.x, p2.x, p3.x });
		const auto [yMin, yMax] = std::minmax({ p0.y, p1.y, p2.y, p3.y });

		return Polygon({ p0, p1, p2, p3 }, { 0, 1, 3, 3, 1, 2 }, RectF(xMin, yMin, xMax - xMin, yMax - yMin));
	}