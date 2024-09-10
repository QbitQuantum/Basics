void RenderPipe_depth_opengl::render( GLuint target )
{
	glDepthMask(GL_FALSE);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, target);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glUseProgram(m_pipeProgramID);

	GLuint reg = glGetUniformLocation(m_pipeProgramID, "u_image");
	glUniform1i(reg, 0);
	reg = glGetUniformLocation(m_pipeProgramID, "u_blurredImage");
	glUniform1i(reg, 1);
	reg = glGetUniformLocation(m_pipeProgramID, "u_zBuffer");
	glUniform1i(reg, 2);

	CMatrix inverProjMat = GetProjectionMatrix();
	inverProjMat.Invert();

	m_zInv = inverProjMat.GetColumn(3);	// only need to calculate z value, so only 4th column is needed.

	m_depthOfField = GetDepthOfFieldFactors();

	reg = glGetUniformLocation(m_pipeProgramID, "u_depthOfField");
	if (reg >= 0)
		glUniform4fv(reg, 1, (float *)&m_depthOfField);
	if (reg >= 0)
		reg = glGetUniformLocation(m_pipeProgramID, "u_zInv");
	glUniform4fv(reg, 1, (float *)&m_zInv);


	glActiveTexture(GL_TEXTURE0_ARB);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, m_image);

	glActiveTexture(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, m_blurredImage);

	glActiveTexture(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glActiveTexture(GL_TEXTURE0_ARB);

	renderScreenQuad();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glDepthMask(GL_TRUE);
}