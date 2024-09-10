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
bool OGLESIntroducingPFX::RenderScene()
{
	// Clears the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the loaded effect
	m_pEffect->Activate();

	/*
		Calculates the frame number to animate in a time-based manner.
		Uses the shell function PVRShellGetTime() to get the time in milliseconds.
	*/
	int iTime = PVRShellGetTime();
	int iDeltaTime = iTime - m_iTimePrev;
	m_iTimePrev	= iTime;
	m_fFrame	+= (float)iDeltaTime * DEMO_FRAME_RATE;
	if (m_fFrame > m_Scene.nNumFrame-1)
		m_fFrame = 0;

	// Sets the scene animation to this frame
	m_Scene.SetFrame(m_fFrame);

	{
		PVRTVec3	vFrom, vTo, vUp;
		VERTTYPE	fFOV;
		vUp.x = 0.0f;
		vUp.y = 1.0f;
		vUp.z = 0.0f;

		// We can get the camera position, target and field of view (fov) with GetCameraPos()
		fFOV = m_Scene.GetCameraPos(vFrom, vTo, 0) * 0.4f;

		/*
			We can build the world view matrix from the camera position, target and an up vector.
			For this we use PVRTMat4LookAtRH().
		*/
		m_mView = PVRTMat4::LookAtRH(vFrom, vTo, vUp);

		// Calculates the projection matrix
		bool bRotate = PVRShellGet(prefIsRotated) && PVRShellGet(prefFullScreen);
		m_mProjection = PVRTMat4::PerspectiveFovRH(fFOV, (float)PVRShellGet(prefWidth)/(float)PVRShellGet(prefHeight), CAM_NEAR, CAM_FAR, PVRTMat4::OGL, bRotate);
	}

	/*
		A scene is composed of nodes. There are 3 types of nodes:
		- MeshNodes :
			references a mesh in the pMesh[].
			These nodes are at the beginning of the pNode[] array.
			And there are nNumMeshNode number of them.
			This way the .pod format can instantiate several times the same mesh
			with different attributes.
		- lights
		- cameras
		To draw a scene, you must go through all the MeshNodes and draw the referenced meshes.
	*/
	for (int i=0; i<(int)m_Scene.nNumMeshNode; i++)
	{
		SPODNode* pNode = &m_Scene.pNode[i];

		// Gets pMesh referenced by the pNode
		SPODMesh* pMesh = &m_Scene.pMesh[pNode->nIdx];

		glBindBuffer(GL_ARRAY_BUFFER, m_aiVboID[i]);

		// Gets the node model matrix
		PVRTMat4 mWorld;
		mWorld = m_Scene.GetWorldMatrix(*pNode);

		PVRTMat4 mWorldView;
		mWorldView = m_mView * mWorld;

		for(unsigned int j = 0; j < m_nUniformCnt; ++j)
		{
			switch(m_psUniforms[j].nSemantic)
			{
			case eUsPOSITION:
				{
					glVertexAttribPointer(m_psUniforms[j].nLocation, 3, GL_FLOAT, GL_FALSE, pMesh->sVertex.nStride, pMesh->sVertex.pData);
					glEnableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			case eUsNORMAL:
				{
					glVertexAttribPointer(m_psUniforms[j].nLocation, 3, GL_FLOAT, GL_FALSE, pMesh->sNormals.nStride, pMesh->sNormals.pData);
					glEnableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			case eUsUV:
				{
					glVertexAttribPointer(m_psUniforms[j].nLocation, 2, GL_FLOAT, GL_FALSE, pMesh->psUVW[0].nStride, pMesh->psUVW[0].pData);
					glEnableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			case eUsWORLDVIEWPROJECTION:
				{
					PVRTMat4 mWVP;

					/* Passes the world-view-projection matrix (WVP) to the shader to transform the vertices */
					mWVP = m_mProjection * mWorldView;
					glUniformMatrix4fv(m_psUniforms[j].nLocation, 1, GL_FALSE, mWVP.f);
				}
				break;
			case eUsWORLDVIEWIT:
				{
					PVRTMat4 mWorldViewI, mWorldViewIT;

					/* Passes the inverse transpose of the world-view matrix to the shader to transform the normals */
					mWorldViewI  = mWorldView.inverse();
					mWorldViewIT = mWorldViewI.transpose();

					PVRTMat3 WorldViewIT = PVRTMat3(mWorldViewIT);

					glUniformMatrix3fv(m_psUniforms[j].nLocation, 1, GL_FALSE, WorldViewIT.f);
				}
				break;
			case eUsLIGHTDIREYE:
				{
					// Reads the light direction from the scene.
					PVRTVec4 vLightDirection;
					PVRTVec3 vPos;
					vLightDirection = m_Scene.GetLightDirection(0);

					vLightDirection.x = -vLightDirection.x;
					vLightDirection.y = -vLightDirection.y;
					vLightDirection.z = -vLightDirection.z;

					/*
						Sets the w component to 0, so when passing it to glLight(), it is
						considered as a directional light (as opposed to a spot light).
					*/
					vLightDirection.w = 0;

					// Passes the light direction in eye space to the shader
					PVRTVec4 vLightDirectionEyeSpace;
					vLightDirectionEyeSpace = m_mView * vLightDirection;

					glUniform3f(m_psUniforms[j].nLocation, vLightDirectionEyeSpace.x, vLightDirectionEyeSpace.y, vLightDirectionEyeSpace.z);
				}
				break;
			case eUsTEXTURE:
				{
					// Set the sampler variable to the texture unit
					glUniform1i(m_psUniforms[j].nLocation, m_psUniforms[j].nIdx);
				}
				break;
			}
		}

		/*
			Now that the model-view matrix is set and the materials ready,
			call another function to actually draw the mesh.
		*/
		DrawMesh(pMesh);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for(unsigned int j = 0; j < m_nUniformCnt; ++j)
		{
			switch(m_psUniforms[j].nSemantic)
			{
			case eUsPOSITION:
				{
					glDisableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			case eUsNORMAL:
				{
					glDisableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			case eUsUV:
				{
					glDisableVertexAttribArray(m_psUniforms[j].nLocation);
				}
				break;
			}
		}
	}

	// Displays the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	m_Print3D.DisplayDefaultTitle("IntroducingPFX", "", ePVRTPrint3DLogoIMG);
	m_Print3D.Flush();

	return true;
}