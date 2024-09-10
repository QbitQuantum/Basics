void Display(void)
{
	double matBuf[4*4];
	YsVec3 eyePos;
	YsMatrix4x4 eyeTfm;

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
	DrawSeparatablePair(nVtx,vtx);

	glFlush();
	glutSwapBuffers();
}