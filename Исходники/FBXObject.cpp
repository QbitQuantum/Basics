void FBXObject::SetupDrawConstantBuffer()
{
	static std::vector<XMFLOAT4X4> mBoneTransforms(128);
	for(std::size_t i = 0; i < this->AnimController.Mesh.second->mNumBones; ++i)
    {
		XMMATRIX invBind = XMLoadFloat4x4(&this->AnimController.Mesh.second->mSkeleton[i].invBindPose);
		XMMATRIX currPose = XMLoadFloat4x4(&this->AnimController.CurrentGlobalPose[i]);
		XMMATRIX total = invBind * currPose;
		XMMATRIX invTotal = XMMatrixTranspose( total);
		XMFLOAT4X4 inv;
		XMStoreFloat4x4(&inv, invTotal);
	
		mBoneTransforms[i] = inv;
	}

	cBuffer::cbChangeEveryFrame cb;
	XMFLOAT4X4 world = this->object.CalculateMatrix();
	cb.mWorld = XMLoadFloat4x4(&world);
	cb.colour.diffuse = this->object.Colour.Diffuse;
	cb.colour.ambient = this->object.Colour.Ambient;
	cb.colour.spec = this->object.Colour.Spec;

	ID3D11DeviceContext* pImmediateContext = DX11App::getInstance()->direct3d.pImmediateContext;

	pImmediateContext->UpdateSubresource( this->pCBChangesEveryFrame.second, 0, NULL, &cb, 0, 0 );    	
    pImmediateContext->VSSetConstantBuffers( 2, 1, &(this->pCBChangesEveryFrame.second) );
	pImmediateContext->PSSetConstantBuffers( 2, 1, &(this->pCBChangesEveryFrame.second) );

	pImmediateContext->UpdateSubresource( this->pAnimBonesBuffer.second, 0, NULL, &(mBoneTransforms.front()), 0, 0 );
	pImmediateContext->VSSetConstantBuffers( 3, 1, &(this->pAnimBonesBuffer.second) );
}