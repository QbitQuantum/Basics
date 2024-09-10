//----------------------------------------------------------------------------
// 计算选择射线
//----------------------------------------------------------------------------
bool Renderer::GetPickRay (int x, int y, APoint& origin, AVector& direction)
const
{
	if (!mCamera)
	{
		return false;
	}

	// Get the current viewport and test whether (x,y) is in it.
	int viewX, viewY, viewW, viewH;
	GetViewport(viewX, viewY, viewW, viewH);
	if (x < viewX || x > viewX + viewW || y < viewY || y > viewY + viewH)
	{
		return false;
	}

	// Get the [0,1]^2-normalized coordinates of (x,y).
	float r = ((float)(x - viewX))/(float)viewW;
	float u = ((float)(y - viewY))/(float)viewH;

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
	}

	return true;
}