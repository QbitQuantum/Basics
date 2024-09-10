void CBaseOglCamera::GetViewPort(RECT& vp)
{
	if (viewPort[0] != 0 || viewPort[1] != 0 || viewPort[2] != 0 || viewPort[3] != 0)
	{
		vp.left = viewPort[0];
		vp.top = viewPort[1];
		vp.right = viewPort[2];
		vp.bottom = viewPort[3];
	}
	else
		GetClientRect(WindowFromDC(wglGetCurrentDC()), &vp);
}