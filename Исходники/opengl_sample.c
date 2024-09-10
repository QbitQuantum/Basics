int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(g_TextureWidth, g_TextureHeight);
	glutInitWindowPosition(0, 0);
	
	win = glutCreateWindow(TITLE);
	createMenu();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	if (initEnvironment())
	{
		glutMainLoop();
	}

	return 0;
}