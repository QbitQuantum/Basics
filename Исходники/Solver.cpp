void ChooseAxis(neV3 & x, neV3 & y, const neV3 & normal)
{
	neV3 mag;

	mag[0] = neAbs(normal[0]);
	mag[1] = neAbs(normal[1]);
	mag[2] = neAbs(normal[2]);

	if (mag[0] > mag[1])
	{
		if (mag[0] > mag[2])
		{
			x[0] = (normal[1] + normal[2]) / normal[0] * -1.0f;
			x[1] = 1.0f;
			x[2] = 1.0f;
		}
		else
		{
			x[2] = (normal[0] + normal[1]) / normal[2] * -1.0f;
			x[0] = 1.0f;
			x[1] = 1.0f;
		}
	}
	else if (mag[1] > mag[2])
	{
		x[1] = (normal[0] + normal[2]) / normal[1] * -1.0f;
		x[0] = 1.0f;
		x[2] = 1.0f;
	}
	else
	{
		x[2] = (normal[0] + normal[1]) / normal[2] * -1.0f;
		x[0] = 1.0f;
		x[1] = 1.0f;
	}
	x.Normalize();
	y = normal.Cross(x);
}