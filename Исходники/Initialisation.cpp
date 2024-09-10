///Function that starts the entire process.
void ScreenSaver::execute(int& argc , char** argv) {

	///Generating objects
	generateTable();
	generateBall();
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	windowID = glutCreateWindow(" Bouncy ball ");

	init();
	threadInit();
	initSkybox();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutSpecialFunc(handleSpecial); 
	//GLUI *glUserInterface = GLUI_Master.create_glui_subwindow( windowID,GLUI_SUBWINDOW_RIGHT );
	menu.createMenu();	

	glutTimerFunc(DELTA_T , timer , 0);
	glutMainLoop();
	for(int i=0; i<NUM_BALLS;i++)
		pthread_exit(&vecBallThread[i]);
}