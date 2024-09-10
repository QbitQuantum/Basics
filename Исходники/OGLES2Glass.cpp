/*!****************************************************************************
 @Function		DrawSkybox
 @Description	Draws the skybox onto the screen.
******************************************************************************/
void OGLES2Glass::DrawSkybox()
{
	glUseProgram(m_SkyboxProgram.uiId);

	PVRTMat4 mVP = m_mProjection * m_mView;
	PVRTMat4 mInvVP = mVP.inverseEx();

	glUniformMatrix4fv(m_SkyboxProgram.auiLoc[eInvVPMatrix], 1, GL_FALSE, mInvVP.ptr());

	PVRTVec3 vEyePos = m_mView.inverse() * PVRTVec4(0, 0, 0, 1);

	glUniform3fv(m_SkyboxProgram.auiLoc[eEyePos], 1, vEyePos.ptr());

	glBindBuffer(GL_ARRAY_BUFFER, m_uiSquareVbo);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiCubeTex);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}