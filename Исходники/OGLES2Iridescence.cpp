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
bool OGLES2Iridescence::RenderScene()
{
	// Keyboard input (cursor up/down to change thickness variation)
	if (PVRShellIsKeyPressed(PVRShellKeyNameUP))
	{
		m_fMaxVariation += 1.0f;
	}
	else if (PVRShellIsKeyPressed(PVRShellKeyNameDOWN))
	{
		m_fMaxVariation = PVRT_MAX(0.0f, m_fMaxVariation - 1.0f);
	}

	// Keyboard input (cursor left/right to change minimum thickness)
	if (PVRShellIsKeyPressed(PVRShellKeyNameRIGHT))
	{
		m_fMinThickness += 1.0f;
	}
	else if (PVRShellIsKeyPressed(PVRShellKeyNameLEFT))
	{
		m_fMinThickness = PVRT_MAX(0.0f, m_fMinThickness - 1.0f);
	}

	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader program
	glUseProgram(m_ShaderProgram.uiId);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	// Rotate and Translation the model matrix
	PVRTMat4 mModel;
	mModel = PVRTMat4::RotationY(m_fAngleY);
	m_fAngleY += (2*PVRT_PI/60)/7;

	// Set model view projection matrix
	PVRTMat4 mModelView, mMVP;
	mModelView = m_mView * mModel;
	mMVP =  m_mProjection * mModelView;
	glUniformMatrix4fv(m_ShaderProgram.uiMVPMatrixLoc, 1, GL_FALSE, mMVP.ptr());

	// Set light direction in model space
	PVRTVec4 vLightDirModel;
	vLightDirModel = mModel.inverse() * PVRTVec4(1, 1, 1, 0);

	glUniform3fv(m_ShaderProgram.uiLightDirLoc, 1, &vLightDirModel.x);

	// Set eye position in model space
	PVRTVec4 vEyePosModel;
	vEyePosModel = mModelView.inverse() * PVRTVec4(0, 0, 0, 1);
	glUniform3fv(m_ShaderProgram.uiEyePosLoc, 1, &vEyePosModel.x);

	/*
		Set the iridescent shading parameters
	*/
	// Set the minimum thickness of the coating in nm
	glUniform1f(m_ShaderProgram.uiMinThicknessLoc, m_fMinThickness);

	// Set the maximum variation in thickness of the coating in nm
	glUniform1f(m_ShaderProgram.uiMaxVariationLoc, m_fMaxVariation);

	/*
		Now that the uniforms are set, call another function to actually draw the mesh.
	*/
	DrawMesh(0);

	m_Print3D.Print3D(2.0f, 10.0f, 0.75f, 0xffffffff, "Minimum Thickness:");
	m_Print3D.Print3D(2.0f, 15.0f, 0.75f, 0xffffffff, "%8.0f nm", m_fMinThickness);
	m_Print3D.Print3D(2.0f, 20.0f, 0.75f, 0xffffffff, "Maximum Variation:");
	m_Print3D.Print3D(2.0f, 25.0f, 0.75f, 0xffffffff, "%8.0f nm", m_fMaxVariation);

	// Displays the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	m_Print3D.DisplayDefaultTitle("Iridescence", "", ePVRTPrint3DLogoIMG);
	m_Print3D.Flush();

	return true;
}