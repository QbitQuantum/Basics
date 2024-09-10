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
bool OGLES3Skinning::RenderScene()
{
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader program
	glUseProgram(m_ShaderProgram.uiId);
	glActiveTexture(GL_TEXTURE0);

	/*
		Calculates the frame number to animate in a time-based manner.
		Uses the shell function PVRShellGetTime() to get the time in milliseconds.
	*/
	unsigned long iTime = PVRShellGetTime();

	if(iTime > m_iTimePrev)
	{
		float fDelta = (float) (iTime - m_iTimePrev);
		m_fFrame += fDelta * g_fDemoFrameRate;

		// Modify the transformation matrix if it is needed
		bool bRebuildTransformation = false;

		if(PVRShellIsKeyPressed(PVRShellKeyNameRIGHT))
		{
			m_fAngle -= 0.03f;

			if(m_fAngle < PVRT_TWO_PIf)
				m_fAngle += PVRT_TWO_PIf;

			bRebuildTransformation = true;
		}

		if(PVRShellIsKeyPressed(PVRShellKeyNameLEFT))
		{
			m_fAngle += 0.03f;

			if(m_fAngle > PVRT_TWO_PIf)
				m_fAngle -= PVRT_TWO_PIf;

			bRebuildTransformation = true;
		}

		if(PVRShellIsKeyPressed(PVRShellKeyNameUP))
		{
			m_fDistance -= 10.0f;

			if(m_fDistance < -500.0f)
				m_fDistance = -500.0f;

			bRebuildTransformation = true;
		}

		if(PVRShellIsKeyPressed(PVRShellKeyNameDOWN))
		{
			m_fDistance += 10.0f;

			if(m_fDistance > 200.0f)
				m_fDistance = 200.0f;

			bRebuildTransformation = true;
		}

		if(bRebuildTransformation)
			m_Transform = PVRTMat4::Translation(0,0, m_fDistance) * PVRTMat4::RotationY(m_fAngle);

	}

	m_iTimePrev	= iTime;

	if(m_fFrame > m_Scene.nNumFrame - 1)
		m_fFrame = 0;

	// Set the scene animation to the current frame
	m_Scene.SetFrame(m_fFrame);

	/*
		Set up camera
	*/
	PVRTVec3	vFrom, vTo, vUp(0, 1, 0);
	PVRTMat4 mView, mProjection;
	float fFOV;

	// We can get the camera position, target and field of view (fov) with GetCameraPos()
	fFOV = m_Scene.GetCamera(vFrom, vTo, vUp, 0);

	/*
		We can build the model view matrix from the camera position, target and an up vector.
		For this we use PVRTMat4::LookAtRH().
	*/
	mView = PVRTMat4::LookAtRH(vFrom, vTo, vUp);

	// Calculate the projection matrix
	bool bRotate = PVRShellGet(prefIsRotated) && PVRShellGet(prefFullScreen);
	mProjection = PVRTMat4::PerspectiveFovRH(fFOV,  (float)PVRShellGet(prefWidth)/(float)PVRShellGet(prefHeight), g_fCameraNear, g_fCameraFar, PVRTMat4::OGL, bRotate);

	// Read the light direction from the scene
	PVRTVec4 vLightDirWorld = PVRTVec4( 0, 0, 0, 0 );
	vLightDirWorld = m_Scene.GetLightDirection(0);
	glUniform3fv(m_ShaderProgram.auiLoc[eLightDirWorld], 1, &vLightDirWorld.x);

	// Set up the View * Projection Matrix
	PVRTMat4 mViewProjection;

	mViewProjection = mProjection * mView;
	glUniformMatrix4fv(m_ShaderProgram.auiLoc[eViewProj], 1, GL_FALSE, mViewProjection.ptr());

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
	for (unsigned int i32NodeIndex = 0; i32NodeIndex < m_Scene.nNumMeshNode; ++i32NodeIndex)
	{
		SPODNode& Node = m_Scene.pNode[i32NodeIndex];

		// Get the node model matrix
		PVRTMat4 mWorld;
		mWorld = m_Scene.GetWorldMatrix(Node);

		// Set up shader uniforms
		PVRTMat4 mModelViewProj;
		mModelViewProj = mViewProjection * mWorld;
		glUniformMatrix4fv(m_ShaderProgram.auiLoc[eMVPMatrix], 1, GL_FALSE, mModelViewProj.ptr());

		PVRTVec4 vLightDirModel;
		vLightDirModel = mWorld.inverse() * vLightDirWorld;
		glUniform3fv(m_ShaderProgram.auiLoc[eLightDirModel], 1, &vLightDirModel.x);

		// Loads the correct texture using our texture lookup table
		if(Node.nIdxMaterial == -1)
			glBindTexture(GL_TEXTURE_2D, 0); // It has no pMaterial defined. Use blank texture (0)
		else
			glBindTexture(GL_TEXTURE_2D, m_puiTextures[Node.nIdxMaterial]);

		DrawMesh(i32NodeIndex);
	}

	// Display the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	m_Print3D.DisplayDefaultTitle("Skinning", "", ePVRTPrint3DSDKLogo);
	m_Print3D.Flush();

	return true;
}