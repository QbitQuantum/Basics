//----------------------------------------------------------------------------
bool RenderStep::GetPickRay(float x, float y, APoint& origin, AVector& direction)
{
	if (!mCamera) return false;

	Rectf viewPort = mViewPort;
	if (viewPort.IsEmpty())
		viewPort = Rectf(0.0f, 0.0f, mSize.Width, mSize.Height);

	if (viewPort.IsEmpty()) return false;

	// Get the current viewport and test whether (x,y) is in it.
	float viewX = viewPort.Left;
	float viewY = viewPort.Bottom;
	float viewW = viewPort.Width();
	float viewH = viewPort.Height();

	// Get the [0,1]^2-normalized coordinates of (x,y).
	float r = ((float)(x - viewX)) / (float)viewW;
	float u = ((float)(y - viewY)) / (float)viewH;

	// Get the relative coordinates in [rmin,rmax]x[umin,umax].
	float rBlend = (1.0f - r)*mCamera->GetRMin() + r*mCamera->GetRMax();
	float uBlend = (1.0f - u)*mCamera->GetUMin() + u*mCamera->GetUMax();

	if (mCamera->IsPerspective())
	{
		origin = mCamera->GetPosition();
		direction = mCamera->GetDMin()*mCamera->GetDVector() +
			rBlend*mCamera->GetRVector() + uBlend*mCamera->GetUVector();
		direction.Normalize();
	}
	else
	{
		origin = mCamera->GetPosition() + rBlend*mCamera->GetRVector() +
			uBlend*mCamera->GetUVector();
		direction = mCamera->GetDVector();
		direction.Normalize();
	}

	return true;
}