//----------------------------------------------------------------------------
bool Camera::GetPickRay(float posSizePercentWdith, float posSizePercentHeight,
	APoint& origin, AVector& direction)
{
	// Get the [0,1]^2-normalized coordinates of (x,y).
	float r = posSizePercentWdith;
	float u = posSizePercentHeight;

	// Get the relative coordinates in [rmin,rmax]x[umin,umax].
	float rBlend = (1.0f - r)*GetRMin() + r*GetRMax();
	float uBlend = (1.0f - u)*GetUMin() + u*GetUMax();

	if (IsPerspective())
	{
		origin = GetPosition();
		direction = GetDMin()*GetDVector() +
			rBlend*GetRVector() + uBlend*GetUVector();
		direction.Normalize();
	}
	else
	{
		origin = GetPosition() + rBlend*GetRVector() +
			uBlend*GetUVector();
		direction = GetDVector();
		direction.Normalize();
	}

	return true;
}