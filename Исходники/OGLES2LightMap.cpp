/*!****************************************************************************
 @Function		RenderScene
 @Return		bool		true if no error occured
 @Description	Main rendering loop function of the program. The shell will
				call this function every frame.
				eglSwapBuffers() will be performed by PVRShell automatically.
				PVRShell will also manage important OS events.
				Will also manage relevent OS events. The user has access to
				these events through an abstraction layer provided by PVRShell.
******************************************************************************/
bool OGLES2LightMap::RenderScene()
{
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader program
	glUseProgram(m_ShaderProgram.uiId);

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiBaseTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_uiReflectTex);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_uiShadowTex);

	// draw two models, mask and plane
	for (int i = 0; i < eNumModels; ++i)
	{
		// rotate and translate the model matrix
		PVRTMat4 mModel;

		if (i == eMask)
		{
			PVRTMat4 mRotX, mRotY;
			mRotX = PVRTMat4::RotationX(m_fAngleX);
			m_fAngleX += PVRT_PI / 300;
			mRotY = PVRTMat4::RotationY(m_fAngleY);
			m_fAngleY += PVRT_PI / 250;

			mModel = mRotY * mRotX;
		}
		else
		{
			mModel = PVRTMat4::Translation(0.0, 0.0, -25);
		}

		// Set model view projection matrix
		PVRTMat4 mModelView, mMVP;
		mModelView = m_mView * mModel;
		mMVP = m_mProjection * mModelView;
		glUniformMatrix4fv(m_ShaderProgram.auiLoc[eMVPMatrix], 1, GL_FALSE, mMVP.ptr());

		// Set shadow projection matrix
		PVRTMat4 mShadowProj;
		mShadowProj = m_mShadowViewProj * mModel;
		glUniformMatrix4fv(m_ShaderProgram.auiLoc[eShadowProj], 1, GL_FALSE, mShadowProj.ptr());

		// Set model world matrix
		PVRTMat3 fModelWorld = PVRTMat3(mModel);

		glUniformMatrix3fv(m_ShaderProgram.auiLoc[eModelWorld], 1, GL_FALSE, fModelWorld.ptr());

		// Set light position in model space
		PVRTVec4 vLightDirModel;
		vLightDirModel =  mModel.inverse() *  PVRTVec4( 1, 1, 1, 0 );

		glUniform3fv(m_ShaderProgram.auiLoc[eLightDirModel], 1, &vLightDirModel.x);

		// Set eye position in model space
		PVRTVec4 vEyePosModel;
		vEyePosModel = mModelView.inverse() * PVRTVec4(0, 0, 0, 1);

		glUniform3fv(m_ShaderProgram.auiLoc[eEyePosModel], 1, &vEyePosModel.x);

		m_Models[i].DrawMesh(0);
	}

	// Displays the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	m_Print3D.DisplayDefaultTitle("LightMap", "", ePVRTPrint3DSDKLogo);
	m_Print3D.Flush();

	return true;
}