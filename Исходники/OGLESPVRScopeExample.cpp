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
bool OGLESPVRScopeExample::RenderScene()
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

	// Clears the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Loads the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjection.f);

	// Specify the modelview matrix
	PVRTMat4 mModel;
	SPODNode& Node = m_Scene.pNode[0];

	m_Scene.GetWorldMatrix(mModel, Node);

	// Rotate and Translate the model matrix
	m_fAngleY += (2*PVRT_PIf/60)/7;

	// Set model view projection matrix
	PVRTMat4 mModelView;
	mModelView = m_mView * PVRTMat4::RotationY(m_fAngleY) * mModel;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(mModelView.f);

	/*
		Load the light direction from the scene if we have one
	*/

	// Enables lighting. See BasicTnL for a detailed explanation
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set light direction
	PVRTVec4 vLightDirModel;
	vLightDirModel = mModel.inverse() * PVRTVec4(1, 1, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, (float*)&vLightDirModel.x);

	// Enable the vertex position attribute array
	glEnableClientState(GL_VERTEX_ARRAY);

	// bind the texture
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	/*
		Now that the model-view matrix is set and the materials are ready,
		call another function to actually draw the mesh.
	*/
	DrawMesh(Node.nIdx);

	// Disable the vertex positions
	glDisableClientState(GL_VERTEX_ARRAY);

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