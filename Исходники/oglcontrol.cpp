void CBaseOglControl::ReDraw()
{
	SetFocus(hMy);
	CalcFps();
	wglMakeCurrent(GetDC(hMy), hOGL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Refresh();

	SwapBuffers(wglGetCurrentDC());
	glFlush();
	wglMakeCurrent(GetDC(hMy), 0);
}