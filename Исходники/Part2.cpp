static void draw		(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if(bRendered)	glEnable(GL_TEXTURE_2D);
	else			glDisable(GL_TEXTURE_2D);

	if(bWireframe)
	{
		glLineWidth( 2.0 );
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
		glPolygonMode(GL_FRONT, GL_FILL);

	glRotatef(5, 1,0,0);
	camera.transform(sky);
	sun.transform();

	if(bDrawGrid) draw_axis();
	
	glColor3f(0.9,0.9,0.9);

	// Cylinder building
	glPushMatrix();
	glTranslatef(0, 0, -100);
	glRotatef(40, 0, 1, 0);
	spLight.transform();	// Update spot light
	cylinder.draw();
	step1.draw();
	step2.draw();
	glPopMatrix();

	// Right cuboid building
	glPushMatrix();
	glTranslatef(100, 25, 25);
	build_right.draw();
	glTranslatef(-75, 0, 150);
	glRotatef( 90, 0, 1, 0 );
	build_right.draw();
	glPopMatrix();

	// Front timber building
	glPushMatrix();
	glTranslatef(20, 15, 0);
	build_front.draw();
	glPopMatrix();

	// Foundations
	glPushMatrix();
	glTranslatef(0, -15, 0);
	foundation.draw();
	glTranslatef(-325, 0, 0);
	foundation.draw();
	glPopMatrix();

	// Water
	glPushMatrix();
	glTranslatef(-160,-10,0);
	water.draw();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
	Sleep(1);	// Frame limiter
}