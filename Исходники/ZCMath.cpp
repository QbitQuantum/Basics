float DistancetoLineSegment(const Vector2f& a, const Vector2f& b, const Vector2f& point)
{
	Vector2f dist = b - a;
	float length = dist.Length();
	float t = (point - a).Dot(dist);

	if(t < 0.0f)
		return (point - a).Length();
	if(t > length)
		return (point - b).Length();

	dist.Normalize();
	if(dist == Vector2f::Zero)
		return (point - a).Length();

	return (point - (a + dist * t)).Length();
}