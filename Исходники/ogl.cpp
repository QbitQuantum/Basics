static bool _begin()
{
	//wglMakeCurrent is slow in some environments. so, check if the desired context is already current
	if(wglGetCurrentContext() == main_hRC)
		return true;

	if(!wglMakeCurrent(main_hDC, main_hRC))
		return false;

	return true;
}