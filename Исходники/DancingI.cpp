void display(void)
{
	if(dipMode==1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	

	curF++;
	// put your OpenGL display commands here
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// reset OpenGL transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // reset transformation matrix to identity

	// setup look at transformation so that 
	// eye is at : (0,0,3)
	// look at center is at : (0,0,0)
	// up direction is +y axis
	gluLookAt(0.f,0.f,3.f,0.f,0.f,0.f,0.f,1.f,0.f);
	glRotatef(fRotateAngle,.3f,1.f,.3f);
	//rand() * 2 - 1;

		// Test drawing a solid teapot

/*
	else{
		glLineWidth(2.5);
		//glColor3f(1. , 0. , 0.);
	}
*/

	glColor3f(changecolor + 1., changecolor + .5, changecolor);// set current color to orange
	//glutSolidTeapot(1.f); // call glut utility to draw a solid teapot 
  glBegin(GL_TRIANGLE_FAN);
  
	glVertex2f(-.6 + sin(change - 10) / 20, 1. + cos(change - 10) / 20);
	glVertex2f(-.6 + cos(change - 10) / 20, .6 + sin(change - 10) / 20);
	glVertex2f(-.2 + cos(change - 10) / 20, .6 + cos(change - 10) / 20); // v3
	glVertex2f(.2 + cos(change - 10) / 20, .6 + sin(change - 10) / 20); // v10
	glVertex2f(.6 + sin(change - 10) / 20, .6 + sin(change - 10) / 20);
	glVertex2f(.6 + cos(change - 10) / 20, 1. + sin(change - 10) / 20);

  glEnd();

  glBegin(GL_TRIANGLE_FAN);
/*	if (colorflag) {
		glColor3f(changecolor + 1., changecolor + .5, changecolor);// set current color to orange
	}
	else {
		glColor3f(changecolor + 1., changecolor + .5, changecolor);
	}*/

	glVertex2f(0. + sin(change - 10) / 20, -1. + sin(change - 10) / 20);
	glVertex2f(-.6 + sin(change - 10) / 20, -1. + sin(change - 10) / 20);
	glVertex2f(-.6 + cos(change - 10) / 20, -.6 + cos(change - 10) / 20);
	glVertex2f(-.2 + cos(change - 10) / 20, -.6 + sin(change - 10) / 20);
	glVertex2f(-.2 + cos(change - 10) / 20, .6 + cos(change - 10) / 20); // v3
	glVertex2f(.2 + cos(change - 10) / 20, .6 + sin(change - 10) / 20); // v10
	glVertex2f(.2 + sin(change - 10) / 20, -.6 + cos(change - 10) / 20);
	glVertex2f(.6 + cos(change - 10) / 20, -.6 + sin(change - 10) / 20);
	glVertex2f(.6 + sin(change - 10) / 20, -1. + cos(change - 10) / 20);

  glEnd();

	//glFlush();
	glutSwapBuffers();	// swap front/back framebuffer to avoid flickering 

	curClock=clock();
	float elapsed=(curClock-startClock)/(float)CLOCKS_PER_SEC;
	if(elapsed>1.0f){
		float fps=(float)(curF-prevF)/elapsed;
		printf("fps:%f\n",fps);
		prevF=curF;
		startClock=curClock;
	}
}