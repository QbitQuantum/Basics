	//
	// `Line::intersectsAt()` is based on
	// https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
	//
	// Licenced with the Code Project Open Licence (CPOL)
	// http://www.codeproject.com/info/cpol10.aspx
	//
	Optional<Line::position_type> Line::intersectsAt(const Line& line) const
	{
		const Vec2 r = end - begin;
		const Vec2 s = line.end - line.begin;
		const Vec2 qp = line.begin - begin;
		const double rxs = r.x * s.y - r.y * s.x;
		const double qpxr = qp.x * r.y - qp.y * r.x;
		const double qpxs = qp.x * s.y - qp.y * s.x;
		const bool rxsIsZero = detail::IsZero(rxs);

		if (rxsIsZero && detail::IsZero(qpxr))
		{
			const double qpr = qp.dot(r);
			const double pqs = (begin - line.begin).dot(s);

			if ((0 <= qpr && qpr <= r.dot(r)) || (0 <= pqs && pqs <= s.dot(s)))
			{
				// Two lines are overlapping			
				return Line::position_type(Math::QNaN, Math::QNaN);
			}

			// Two lines are collinear but disjoint.
			return none;
		}
		
		if (rxsIsZero && !detail::IsZero(qpxr))
		{
			// Two lines are parallel and non-intersecting.
			return none;
		}

		const double t = qpxs / rxs;
		const double u = qpxr / rxs;

		if (!rxsIsZero && (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
		{
			// An intersection was found
			return begin + t * r;
		}

		// Two line segments are not parallel but do not intersect
		return none;
	}