int VectorToPolar (const CVector &vP, Metric *retrRadius)

//	VectorToPolar
//
//	Converts from a vector to polar coordinates (see PolarToVector)

	{
	int iAngle;
	Metric rRadius;
	Metric rSqrRadius = vP.Dot(vP);

	//	If we are at the origin then the angle is undefined

	if (rSqrRadius == 0.0)
		{
		iAngle = 0;
		rRadius = 0.0;
		}
	else
		{
		rRadius = sqrt(rSqrRadius);
		if (vP.GetX() >= 0.0)
			iAngle = (((int)(180 * asin(vP.GetY() / rRadius) / g_Pi)) + 360) % 360;
		else
			iAngle = 180 - ((int)(180 * asin(vP.GetY() / rRadius) / g_Pi));
		}

	//	Done

	if (retrRadius)
		*retrRadius = rRadius;

	return iAngle;
	}