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
bool OGLES2ChameleonMan::RenderScene()
{
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader program
	glUseProgram(m_SkinnedShaderProgram.uiId);

	if(PVRShellIsKeyPressed(PVRShellKeyNameACTION1))
	{
		m_bEnableDOT3 = !m_bEnableDOT3;
		glUniform1i(m_SkinnedShaderProgram.auiLoc[ebUseDot3], m_bEnableDOT3);
	}

	/*
		Calculates the frame number to animate in a time-based manner.
		Uses the shell function PVRShellGetTime() to get the time in milliseconds.
	*/
	unsigned long iTime = PVRShellGetTime();

	if(iTime > m_iTimePrev)
	{
		float fDelta = (float) (iTime - m_iTimePrev);
		m_fFrame += fDelta * g_fDemoFrameRate;

		// Increment the counters to make sure our animation works
		m_fLightPos	+= fDelta * 0.0034f;
		m_fWallPos	+= fDelta * 0.00027f;
		m_fBackgroundPos += fDelta * -0.000027f;

		// Wrap the Animation back to the Start
		if(m_fLightPos >= PVRT_TWO_PI)
			m_fLightPos -= PVRT_TWO_PI;

		if(m_fWallPos >= PVRT_TWO_PI)
			m_fWallPos -= PVRT_TWO_PI;

		if(m_fBackgroundPos <= 0)
			m_fBackgroundPos += 1.0f;

		if(m_fFrame > m_Scene.nNumFrame - 1)
			m_fFrame = 0;
	}

	m_iTimePrev	= iTime;

	// Set the scene animation to the current frame
	m_Scene.SetFrame(m_fFrame);

	// Set up camera
	PVRTVec3	vFrom, vTo, vUp(0.0f, 1.0f, 0.0f);
	PVRTMat4 mView, mProjection;
	PVRTVec3	LightPos;
	float fFOV;
	int i;

	bool bRotate = PVRShellGet(prefIsRotated) && PVRShellGet(prefFullScreen);

	// Get the camera position, target and field of view (fov)
	if(m_Scene.pCamera[0].nIdxTarget != -1) // Does the camera have a target?
		fFOV = m_Scene.GetCameraPos( vFrom, vTo, 0); // vTo is taken from the target node
	else
		fFOV = m_Scene.GetCamera( vFrom, vTo, vUp, 0); // vTo is calculated from the rotation

	fFOV *= bRotate ? (float)PVRShellGet(prefWidth)/(float)PVRShellGet(prefHeight) : (float)PVRShellGet(prefHeight)/(float)PVRShellGet(prefWidth);

	/*
		We can build the model view matrix from the camera position, target and an up vector.
		For this we use PVRTMat4::LookAtRH().
	*/
	mView = PVRTMat4::LookAtRH(vFrom, vTo, vUp);

	// Calculate the projection matrix
	mProjection = PVRTMat4::PerspectiveFovRH(fFOV,  (float)PVRShellGet(prefWidth)/(float)PVRShellGet(prefHeight), g_fCameraNear, g_fCameraFar, PVRTMat4::OGL, bRotate);

	// Update Light Position and related VGP Program constant
	LightPos.x = 200.0f;
	LightPos.y = 350.0f;
	LightPos.z = 200.0f * PVRTABS(sin((PVRT_PI / 4.0f) + m_fLightPos));

	glUniform3fv(m_SkinnedShaderProgram.auiLoc[eLightPos], 1, LightPos.ptr());

	// Set up the View * Projection Matrix
	PVRTMat4 mViewProjection;

	mViewProjection = mProjection * mView;
	glUniformMatrix4fv(m_SkinnedShaderProgram.auiLoc[eViewProj], 1, GL_FALSE, mViewProjection.ptr());

	// Enable the vertex attribute arrays
	for(i = 0; i < eNumAttribs; ++i) glEnableVertexAttribArray(i);

	// Draw skinned meshes
	for(unsigned int i32NodeIndex = 0; i32NodeIndex < 3; ++i32NodeIndex)
	{
		// Bind correct texture
		switch(i32NodeIndex)
		{
			case eBody:
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexHeadNormalMap);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexHeadBody);
				break;
			case eLegs:
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexLegsNormalMap);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexLegs);
				break;
			default:
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexBeltNormalMap);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_ui32TexBelt);
				break;
		}

		DrawSkinnedMesh(i32NodeIndex);
	}

	// Safely disable the vertex attribute arrays
	for(i = 0; i < eNumAttribs; ++i) glDisableVertexAttribArray(i);

	// Draw non-skinned meshes
	glUseProgram(m_DefaultShaderProgram.uiId);

	// Enable the vertex attribute arrays
	for(i = 0; i < eNumDefaultAttribs; ++i) glEnableVertexAttribArray(i);

	for(unsigned int i32NodeIndex = 3; i32NodeIndex < m_Scene.nNumMeshNode; ++i32NodeIndex)
	{
		SPODNode& Node = m_Scene.pNode[i32NodeIndex];
		SPODMesh& Mesh = m_Scene.pMesh[Node.nIdx];

		// bind the VBO for the mesh
		glBindBuffer(GL_ARRAY_BUFFER, m_puiVbo[Node.nIdx]);

		// bind the index buffer, won't hurt if the handle is 0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_puiIndexVbo[Node.nIdx]);

		// Get the node model matrix
		PVRTMat4 mWorld;
		mWorld = m_Scene.GetWorldMatrix(Node);

		// Setup the appropriate texture and transformation (if needed)
		switch(i32NodeIndex)
		{
			case eWall:
				glBindTexture(GL_TEXTURE_2D, m_ui32TexWall);

				// Rotate the wall mesh which is circular
				mWorld *= PVRTMat4::RotationY(m_fWallPos);

				glUniform1f(m_DefaultShaderProgram.auiLoc[eDefaultUOffset], 0);

				break;
			case eBackground:
				glBindTexture(GL_TEXTURE_2D, m_ui32TexSkyLine);

				glUniform1f(m_DefaultShaderProgram.auiLoc[eDefaultUOffset], m_fBackgroundPos);
				break;
			case eLights:
				{
					glBindTexture(GL_TEXTURE_2D, m_ui32TexLamp);

					PVRTMat4 mWallWorld = m_Scene.GetWorldMatrix(m_Scene.pNode[eWall]);
					mWorld = mWallWorld * PVRTMat4::RotationY(m_fWallPos) * mWallWorld.inverse() * mWorld;

					glUniform1f(m_DefaultShaderProgram.auiLoc[eDefaultUOffset], 0);
				}
				break;
			default:
			break;
		};

		// Set up shader uniforms
		PVRTMat4 mModelViewProj;
		mModelViewProj = mViewProjection * mWorld;
		glUniformMatrix4fv(m_DefaultShaderProgram.auiLoc[eDefaultMVPMatrix], 1, GL_FALSE, mModelViewProj.ptr());

		// Set the vertex attribute offsets
		glVertexAttribPointer(DEFAULT_VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, Mesh.sVertex.nStride,  Mesh.sVertex.pData);
		glVertexAttribPointer(DEFAULT_TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, Mesh.psUVW[0].nStride, Mesh.psUVW[0].pData);

		// Indexed Triangle list
		glDrawElements(GL_TRIANGLES, Mesh.nNumFaces*3, GL_UNSIGNED_SHORT, 0);
	}

	// Safely disable the vertex attribute arrays
	for(i = 0; i < eNumAttribs; ++i) glDisableVertexAttribArray(i);

	// unbind the VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Display the demo name using the tools. For a detailed explanation, see the training course IntroducingPVRTools
	const char * pDescription;

	if(m_bEnableDOT3)
		pDescription = "Skinning with DOT3 Per Pixel Lighting";
	else
		pDescription = "Skinning with Vertex Lighting";

	m_Print3D.DisplayDefaultTitle("Chameleon Man", pDescription, ePVRTPrint3DSDKLogo);
	m_Print3D.Flush();

	return true;
}