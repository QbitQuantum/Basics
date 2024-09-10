float getAngle(Vector2f v1, Vector2f v2)
{
	auto l1 = v1.lengthSq();
	auto l2 = v2.lengthSq();

	// Make sure we don't divide by zero
	if (std::abs(l1) < EPSILON || std::abs(l2) < EPSILON)
		return 0;

	v1.normalize();
	v2.normalize();

	auto angle = std::acos(Vector2f::dot(v1, v2));
	auto orientation = (v1.x * v2.y) - (v2.x * v1.y);

	if (orientation > 0)
		angle = -angle;

	// Radians to degrees
	return static_cast<float>(angle * (180.0 / M_PI));
}