void TexColumnApp::UpdateScene(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	mEyePosW = XMFLOAT3(x, y, z);

	// Build the view matrix.
	XMVECTOR pos    = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, V);

	//
	// Switch the number of lights based on key presses.
	//
	if( GetAsyncKeyState('0') & 0x8000 )
		mLightCount = 0; 

	if( GetAsyncKeyState('1') & 0x8000 )
		mLightCount = 1; 

	if( GetAsyncKeyState('2') & 0x8000 )
		mLightCount = 2; 

	if( GetAsyncKeyState('3') & 0x8000 )
		mLightCount = 3; 
}