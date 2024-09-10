void MultiCursorAppCpp::initGL(int argc, char* argv[])
{
	glutInit(&argc, argv);

	WinIDs = new int[TKinect2Display.size()];
	for (size_t i = 0; i < TKinect2Display.size(); ++i)
	{
		glutInitWindowPosition(i*20, 0);
		//glutInitWindowPosition(windowOffsetX[i], 0);
		glutInitWindowSize(VEC_WIN_WIDTH[i], VEC_WIN_HEIGHT[i]);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		char winName[8];
		_itoa((int)i, winName, 10);
		WinIDs[i] = glutCreateWindow(winName);

		//// Register callback functions
		//glutReshapeFunc(sreshape);
		glutDisplayFunc(sdisplay);
		glutIdleFunc(sidle);
		glutKeyboardFunc(skeyboard);
		glutMouseFunc(smouse);

		glClearColor(1.0, 1.0, 1.0, 1.0);

		/* Camera setup */
		glViewport(0, 0, kinectBasics.widthDepth, kinectBasics.heightDepth);
		glLoadIdentity();

		if (i == 0){
			/* GLのウィンドウをフルスクリーンに */
			//GLのデバイスコンテキストハンドル取得
			glutSetWindow(WinIDs[i]);
			HDC glDc = wglGetCurrentDC();
			//ウィンドウハンドル取得
			HWND hWnd = WindowFromDC(glDc);
			//ウィンドウの属性と位置変更
			SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
			SetWindowPos(hWnd, HWND_TOP, windowOffsetX[i], 0, VEC_WIN_WIDTH[i], VEC_WIN_HEIGHT[i], SWP_SHOWWINDOW);
		}
	}
}