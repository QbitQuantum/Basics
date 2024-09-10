	void	render()
	{
	

		
		btScalar childMat[16];
		m_bulletObject->getWorldTransform().getOpenGLMatrix(childMat);

		if (m_texture)
		{
			m_texture->initOpenGLTexture();

			glBindTexture(GL_TEXTURE_2D,m_texture->m_textureName);

			glEnable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_GEN_R);
			
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glDepthFunc (GL_LEQUAL);
			glDisable(GL_BLEND);
			glEnable (GL_DEPTH_TEST);

			glMatrixMode(GL_TEXTURE);
			
			
			glMatrixMode(GL_MODELVIEW);


		} else
		{
			glDisable(GL_TEXTURE_2D);
		}

		glDisable(GL_LIGHTING);
		glPushMatrix();
		
		
		btglMultMatrix(childMat);
		
		//glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
		
		glBegin(GL_TRIANGLES);
		
		glColor4f(1, 1, 1,1);
		
		for (int i=0;i<m_indices.size();i++)
		{
			glNormal3f(1.f,0.f,0.f);
			glTexCoord2f(m_vertices[m_indices[i]].m_uv1[0],m_vertices[m_indices[i]].m_uv1[1]);
			glVertex3f(m_vertices[m_indices[i]].m_localxyz.getX(),m_vertices[m_indices[i]].m_localxyz.getY(),m_vertices[m_indices[i]].m_localxyz.getZ());
			
		}
		glEnd();

		glPopMatrix();
		
	}