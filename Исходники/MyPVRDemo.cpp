// ---------------------------------------------------------------
void MyPVRDemo::RenderCurch(const PVRTMat4& mxCam)
	{
	PVRTMat4 mxModel = PVRTMat4::Identity();
	PVRTMat4 mxModelView = mxCam * mxModel;
	PVRTMat4 mxTexProj = m_mxLightBias * m_mxLightProj * m_mxLightView * mxCam.inverse();

	// --- Draw the floor reflected first, so we don't have to swap between GPU programs
	glUseProgram(m_ChurchReflShader.uiID);
	// Base map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex[enumTEXTURE_ChurchWalls]);
	// Light map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_tex[enumTEXTURE_ChurchLightmap]);

	glCullFace(GL_FRONT);
	PVRTMat4 mxReflChurchView = mxCam * PVRTMat4::Scale(1, -1, 1);
	glUniformMatrix4fv(m_ChurchReflShader.uiProjection, 1, GL_FALSE, m_mxProjection.ptr());
	glUniformMatrix4fv(m_ChurchReflShader.uiModelView, 1, GL_FALSE, mxReflChurchView.ptr());	// Reflected ModelView matrix
	DrawMesh(enumMODEL_Church, FLAG_VRT | FLAG_TEX0 | FLAG_TEX1);
	glCullFace(GL_BACK);

	// --- Activate the Church shader which utilises the Shadow Map.
	glUseProgram(m_ChurchShader.uiID);
	
	
	// --- Use the Shadow Map texture in texture unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTex);
	
	// --- Upload projection matrices
	glUniformMatrix4fv(m_ChurchShader.uiProjection, 1, GL_FALSE, m_mxProjection.ptr());	
	glUniformMatrix4fv(m_ChurchShader.uiTexProjection, 1, GL_FALSE, mxTexProj.ptr());
	glUniform1f(m_ChurchShader.uiAlpha, 1.0f);	// Set no alpha while we draw the walls.

	// --- Draw church walls	 (Textures are already bound)
	// Draw the walls as normal
	glUniformMatrix4fv(m_ChurchShader.uiModelView, 1, GL_FALSE, mxModelView.ptr());		// Standard ModelView matrix
	DrawMesh(enumMODEL_Church, FLAG_VRT | FLAG_TEX0 | FLAG_TEX1);

	// --- Draw floor
	glEnable(GL_BLEND);
	// Base map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex[enumTEXTURE_Floor]);
	// Light map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_tex[enumTEXTURE_FloorLightmap]);
	
	// Draw the floor
	glUniform1f(m_ChurchShader.uiAlpha, FLOOR_ALPHA);
	glUniformMatrix4fv(m_ChurchShader.uiModelView, 1, GL_FALSE, mxModelView.ptr());		// Standard ModelView matrix
	DrawMesh(enumMODEL_Floor, FLAG_VRT | FLAG_TEX0 | FLAG_TEX1);

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	}