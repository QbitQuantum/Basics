bool Pyramid::isInside(Point3D point) const {
	return point.getP().getX() >= 0 &&
		   point.getP().getY() >= 0 &&
		   point.getZ() >= 0 &&
		   point.getP().getX() / getA() +
		   point.getP().getY() / getB() +
		   point.getZ() / getC() <= 1;
}