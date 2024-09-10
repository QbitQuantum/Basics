void IEngine::drawScene()
{
	
	p.startDraw();
	
	if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	glActiveTexture(GL_TEXTURE2);
	bindImage(0);

	glActiveTexture(GL_TEXTURE3);
	bindImage(0);
	
	glActiveTexture(GL_TEXTURE4);
	bindImage(0);

	glTranslatef(0, -c_pos.y, 0);

	//glTranslatef(0, -25, 0);	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);
	skybox->draw();
	
	glPopMatrix();

	
	float ref_pitch = pitch;
	vec3 ref_pos = water->getReflectionPosition(c_pos, ref_pitch);
	
	int drawx, drawz;
	drawx = (int) (c_pos.x / CHUNK_SIZE);
	drawz = (int) (c_pos.z / CHUNK_SIZE);
	
	//////////////////////////////////////
	/// Draw the inverted terrain
	//////////////////////////////////////
	
	if(c_pos.y > 0.0){
	
		glPushMatrix();
		glLoadIdentity();
	
		glRotatef(-pitch, 1,0,0);
		glRotatef(-yaw, 0,1,0);
		glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);
		//water->protectDepthBuffer();
		//water->stencilBuffer(c_pos, pitch, yaw);
		
		sh2->bind();
		
		glActiveTexture(GL_TEXTURE2);
		bindImage(tex);
	
		glActiveTexture(GL_TEXTURE3);
		bindImage(tex2);
	
		glActiveTexture(GL_TEXTURE4);
		bindImage(tex3);
	
		sh2->setUniform1i((char*)"tex", 2);
		sh2->setUniform1i((char*)"tex2", 3);
		sh2->setUniform1i((char*)"tex3", 4);
		
		sh2->setUniform1f("time", frames * .1);
		w.drawAt(drawx,0,drawz);
		sh2->release();
	
	}
	
	//////////////////////////////////////////
	/// Draw the water polygon
	//////////////////////////////////////////
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
	static int inc = 20;
	glColor4f(0.0,.05,.1,.6);
	for(int i = -1000; i < 1000; i+=inc){
		for(int j = -1000; j < 1000; j+=inc){
			glVertex3f(i, 0, j);
			glVertex3f(i+inc, 0, j);
			glVertex3f(i+inc, 0, j+inc);
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+inc);
			glVertex3f(i+inc, 0, j+inc);
		}
	}
	glEnd();
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
		
	//////////////////////////////////////
	///  Draw the primary terrain
	//////////////////////////////////////
	glPushMatrix();
	glLoadIdentity();
	
	glRotatef(-pitch, 1,0,0);
	glRotatef(-yaw, 0,1,0);

	glTranslatef(-c_pos.x, -c_pos.y, -c_pos.z);

	sh->bind();
	
	glActiveTexture(GL_TEXTURE2);
	bindImage(tex);
	
	glActiveTexture(GL_TEXTURE3);
	bindImage(tex2);
	
	glActiveTexture(GL_TEXTURE4);
	bindImage(tex3);
	
	sh->setUniform1i((char*)"tex", 2);
	sh->setUniform1i((char*)"tex2", 3);
	sh->setUniform1i((char*)"tex3", 4);
	
	w.drawAt(drawx,0,drawz);
	glPopMatrix();

	sh->release();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	p.draw();
	
	
}