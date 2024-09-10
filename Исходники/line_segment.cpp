	Type LineSegment2x<Type>::point_distance(const Vec2<Type> &point)
	{
		Type L = pow2(q.x - p.x) + pow2(q.y - p.y);
		Type r = ((point.x - p.x)*(q.x - p.x) + (point.y - p.y)*(q.y - p.y)) / L;

		if (r <= 0 || r >= 1)
		{
			return min(point.distance(p), point.distance(q));
		}

		Type s = ((p.y - point.y)*(q.x - p.x) - (p.x - point.x)*(q.y - p.y)) / L;

		s *= sqrt(L);

		if (s < ((Type)0))
			s = -s;

		return s;
	}