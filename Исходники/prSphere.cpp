void
prSphere::Intersect(Ray &r) const
{
	const vec3 vec = r.pos-mCenter;
	const real b = -vec.dot(r.dir);
	real det = Square(b) - r.dir.dot(r.dir) * vec.sqr_length() + mSqrRadius;
	if (det > real(0)) {
		det = det.Sqrt();
		const real i1 = b - det;
		const real i2 = b + det;
		if (i2 > r.minDist) {
			if (mMaterialFront && i1 < r.dist && i1 > r.minDist) {
				//outside
				r.gState.object = this;
				r.dist = i1;
			} else if (mMaterialBack && i2 < r.dist) {
				//inside
				r.gState.object = this;
				r.dist = i2;
			}
			return;
		}
	}
}