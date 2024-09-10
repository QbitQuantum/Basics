void DXBox::DrawBox(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{
	//Perform matrix operations for stored scale and position
	XMMATRIX mBoxRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mBoxScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mBoxPosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&mBoxWorld, XMMatrixMultiply(XMMatrixMultiply(mBoxRotation,mBoxScale), mBoxPosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

	// Draw the box.
	XMMATRIX world = XMLoadFloat4x4(&mBoxWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BasicFX->SetWorld(world);
	Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BasicFX->SetWorldViewProj(worldViewProj);
	Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BasicFX->SetMaterial(mBoxMat);
	Effects::BasicFX->SetDiffuseMap(boxDiffuseTexture);

	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
	md3dImmediateContext->DrawIndexed(mBoxIndexCount, mBoxIndexOffset, mBoxVertexOffset);
}