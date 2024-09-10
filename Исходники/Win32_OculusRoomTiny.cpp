//-------------------------------------------------------------------------------------
void ProcessAndRender()
{
#if 0
	//HRESULT hr = pRender->Device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//OVR_ASSERT(SUCCEEDED(hr));

	pRender->Clear();
	pRender->BeginScene();

	Vector3f eye(0.0f, 0.0f, -5.0f);
	Vector3f lookat(0.0f, 0.0f, 0.0f);
	Vector3f up(0.0f, 1.0f, 0.0f);
	Matrix4f view = Matrix4f::LookAtLH(eye, lookat, up);
	//Matrix4f proj = Matrix4f::PerspectiveLH(3.14145f / 2, 800.0f / 600.0f, 1.0f, 10000.0f);

	ovrFovPort fov = { 1, 1, 1, 1 };
	Matrix4f proj = ovrMatrix4f_Projection(fov, 1.0f, 10000.0f, false);

	pRender->SetProjection(proj);
	pRoomScene->Render(pRender, view);

	pRender->EndScene();
	pRender->Present();
#endif

	static ovrPosef eyeRenderPose[2];
	ovrHmd_BeginFrameTiming(HMD, 0);

	// Adjust eye position and rotation from controls, maintaining y position from HMD.
	static float BodyYaw(3.141592f);
	static Vector3f HeadPos(0.0f, 1.6f, -5.0f);
	HeadPos.y = ovrHmd_GetFloat(HMD, OVR_KEY_EYE_HEIGHT, HeadPos.y);
	bool freezeEyeRender = false;

	pRender->BeginScene();

	if (!freezeEyeRender)
	{
		pRender->SetRenderTarget(pRendertargetTexture);
		pRender->SetViewport(Recti(0, 0, pRendertargetTexture->Width, pRendertargetTexture->Height));
		pRender->Clear();
		for (int eyeIndex = 0; eyeIndex < ovrEye_Count; ++eyeIndex)
		{
			ovrEyeType eye = HMD->EyeRenderOrder[eyeIndex];
			eyeRenderPose[eye] = ovrHmd_GetEyePose(HMD, eye);

			// Get view and projection matrices
			Matrix4f rollPitchYaw = Matrix4f::RotationY(BodyYaw);
			Matrix4f finalRollPitchYaw = rollPitchYaw * Matrix4f(eyeRenderPose[eye].Orientation);
			Vector3f finalUp = finalRollPitchYaw.Transform(Vector3f(0, 1, 0));
			Vector3f finalForward = finalRollPitchYaw.Transform(Vector3f(0, 0, -1));
			Vector3f shiftedEyePos      = HeadPos + rollPitchYaw.Transform(eyeRenderPose[eye].Position);
			//Matrix4f view = Matrix4f::LookAtRH(shiftedEyePos, shiftedEyePos + finalForward, finalUp); 
			//Matrix4f proj = ovrMatrix4f_Projection(EyeRenderDesc[eye].Fov, 0.01f, 10000.0f, true);
			Matrix4f view = Matrix4f::LookAtLH(shiftedEyePos, shiftedEyePos + finalForward, finalUp);
			Matrix4f proj = ovrMatrix4f_Projection(EyeRenderDesc[eye].Fov, 0.01f, 10000.0f, false);

			pRender->SetViewport(Recti(EyeRenderViewport[eye]));
			pRender->SetProjection(proj);
			pRender->SetDepthMode(true, true);
			pRoomScene->Render(pRender, Matrix4f::Translation(EyeRenderDesc[eye].ViewAdjust) * view);
		}
	}

	pRender->SetDefaultRenderTarget();
	pRender->SetFullViewport();
	pRender->Clear(0.0f, 0.0f, 0.0f, 0.0f);

	ShaderFill distortionShaderFill(DistortionShaders);
	distortionShaderFill.SetTexture(0, pRendertargetTexture);

	for (int eyeNum = 0; eyeNum < ovrEye_Count; eyeNum++)
	{
		// Get and set shader constants
		DistortionShaders->SetUniform2f("EyeToSourceUVScale", UVScaleOffset[eyeNum][0].x, UVScaleOffset[eyeNum][0].y);
		DistortionShaders->SetUniform2f("EyeToSourceUVOffset", UVScaleOffset[eyeNum][1].x, UVScaleOffset[eyeNum][1].y);
		ovrMatrix4f timeWarpMatrices[2];
		ovrHmd_GetEyeTimewarpMatrices(HMD, (ovrEyeType)eyeNum, eyeRenderPose[eyeNum], timeWarpMatrices);
		DistortionShaders->SetUniform4x4f("EyeRotationStart", timeWarpMatrices[0]);  //Nb transposed when set
		DistortionShaders->SetUniform4x4f("EyeRotationEnd", timeWarpMatrices[1]);  //Nb transposed when set
		// Perform distortion
		pRender->Render(&distortionShaderFill, DistortionDecl, MeshVBs[eyeNum], MeshIBs[eyeNum],
			sizeof(ovrDistortionVertex), Matrix4f(), MeshVBCnts[eyeNum], MeshIBCnts[eyeNum], Prim_Triangles);
		//Render(fill, vertices, indices, stride, Matrix4f(), 0,(int)vertices->GetSize(), Prim_Triangles, false);
		//(&distortionShaderFill, MeshVBs[eyeNum], MeshIBs[eyeNum],sizeof(ovrDistortionVertex));
	}

	/*
	pRender->SetDefaultRenderTarget();
	pRender->SetFullViewport();
	pRender->Clear(0.0f, 0.0f, 0.0f, 0.0f);

	Vector3f eye(0.0f, 0.0f, -5.0f);
	Vector3f lookat(0.0f, 0.0f, 0.0f);
	Vector3f up(0.0f, 1.0f, 0.0f);
	Matrix4f view = Matrix4f::LookAtLH(eye, lookat, up);
	Matrix4f proj = Matrix4f::PerspectiveLH(3.14145f / 4, 800.0f / 600.0f, 1.0f, 10000.0f);

	pRender->Proj = proj;
	pScene->Render(pRender, view);
	*/
	//pRender->SetDefaultRenderTarget();

	pRender->EndScene();
	pRender->Present();

	//if (HMD->HmdCaps & ovrHmdCap_ExtendDesktop)
	//	pRender->WaitUntilG
	ovrHmd_EndFrameTiming(HMD);
}