	bool equals(const Coordinate& p0, const Coordinate& p1,
	            double distanceTolerance)
        {
                return p0.distance(p1) <= distanceTolerance;
        }