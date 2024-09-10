void CALLBACK OnFrameMove(_In_ double fTime, _In_ float fElapsedTime, _In_opt_ void* pUserContext)
{
	static float rot = 0.0f;
	rot += fElapsedTime;
	XMMATRIX mscale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX mrot	= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, rot);
	XMMATRIX mtrans = XMMatrixTranslation(20.0f, 50.0f, 0.0f);

	// gmesh 의 월드 매트릭스 -> XMMATRIX
	XMMATRIX mParent = XMLoadFloat4x4(&g_mesh->getWorld());

	g_matLight = (mscale * mtrans * mrot) * mParent;
	
	// 조명 메시 연결
	XMFLOAT4X4 mlit = XMFLOAT4X4();
	XMStoreFloat4x4(&mlit, g_matLight);
	g_meshLight->setWorld(mlit);


	g_camera.FrameMove(fElapsedTime);




}