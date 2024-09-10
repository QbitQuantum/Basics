	// computes distance to other rectangle
	double IntersectionRectangle::distance(const IntersectionRectangle &ir) const
	{
		double dist = 0.0;
		if(!intersects(ir)) {
			dist = parallelDist(top(),ir.bottom());
			dist = min(dist, parallelDist(left(),ir.right()));
			dist = min(dist, parallelDist(right(),ir.left()));
			dist = min(dist, parallelDist(bottom(),ir.top()));
		}
		return dist;
	}