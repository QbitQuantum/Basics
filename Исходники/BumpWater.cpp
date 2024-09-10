void CBumpWater::UpdateCoastmap(const int x1, const int y1, const int x2, const int y2)
{
	glDisable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	coastFBO.Bind();

	glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, coastTexture[1]);
	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, coastTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();
		glScalef(1.0f/gs->mapx, 1.0f/gs->mapy, 1);
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glScalef(1.0f/gs->mapx, 1.0f/gs->mapy, 1);

	glViewport(0,0,gs->mapx, gs->mapy);
	glUseProgram(blurShader);

	int xmin = max(x1 - 10*2,0);
	int xmax = min(x2 + 10*2,gs->mapx);
	int ymin = max(y1 - 10*2,0);
	int ymax = min(y2 + 10*2,gs->mapy);
	int xsize = xmax - xmin;
	int ysize = ymax - ymin;

	glUniform2f(blurDirLoc,1.0f/gs->mapx,0.0f);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glUniform1i(blurTexLoc,1);

	glBegin(GL_QUADS);
		glTexCoord2f(xmin,ymin); glVertex2f(xmin,ymin);
		glTexCoord2f(xmin,ymax); glVertex2f(xmin,ymax);
		glTexCoord2f(xmax,ymax); glVertex2f(xmax,ymax);
		glTexCoord2f(xmax,ymin); glVertex2f(xmax,ymin);
	glEnd();

	for (int i=0; i<5; ++i){
		glUniform2f(blurDirLoc,0.0f,1.0f/gs->mapy);
		glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
		glUniform1i(blurTexLoc,0);

		glBegin(GL_QUADS);
			glTexCoord2f(xmin,ymin); glVertex2f(xmin,ymin);
			glTexCoord2f(xmin,ymax); glVertex2f(xmin,ymax);
			glTexCoord2f(xmax,ymax); glVertex2f(xmax,ymax);
			glTexCoord2f(xmax,ymin); glVertex2f(xmax,ymin);
		glEnd();

		glUniform2f(blurDirLoc,1.0f/gs->mapx,0.0f);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glUniform1i(blurTexLoc,1);

		glBegin(GL_QUADS);
			glTexCoord2f(xmin,ymin); glVertex2f(xmin,ymin);
			glTexCoord2f(xmin,ymax); glVertex2f(xmin,ymax);
			glTexCoord2f(xmax,ymax); glVertex2f(xmax,ymax);
			glTexCoord2f(xmax,ymin); glVertex2f(xmax,ymin);
		glEnd();
	}

	glMatrixMode(GL_TEXTURE);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, coastTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmapEXT(GL_TEXTURE_2D);

	glUseProgram(0);
	glViewport(gu->viewPosX,0,gu->viewSizeX,gu->viewSizeY);

	coastFBO.Unbind();
}