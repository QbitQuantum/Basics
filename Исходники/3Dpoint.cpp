bool Point3D::belongsTo(Plain const& alpha) const
{
	return alpha.getA() * x + alpha.getB() * y + alpha.getC() *z + alpha.getD() == 0;
}