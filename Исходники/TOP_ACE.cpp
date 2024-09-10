void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char path[_MAX_PATH];
    GetModuleFileName(hInstance, path, _MAX_PATH);
	char* argv=(char *)path;
	
	glutInit            ( &nCmdShow, &argv ); // Erm Just Write It =)
	if(GameSet.AA>0)
		glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE ); // Display Mode
	else
		glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH );
	if(GameSet.AA>0)
		glutSetOption(GLUT_MULTISAMPLE,GameSet.AA);
	if(GameSet.isFullScreem)
		isFullScreem();
	else
		isWindow();
	if(GameSet.SYNC)
	{
		typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
		PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)
		wglGetProcAddress("wglSwapIntervalEXT");
		wglSwapIntervalEXT(1);
	}
}