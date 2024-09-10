float RMZHelper::calculateAngle(const Point origin, const Point offset)
{
	Point up = ccp(0, 1);
	Point indicator = origin - offset;

	float theta = CC_RADIANS_TO_DEGREES(acos(indicator.dot(up) / indicator.getLength() * up.getLength()));

	return theta;
}