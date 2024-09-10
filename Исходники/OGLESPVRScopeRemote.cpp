/*!****************************************************************************
 @Function		RenderScene
 @Return		bool		true if no error occurred
 @Description	Main rendering loop function of the program. The shell will
				call this function every frame.
				eglSwapBuffers() will be performed by PVRShell automatically.
				PVRShell will also manage important OS events.
				Will also manage relevant OS events. The user has access to
				these events through an abstraction layer provided by PVRShell.
******************************************************************************/
bool OGLESPVRScopeRemote::RenderScene()
{
	CPPLProcessingScoped PPLProcessingScoped(m_psSPSCommsData,
		__FUNCTION__, static_cast<unsigned int>(strlen(__FUNCTION__)), m_i32FrameCounter);

	if(m_psSPSCommsData)
	{
		// mark every N frames
		if(!(m_i32FrameCounter % 100))
		{
			char buf[128];
			const int nLen = sprintf(buf, "frame %u", m_i32FrameCounter);
			m_bCommsError |= !pplSendMark(m_psSPSCommsData, buf, nLen);
		}

		// Check for dirty items
		m_bCommsError |= !pplSendProcessingBegin(m_psSPSCommsData, "dirty", static_cast<unsigned int>(strlen("dirty")), m_i32FrameCounter);
		{
			unsigned int nItem, nNewDataLen;
			const char *pData;
			while(pplLibraryDirtyGetFirst(m_psSPSCommsData, &nItem, &nNewDataLen, &pData))
			{
				PVRShellOutputDebug("dirty item %u %u 0x%08x\n", nItem, nNewDataLen, pData);
				switch(nItem)
				{
				case 0:
					if(nNewDataLen == sizeof(SSPSCommsLibraryTypeFloat))
					{
						const SSPSCommsLibraryTypeFloat * const psData = (SSPSCommsLibraryTypeFloat*)pData;
						m_fMinThickness = psData->fCurrent;
					}
					break;
				case 1:
					if(nNewDataLen == sizeof(SSPSCommsLibraryTypeFloat))
					{
						const SSPSCommsLibraryTypeFloat * const psData = (SSPSCommsLibraryTypeFloat*)pData;
						m_fMaxVariation = psData->fCurrent;
					}
					break;
				}
			}
		}
		m_bCommsError |= !pplSendProcessingEnd(m_psSPSCommsData);
	}

	if (m_psSPSCommsData)
	{
		m_bCommsError |= !pplSendProcessingBegin(m_psSPSCommsData, "draw", static_cast<unsigned int>(strlen("draw")), m_i32FrameCounter);
	}

	// Clear the color and depth buffer
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

	if (m_psSPSCommsData)
	{
		m_bCommsError |= !pplSendProcessingEnd(m_psSPSCommsData);
		m_bCommsError |= !pplSendProcessingBegin(m_psSPSCommsData, "Print3D", static_cast<unsigned int>(strlen("Print3D")), m_i32FrameCounter);
	}

	// Displays the demo name using the tools. For a detailed explanation, see the example IntroducingPVRTools
	if(m_bCommsError)
	{
		m_Print3D.DisplayDefaultTitle("PVRScopeRemote", "Remote APIs\n\nError:\n  PVRScopeComms failed\n  Is PVRPerfServer connected?", ePVRTPrint3DSDKLogo);
		m_bCommsError = false;
	}
	else
		m_Print3D.DisplayDefaultTitle("PVRScopeRemote", "Remote APIs", ePVRTPrint3DSDKLogo);

	m_Print3D.Flush();

	if (m_psSPSCommsData)
	{
		m_bCommsError |= !pplSendProcessingEnd(m_psSPSCommsData);
	}

	// send counters
	m_anCounterReadings[eCounter]	= m_i32FrameCounter;
	m_anCounterReadings[eCounter10]	= m_i32Frame10Counter;
	if(m_psSPSCommsData)
	{
		m_bCommsError |= !pplCountersUpdate(m_psSPSCommsData, m_anCounterReadings);
	}

	// update some counters
	++m_i32FrameCounter;
	if(0 == (m_i32FrameCounter / 10) % 10)
	{
		m_i32Frame10Counter += 10;
	}

	return true;
}