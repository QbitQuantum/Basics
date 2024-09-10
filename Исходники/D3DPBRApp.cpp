void D3DPBRApp::DrawScene(Camera& camera)
{
	md3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	md3dImmediateContext->RSSetViewports(1, &mScreenViewport);

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;

	//

	XMMATRIX view     = camera.View();
	XMMATRIX proj     = camera.Proj();
	XMMATRIX viewProj = camera.ViewProj();




	// Set per frame constants.
	Effects::CommonPassFX->SetDirLights(mDirLights);
	Effects::CommonPassFX->SetEyePosW(mCam.GetPosition());
	Effects::CommonPassFX->SetEnvMap(mDynamicCubeMapSRV);

	ID3DX11EffectTechnique* activeMeshTech = Effects::CommonPassFX->Light1Tech;

	D3DX11_TECHNIQUE_DESC techDesc;
	activeMeshTech->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p)
	{
		// Draw the Mesh.

		if( GetAsyncKeyState('1') & 0x8000 )
			md3dImmediateContext->RSSetState(RenderStates::WireframeRS);

		md3dImmediateContext->IASetVertexBuffers(0, 1, &m_pVB, &stride, &offset);
		md3dImmediateContext->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX world = XMLoadFloat4x4(&mMeshWorld);
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
		XMMATRIX worldViewProj = world*view*proj;

		Effects::CommonPassFX->SetWorld(world);
		Effects::CommonPassFX->SetWorldInvTranspose(worldInvTranspose);
		Effects::CommonPassFX->SetWorldViewProj(worldViewProj);
		Effects::CommonPassFX->SetMaterial(mMeshMat);

		activeMeshTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		md3dImmediateContext->DrawIndexed(m_indexnum, 0, 0);

		//m_pSky->Draw(md3dImmediateContext, camera);

		// Restore default
		md3dImmediateContext->RSSetState(0);
	}

}