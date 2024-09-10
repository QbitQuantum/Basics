static void raytraceCollMesh(vector3d camPos, vector3d camera_up, vector3d camera_forward, CollisionSpace *space)
{
	memset(wank, 0, sizeof(float)*TEXSIZE*TEXSIZE);

	vector3d toPoint, xMov, yMov;

	vector3d topLeft, topRight, botRight, cross;
	topLeft = topRight = botRight = camera_forward * camera_zoom;
	cross = camera_forward.Cross(camera_up) * aspectRatio;
	topLeft = topLeft + camera_up - cross;
	topRight = topRight + camera_up + cross;
	botRight = botRight - camera_up + cross;

	xMov = topRight - topLeft;
	yMov = botRight - topRight;
	float xstep = 1.0f / TEXSIZE;
	float ystep = 1.0f / TEXSIZE;
	float xpos, ypos;
	ypos = 0.0f;
	GeomTree::stats_rayTriIntersections = 0;

	Uint32 t = SDL_GetTicks();
	for (int y=0; y<TEXSIZE; y++, ypos += ystep) {
		xpos = 0.0f;
		for (int x=0; x<TEXSIZE; x++, xpos += xstep) {
			toPoint = (topLeft + (xMov * xpos) + (yMov * ypos)).Normalized();
			
			CollisionContact c;
			space->TraceRay(camPos, toPoint, 1000000.0f, &c);

			if (c.triIdx != -1) {
				wank[x][y] = 100.0/(10*c.dist);
			} else {
				wank[x][y] = 0;
			}
		}
	}
	printf("%.3f million rays/sec, %.2f tri isect tests per ray\n", (TEXSIZE*TEXSIZE)/(1000.0*(SDL_GetTicks()-t)),
				GeomTree::stats_rayTriIntersections/(float)(TEXSIZE*TEXSIZE));
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mytexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, GL_LUMINANCE, GL_FLOAT, wank);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//glActiveTexture(GL_TEXTURE0);
	glDisable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2i(0,1);
		glVertex3f(1,1,0);

		glTexCoord2i(0,0);
		glVertex3f(0,1,0);
		
		glTexCoord2i(1,0);
		glVertex3f(0,0,0);
		
		glTexCoord2i(1,1);
		glVertex3f(1,0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}