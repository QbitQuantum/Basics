int _tmain(int argc, char* argv[])
{
    screenHeight = 600;
    screenWidth = 800;
    isFullScreen = false;
    isAnimated = true;

    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth,screenHeight);

    glutCreateWindow("FBO Mirror");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutSpecialFunc(SpecialKeys);
    glutSpecialUpFunc(SpecialKeysUp);

    Init();
    glutMainLoop();
    ShutDown();

    return 0;
}