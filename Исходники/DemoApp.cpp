void DemoApp::BuildShadowMapMatrices()
{
	//Calculate the radius of the scene's bounding sphere. Approximately use the half of ground plane diagonal.
	float aabbRadius = sqrt(grndLength * grndLength + grndWidth * grndWidth) / 2.0f ;

	//Set up light parameter
	XMVECTOR lightDir = XMLoadFloat3(&mDirLight.Direction);
	XMVECTOR lightPos = -1.0f * lightDir * aabbRadius;
	XMFLOAT3 tar = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMVECTOR targetPos = XMLoadFloat3(&tar); 
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	mLightView = XMMatrixLookAtLH(lightPos, targetPos, up);

	// Transform bounding sphere to light space.
	XMFLOAT3 aabbCenterLightSpace;
	XMStoreFloat3(&aabbCenterLightSpace, XMVector3TransformCoord(targetPos, mLightView));

	//// Ortho frustum in light space encloses scene.
	float l = aabbCenterLightSpace.x - aabbRadius;
	float b = aabbCenterLightSpace.y - aabbRadius;
	float n = aabbCenterLightSpace.z - aabbRadius;
	float r = aabbCenterLightSpace.x + aabbRadius;
	float t = aabbCenterLightSpace.y + aabbRadius;
	float f = aabbCenterLightSpace.z + aabbRadius;
	mLightProj = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	// Transform NDC space [-1,+1]^2 to texture space [0,1]^2
	mLightViewport = XMMATRIX(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	 mLightVPT = mLightView*mLightProj*mLightViewport;
}