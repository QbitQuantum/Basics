Vector Vector::projection(const Vector& o) const
{
	Vector unit = o.normalize();

	return (*this * o)/o.size()*unit;
}