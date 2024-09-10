void D3DTextureDemo::UpdateScene(float dt)
{
	float x = mRadius * sinf(mPhi) * cosf(mTheta);
	float z = mRadius * sinf(mPhi) * sinf(mTheta);
	float y = mRadius * cosf(mPhi);

	mEyePosW = XMFLOAT3(x, y, z);

	XMVECTOR pos    = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view      = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, view);

	static float t_base = 0.0f;
	if ((m_Timer.TotalTime() - t_base) >= 0.25f)
	{
		t_base += 0.25f;
		DWORD i = 5 + rand() % (mWaves.RowCount()    - 10);
		DWORD j = 5 + rand() % (mWaves.ColumnCount() - 10);
		float r = MathHelper::RandF(1.0f, 2.0f);
		mWaves.Disturb(i, j, r);
	}
	mWaves.Update(dt);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_d3dImmediateContext->Map(
		mWaveVB, 
		0, 
		D3D11_MAP_WRITE_DISCARD, 
		0, 
		&mappedData),
		L"Context Map");

	Vertex* v = reinterpret_cast<Vertex*>(mappedData.pData);
	for(UINT i = 0; i < mWaves.VertexCount(); ++i)
	{
		v[i].Pos    = mWaves[i];
		v[i].Normal = mWaves.Normal(i);
		v[i].Tex.x  = 0.5f + mWaves[i].x / mWaves.Width();
		v[i].Tex.y  = 0.5f - mWaves[i].z / mWaves.Depth();
	}

	m_d3dImmediateContext->Unmap(mWaveVB, 0);

	XMMATRIX wavesScale = XMMatrixScaling(5.0f, 5.0f, 0.0f);
	mWaterTexOffset.y += 0.05f * dt;
	mWaterTexOffset.x += 0.1f  * dt;	
	XMMATRIX wavesOffset = XMMatrixTranslation(mWaterTexOffset.x, mWaterTexOffset.y, 0.0f);
	XMStoreFloat4x4(&mWaterTexTransform, wavesScale*wavesOffset);
}