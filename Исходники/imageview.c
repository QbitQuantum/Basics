/**
 * create window & run main loop
 */
void createWindow(windowData *win){
	FNAME();
	if(!initialized) return;
	if(!win) return;
	int w = win->w, h = win->h;
	DBG("create window with title %s", win->title);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	win->GL_ID = glutCreateWindow(win->title);
	DBG("created GL_ID=%d", win->GL_ID);
	glutReshapeFunc(Resize);
	glutDisplayFunc(RedrawWindow);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(keySpPressed);
	//glutMouseWheelFunc(mouseWheel);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMove);
	//glutIdleFunc(glutPostRedisplay);
	glutIdleFunc(NULL);
	DBG("init textures");
	glGenTextures(1, &(win->Tex));
	calc_win_props(win, NULL, NULL);
	win->zoom = 1. / win->Daspect;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, win->Tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, win->image->w, win->image->h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, win->image->rawdata);
	glDisable(GL_TEXTURE_2D);
	totWindows++;
	createMenu(win->GL_ID);
	DBG("OK, total opened windows: %d", totWindows);
}