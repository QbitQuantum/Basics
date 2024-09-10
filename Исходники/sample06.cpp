void Display(void)
{
	double matBuf[4*4];
	YsVec3 eyePos;
	YsMatrix4x4 eyeTfm;
	YsVec3 p;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	eyePos.Set(0.0,0.0,eyeDistance);
	eyePos=eyeAtt.GetMatrix()*eyePos;

	eyeTfm.Initialize();
	eyeTfm.Translate(eyePos);
	eyeTfm.Rotate(eyeAtt);
	eyeTfm.Invert();
	eyeTfm.Translate(-eyeLookAt);

	eyeTfm.GetArray(matBuf);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixd(matBuf);
	DrawAxis(5.0);

	glDisable(GL_LIGHTING);
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(axisOfOrbit.x()*5.0,axisOfOrbit.y()*5.0,axisOfOrbit.z()*5.0);
	glEnd();

	rot.RotatePositive(p,orbiter);
	glPushMatrix();
	glTranslatef(p.x()*5.0,p.y()*5.0,p.z()*5.0);
	DrawCursor();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}