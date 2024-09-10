void callBackDisplay(void)
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)winwidth/winheight, 0.01, 100);

	camera.move( phyEngine->getPositionBody(Body::Trunk) - camera.lookAt );
	camera.transform();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	draw_axis();
	glEnable(GL_LIGHTING);


	glPushMatrix();
	glSetMaterial(1,1,1);
	simBird->drawBird();		// bird model
	glPopMatrix();

	glutSwapBuffers();
}