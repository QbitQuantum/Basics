CirclePath::CirclePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& orbitPosition, bool clockWise, const Vector3& rotationAxis) :
		Path(baseRotation), startPosition(startPosition), orbitPosition(orbitPosition), clockWise(clockWise)
{
	Vector3 orbitDirection = orbitPosition - startPosition;

	radius = orbitDirection.length();

	orbitDirection = orbitDirection.normalize();

	//

	Vector3 normalizedRotationAxis = rotationAxis.normalize();

	Vector3 testAxis = orbitDirection.cross(normalizedRotationAxis);

	if (testAxis.length() == 0.0f)
	{
		testAxis = Vector3(1.0f, 0.0f, 0.0f).cross(orbitDirection);

		if (testAxis.length() == 0.0f)
		{
			this->rotationAxis = Vector3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			this->rotationAxis = testAxis;
		}
	}
	else
	{
		this->rotationAxis = rotationAxis;
	}

	elapsedAngle = 0.0f;
}