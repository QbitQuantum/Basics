GLvoid drawScene(GLvoid) 
{ 
	wglMakeCurrent(g_hDC, g_hGLRC);

    glClear(GL_COLOR_BUFFER_BIT); 
 
    glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor4ub(255, 255, 255, 255);
		
	
	GLfloat maxU = (GLfloat) ((g_windowWidth * 1.0) / g_vTextures[0].nWidth);
	GLfloat maxV = (GLfloat) ((g_windowHeight * 1.0) / g_vTextures[0].nHeight);
	
	glBindTexture(GL_TEXTURE_2D, g_vTextureIDs[0]);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, maxV); glVertex2i(0, 0);
	glTexCoord2f(maxU, maxV); glVertex2i(g_windowWidth, 0);
	glTexCoord2f(maxU, 0.0f); glVertex2i(g_windowWidth, g_windowHeight);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, g_windowHeight);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, g_vTextureIDs[1]);
	
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, g_vTextures[1].nMaxV);	glVertex2i(100, 100);
	
	glTexCoord2f(g_vTextures[1].nMaxU, 
		g_vTextures[1].nMaxV);					glVertex2i(171, 100); 
	glTexCoord2f(g_vTextures[1].nMaxU, 0.0f); 	glVertex2i(171, 196);
	glTexCoord2f(0.0f, 0.0f); 					glVertex2i(100, 196);
	
	glEnd();
 	
	glDisable(GL_TEXTURE_2D);

	
	glBegin(GL_QUADS);
	glColor4ub(0, 200, 0, 255);
	glVertex2i(200, 100);
	glVertex2i(350, 100);
	glVertex2i(350, 200);
	glVertex2i(200, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor4ub(0, 0, 0, 255);
	glVertex2i(200, 100);
	glVertex2i(350, 100);
	glVertex2i(350, 200);
	glVertex2i(200, 200);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_vTextureIDs[2]);

	glBegin(GL_QUADS);
	glColor4ub(255, 0, 0, 255);
	glTexCoord2f(0.0f, g_vTextures[2].nMaxV);	glVertex2i(10, 10);

	glTexCoord2f(g_vTextures[2].nMaxU, 
		g_vTextures[2].nMaxV);					glVertex2i(20, 10); 
	glTexCoord2f(g_vTextures[2].nMaxU, 0.0f); 	glVertex2i(20, 20);
	glTexCoord2f(0.0f, 0.0f);					glVertex2i(10, 20);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glFlush();

	
 
    SwapBuffers(g_hDC); 
}