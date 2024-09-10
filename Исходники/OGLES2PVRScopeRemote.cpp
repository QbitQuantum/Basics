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
bool OGLES2PVRScopeRemote::RenderScene()
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
			bool bRecompile = false;
			while(pplLibraryDirtyGetFirst(m_psSPSCommsData, &nItem, &nNewDataLen, &pData))
			{
				PVRShellOutputDebug("dirty item %u %u 0x%08x\n", nItem, nNewDataLen, pData);
				switch(nItem)
				{
				case 0:
					delete [] m_pszFragShader;
					m_pszFragShader = new char [nNewDataLen+1];
					strncpy(m_pszFragShader, (char*)pData, nNewDataLen);
					m_pszFragShader[nNewDataLen] = 0;
					bRecompile = true;
					break;

				case 1:
					delete [] m_pszVertShader;
					m_pszVertShader = new char [nNewDataLen+1];
					strncpy(m_pszVertShader, (char*)pData, nNewDataLen);
					m_pszVertShader[nNewDataLen] = 0;
					bRecompile = true;
					break;

				case 2:
					if(nNewDataLen == sizeof(SSPSCommsLibraryTypeFloat))
					{
						const SSPSCommsLibraryTypeFloat * const psData = (SSPSCommsLibraryTypeFloat*)pData;
						m_fMinThickness = psData->fCurrent;
					}
					break;
				case 3:
					if(nNewDataLen == sizeof(SSPSCommsLibraryTypeFloat))
					{
						const SSPSCommsLibraryTypeFloat * const psData = (SSPSCommsLibraryTypeFloat*)pData;
						m_fMaxVariation = psData->fCurrent;
					}
					break;
				}
			}

			if(bRecompile)
			{
				CPVRTString ErrorStr;
				glDeleteProgram(m_ShaderProgram.uiId);
				glDeleteShader(m_uiVertShader);
				glDeleteShader(m_uiFragShader);
				if (!LoadShaders(&ErrorStr, m_pszFragShader, m_pszVertShader))
				{
					PVRShellOutputDebug("%s", ErrorStr.c_str());
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