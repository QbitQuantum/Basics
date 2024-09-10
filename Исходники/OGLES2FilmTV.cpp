void OGLES2FilmTV::DrawPODScene(PVRTMat4 &mViewProjection, bool bDrawCamera)
{
	// Clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get the position of the first light from the scene.
	PVRTVec4 vLightPosition = m_Scene.GetLightPosition(0);

	for(unsigned int i = 0; i < m_Scene.nNumMeshNode; ++i)
	{
		SPODNode& Node = m_Scene.pNode[i];

		// Get the node model matrix
		PVRTMat4 mWorld = m_Scene.GetWorldMatrix(Node);

		if(i == g_ui32CameraMesh)
		{
			if(!bDrawCamera)
				continue;

			// Rotate camera model
			mWorld =  m_MiniCamView.inverse() * mWorld;
		}
		else if(i == g_ui32TvScreen) // If we're drawing the TV screen change to the black and white shader
		{
			glUseProgram(m_BWShaderProgram.uiId);
		}

		// Pass the model-view-projection matrix (MVP) to the shader to transform the vertices
		PVRTMat4 mModelView, mMVP;
		mMVP = mViewProjection * mWorld;
		glUniformMatrix4fv(m_ShaderProgram.uiMVPMatrixLoc, 1, GL_FALSE, mMVP.f);

		// Pass the light position in model space to the shader
		PVRTVec4 vLightPos;
		vLightPos = mWorld.inverse() * vLightPosition;

		glUniform3fv(m_ShaderProgram.uiLightPosLoc, 1, &vLightPos.x);

		// Load the correct texture using our texture lookup table
		GLuint uiTex = 0;

		if(Node.nIdxMaterial != -1)
		{
            if(m_bFBOsCreated && Node.nIdxMaterial == m_uiTVScreen && m_i32Frame != 0)
				uiTex = m_uiTexture[1 - m_i32CurrentFBO];
			else
				uiTex = m_puiTextureIDs[Node.nIdxMaterial];
		}

		glBindTexture(GL_TEXTURE_2D, uiTex);

		/*
			Now that the model-view matrix is set and the materials ready,
			call another function to actually draw the mesh.
		*/
		DrawMesh(Node.nIdx);

		if(i == g_ui32TvScreen)
		{
			// Change back to the normal shader after drawing the g_ui32TvScreen
			glUseProgram(m_ShaderProgram.uiId);
		}
	}
}