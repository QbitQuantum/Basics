bool
CameraCalib::InitGlutUI(int argc, WCHAR* argvW[]) {
	srand(unsigned int(time(NULL)));

	const size_t len = wcsnlen(argvW[0], 1024);
	std::unique_ptr<char[]> argvuq(new char[len + 1]);
	char *pStr = (argvuq.get());
	size_t lastChar = 0;
	wcstombs_s(&lastChar, pStr, len, argvW[0], len - 1);
	pStr[lastChar] = '\0';
	char **argv = &pStr;
	argc = 1;

	glutInit(&argc, argv);
	glutInitWindowSize(windowRect[0], windowRect[1]);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //
	mainWnd = glutCreateWindow("CameraCalib");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::wcout << L"Camera Calib" << glewGetErrorString(err) << std::endl;
		return false;
	}
	
	glutDisplayFunc(clbDisplay);
	glutKeyboardFunc(clbKeys);
	glutReshapeFunc(clbReshape);
	glutMouseFunc(clbMouse);
	glutCloseFunc(clbExitFunc);

	glEnable(GL_DEPTH_TEST);
	return true;
}