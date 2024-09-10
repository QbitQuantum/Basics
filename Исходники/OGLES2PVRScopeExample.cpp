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
bool OGLES2PVRScopeExample::RenderScene()
{
	// Keyboard input (cursor up/down to cycle through counters)
	if(PVRShellIsKeyPressed(PVRShellKeyNameUP))
	{
		m_i32Counter++;

		if(m_i32Counter > (int) m_pScopeGraph->GetCounterNum())
			m_i32Counter = m_pScopeGraph->GetCounterNum();
	}

	if(PVRShellIsKeyPressed(PVRShellKeyNameDOWN))
	{
		m_i32Counter--;

		if(m_i32Counter < 0)
			m_i32Counter = 0;
	}

	if(PVRShellIsKeyPressed(PVRShellKeyNameACTION2))
		m_pScopeGraph->ShowCounter(m_i32Counter, !m_pScopeGraph->IsCounterShown(m_i32Counter));

	// Keyboard input (cursor left/right to change active group)
	if(PVRShellIsKeyPressed(PVRShellKeyNameRIGHT))
	{
		m_pScopeGraph->SetActiveGroup(m_pScopeGraph->GetActiveGroup()+1);
	}

	if(PVRShellIsKeyPressed(PVRShellKeyNameLEFT))
	{
		m_pScopeGraph->SetActiveGroup(m_pScopeGraph->GetActiveGroup()-1);
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

	char Description[256];

	if(m_pScopeGraph->GetCounterNum())
	{
		sprintf(Description, "Active Grp %i\n\nCounter %i (Grp %i) \nName: %s\nShown: %s\nuser y-axis: %.2f  max: %.2f%s",
			m_pScopeGraph->GetActiveGroup(), m_i32Counter,
			m_pScopeGraph->GetCounterGroup(m_i32Counter),
			m_pScopeGraph->GetCounterName(m_i32Counter),
			m_pScopeGraph->IsCounterShown(m_i32Counter) ? "Yes" : "No",
			m_pScopeGraph->GetMaximum(m_i32Counter),
			m_pScopeGraph->GetMaximumOfData(m_i32Counter),
			m_pScopeGraph->IsCounterPercentage(m_i32Counter) ? "%%" : "");
	}
	else
	{
		sprintf(Description, "No counters present");
	}

	// Displays the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	m_Print3D.DisplayDefaultTitle("PVRScopeExample", Description, ePVRTPrint3DSDKLogo);
	m_Print3D.Flush();

	// Update counters and draw the graph
	m_pScopeGraph->Ping();

	return true;
}