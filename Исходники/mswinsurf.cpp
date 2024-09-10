void *
MSWinSurface::createExtraContext()
{
	assert(hGLRC != 0);
	HDC hDC = GetDC(hWnd);
	HGLRC hRC = wglCreateContext(hDC);
	if (hRC == 0) throw EMSWinError(GetLastError(), "wglCreateContext() (extra context)");
    if (! wglShareLists(hGLRC, hRC)) throw EMSWinError(GetLastError(), "wglShareLists() (extra context)");
	return hRC;
}