AmbientOcclusionApp::AmbientOcclusionApp(HINSTANCE hInstance)
: D3DApp(hInstance), mSkullVB(0), mSkullIB(0), mSkullIndexCount(0)
{
	mMainWndCaption = L"Ambient Occlusion";
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	mCam.SetPosition(0.0f, 5.0f, -5.0f);
	mCam.LookAt(
		XMFLOAT3(-4.0f, 4.0f, -4.0f),
		XMFLOAT3(0.0f, 2.2f, 0.0f),
		XMFLOAT3(0.0f, 1.0f, 0.0f));

	XMMATRIX skullScale = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	XMMATRIX skullOffset = XMMatrixTranslation(0.0f, 1.0f, 0.0f);
	XMStoreFloat4x4(&mSkullWorld, XMMatrixMultiply(skullScale, skullOffset));
}