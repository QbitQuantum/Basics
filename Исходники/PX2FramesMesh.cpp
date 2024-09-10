//----------------------------------------------------------------------------
int FramesMesh::_GetDirIndex(const AVector &dir)
{
	AVector animVec = dir;
	animVec.Normalize();

	AVector up = AVector::UNIT_Y;
	float dotVal = up.Dot(animVec);

	float rad = Mathf::ACos(dotVal);
	float degree = Mathf::RAD_TO_DEG * rad;
	bool isRight = (dir.X() > 0.0f);

	if (0 <= degree && degree < 22.5f)
	{
		return 0;
	}
	else if (22.5f <= degree && degree < 67.5f)
	{
		if (isRight)
			return 1;
		else
			return 7;
	}
	else if (67.5 <= degree && degree < 112.5f)
	{
		if (isRight)
			return 2;
		else
			return 6;
	}
	else if (112.5f <= degree && degree < 157.5f)
	{
		if (isRight)
			return 3;
		else
			return 5;
	}
	else if (157.5f <= degree && degree <= 180.0f)
	{
		return 4;
	}

	return 0;
}