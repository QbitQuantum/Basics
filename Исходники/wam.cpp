void wam::Pick(int sx, int sy)
{
	
XMMATRIX P = mCam.Proj();

	// Compute picking ray in view space.
	float vx = (+2.0f*sx/mClientWidth  - 1.0f)/P(0,0);
	float vy = (-2.0f*sy/mClientHeight + 1.0f)/P(1,1);

	// Ray definition in view space.
	XMVECTOR rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR rayDir    = XMVectorSet(vx, vy, 1.0f, 0.0f);

	// Tranform ray to local space of Mesh.
	XMMATRIX V = mCam.View();
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(V), V);

	XMMATRIX W = XMLoadFloat4x4(&mGridWorld);
	XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

	XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);

	rayOrigin = XMVector3TransformCoord(rayOrigin, toLocal);
	rayDir = XMVector3TransformNormal(rayDir, toLocal);

	// Make the ray direction unit length for the intersection tests.
	rayDir = XMVector3Normalize(rayDir);
	
		XNA::Sphere tmpSphere11,tmpSphere12,tmpSphere13,tmpSphere21,tmpSphere22,tmpSphere23,tmpSphere31,tmpSphere32,tmpSphere33;
		float radius =0.5f;
		tmpSphere11.Radius = radius;
		tmpSphere12.Radius = radius;
		tmpSphere13.Radius = radius;
		tmpSphere21.Radius = radius;
		tmpSphere22.Radius = radius;
		tmpSphere23.Radius = radius;
		tmpSphere31.Radius = radius;
		tmpSphere32.Radius = radius;
		tmpSphere33.Radius = radius;

		tmpSphere11.Center = XMFLOAT3(-5.0f,-1.0f,-5.0f);
		tmpSphere12.Center = XMFLOAT3( 0.0f,-1.0f,-5.0f);
		tmpSphere13.Center = XMFLOAT3( 5.0f,-1.0f,-5.0f);
		tmpSphere21.Center = XMFLOAT3(-5.0f,-1.0f, 0.0f);
		tmpSphere22.Center = XMFLOAT3( 0.0f,-1.0f, 0.0f);
		tmpSphere23.Center = XMFLOAT3( 5.0f,-1.0f, 0.0f);
		tmpSphere31.Center = XMFLOAT3(-5.0f,-1.0f, 5.0f);
		tmpSphere32.Center = XMFLOAT3( 0.0f,-1.0f, 5.0f);
		tmpSphere33.Center = XMFLOAT3( 5.0f,-1.0f, 5.0f);

		UINT PickedSphere=0;
		FLOAT tmpDist;
		//IntersectRaySphere( FXMVECTOR Origin, FXMVECTOR Direction, const Sphere* pVolume, FLOAT* pDist );

		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere11, &tmpDist ))
			PickedSphere= 11;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere12, &tmpDist ))
			PickedSphere= 12;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere13, &tmpDist ))
			PickedSphere= 13;

		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere21, &tmpDist ))
			PickedSphere= 21;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere22, &tmpDist ))
			PickedSphere= 22;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere23, &tmpDist ))
			PickedSphere= 23;

		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere31, &tmpDist ))
			PickedSphere= 31;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere32, &tmpDist ))
			PickedSphere= 32;
		if(XNA::IntersectRaySphere( rayOrigin, rayDir, &tmpSphere33, &tmpDist ))
			PickedSphere= 33;

		if(PickedSphere!=0)
		{
			int ps =PickedSphere;
		}
	}