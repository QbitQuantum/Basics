float Capsule::Distance(const LineSegment &lineSegment) const
{
	return lineSegment.Distance(*this);
}