void DrawFrame(OpenGLDrawData &oglData)
{
	//OutputDebugString("Drawing frame ...\n");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	EnumDisplayMonitors(oglData.oglDC, NULL, MonitorEnumProc, (LPARAM)&oglData);

#if 0
	//glScalef(oglData.width, oglData.height, 1.0f);
	glPushMatrix();
	glTranslatef(oglData.width / 2.0f, oglData.height / 2.0f, 0.0f);
	glScalef(oglData.width, oglData.height, 0.0f);

	glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex2f(-0.5f, -0.5f);

		glColor3ub(0, 255, 0);
		glVertex2f(-0.5f, 0.5f);

		glColor3ub(0, 0, 255);
		glVertex2f(0.5f, 0.5f);

		glColor3ub(255, 255, 255);
		glVertex2f(0.5f, -0.5f);
	glEnd();
	glPopMatrix();
#endif
#if 1
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // non-premultiplied alpha
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); // premultiplied alpha
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, oglData.iconsTexture);
	glColor3ub(255, 255, 255);
	glScalef(oglData.width, oglData.height, 0.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
#endif

	//OutputDebugString("Drew frame.\n");
}