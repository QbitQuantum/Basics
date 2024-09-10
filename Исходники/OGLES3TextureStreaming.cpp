/*!***************************************************************************
 @Function		DrawPODScene
 @Input         mViewProjection
 @Input         bDrawCamera
 @Description   Draws the scene described by the loaded POD file.
 *****************************************************************************/
void OGLES3TextureStreaming::DrawPODScene(const PVRTMat4 &mViewProjection)
{
	// Clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get the position of the first light from the scene.
	PVRTVec4 vLightPosition = m_Scene.GetLightPosition(0);
	int iTVCount            = 0;

#if defined(__ANDROID__)
	// Check if the MVP has changed
	if (m_Camera.HasImageChanged() && m_Camera.HasProjectionMatrixChanged())
	{
		m_TexCoordsProjection = PVRTMat4(m_Camera.GetProjectionMatrix());
	}
#endif

	for(unsigned int i = 0; i < m_Scene.nNumMeshNode; ++i)
	{
		SPODNode& Node = m_Scene.pNode[i];

		bool bIsTVScreen   = Node.nIdxMaterial == m_uiTVScreen;
		bool bIsRecordGlow = Node.nIdxMaterial == m_uiRecordGlow;

		// Get the node model matrix
		PVRTMat4 mWorld = m_Scene.GetWorldMatrix(Node);
		PVRTMat4 mModelView, mMVP;
		mMVP = mViewProjection * mWorld;

		GLint iMVPLoc = -1;
#if defined(__ANDROID__)
		GLint iTexProjLoc = -1;
#endif
		if(bIsTVScreen) // If we're drawing the TV screen change to the correct TV shader
		{
			_ASSERT(iTVCount < c_numTVScreens);
			if(c_screenEffects[iTVCount] == eTVNoise)
			{
				glUseProgram(m_TVNoiseShaderProgram.uiId);
				iMVPLoc = m_TVNoiseShaderProgram.uiMVP;
#if defined(__ANDROID__)
				iTexProjLoc = m_TVNoiseShaderProgram.uiVideoTexProjM;
#endif

				// Do the screen scrolling
				float fBandY1 = m_fBandScroll;
				float fBandY2 = fBandY1 + c_fBandWidth;
				glUniform2f(m_TVNoiseShaderProgram.uiScreenBand, fBandY1, fBandY2);

				// Do the noise
				PVRTVec2 vNoiseCoords;
				vNoiseCoords.x = (m_iNoiseCoordIdx % 4) * 0.25f;
				vNoiseCoords.y = (m_iNoiseCoordIdx / 4) * 0.25f;

				// Set the texmod value
				glUniform2f(m_TVNoiseShaderProgram.uiNoiseLoc, vNoiseCoords.x, vNoiseCoords.y);

				// Increment and reset
				m_iNoiseCoordIdx++;
				if(m_iNoiseCoordIdx >= 16)
					m_iNoiseCoordIdx = 0;
			}
			else if(c_screenEffects[iTVCount] == eTVGreyscale)
			{
				glUseProgram(m_TVGreyscaleShaderProgram.uiId);
				iMVPLoc = m_TVGreyscaleShaderProgram.uiMVP;
#if defined(__ANDROID__)
				iTexProjLoc = m_TVGreyscaleShaderProgram.uiVideoTexProjM;
#endif
			}
			else if(c_screenEffects[iTVCount] == eTVColour)
			{
				glUseProgram(m_TVShaderProgram.uiId);
				iMVPLoc = m_TVShaderProgram.uiMVP;
#if defined(__ANDROID__)
				iTexProjLoc = m_TVShaderProgram.uiVideoTexProjM;
#endif
			}
			else
			{
				_ASSERT(false); // Invalid enum
			}
			iTVCount++;
		}
		else if(bIsRecordGlow)
		{
			// Should the glow be active?
			unsigned long ulNow = PVRShellGetTime();
			if(ulNow - m_ulGlowTime > 1000)
			{
				m_bGlowState = !m_bGlowState;
				m_ulGlowTime = ulNow;
			}

			if(!m_bGlowState)
				continue;

			glEnable(GL_BLEND);
			glUseProgram(m_AmbientShaderProgram.uiId);
			iMVPLoc = m_AmbientShaderProgram.uiMVP;
		}
		else
		{
			glUseProgram(m_LitProgram.uiId);
			iMVPLoc = m_LitProgram.uiMVP;
		}

		glUniformMatrix4fv(iMVPLoc, 1, GL_FALSE, mMVP.f);

		// Pass the light position in model space to the shader. Don't do this for the TV screen.
		if(!bIsTVScreen && !bIsRecordGlow)
		{
			PVRTVec4 vLightPos;
			vLightPos = mWorld.inverse() * vLightPosition;

			glUniform3fv(m_LitProgram.uiLightPosition, 1, &vLightPos.x);
		}

		// Bind the correct texture
		if(Node.nIdxMaterial != -1)
		{
            if(Node.nIdxMaterial == m_uiTVScreen && m_i32Frame != 0)
			{
#if defined(__ANDROID__)
				GLuint yuvTexture = m_Camera.GetYUVTexture();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_EXTERNAL_OES, yuvTexture);

				// Set the sampler projection
				glUniformMatrix4fv(iTexProjLoc, 1, GL_FALSE, m_TexCoordsProjection.f);
#elif defined(__APPLE__)
				GLuint lumaTexure    = m_Camera.GetLuminanceTexture();
				GLuint chromaTexture = m_Camera.GetChrominanceTexture();
				GLenum lumaTarget    = m_Camera.GetLuminanceTextureTarget();
				GLenum chromaTarget  = m_Camera.GetChrominanceTextureTarget();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(lumaTarget, lumaTexure);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(chromaTarget, chromaTexture);
#endif

				if(c_screenEffects[iTVCount] == eTVNoise)
				{
					// Bind the noise texture
					glActiveTexture(GL_TEXTURE2);
					glBindTexture(GL_TEXTURE_2D, m_uiNoiseTex);
				}
			}
			else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_puiTextureIDs[Node.nIdxMaterial]);
			}
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		/*
		 Now that the model-view matrix is set and the materials ready,
		 call another function to actually draw the mesh.
		 */
		DrawMesh(Node.nIdx, (bIsTVScreen || bIsRecordGlow) ? false : true);

		if(bIsRecordGlow)
		{
			glDisable(GL_BLEND);
		}
	}
}