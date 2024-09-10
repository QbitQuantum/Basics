void SkeletonMeshShader::SetBuffer(AglMatrix pWorld, AglMatrix pView, AglMatrix pProjection, float pScale, AglSkeleton* pSkeleton, AglMaterial pMaterial)
{
	pWorld = AglMatrix::transpose(pWorld);
	pView = AglMatrix::transpose(pView);
	pProjection = AglMatrix::transpose(pProjection);

	//Copy the matrix palette buffer to the gpu
	D3D11_MAPPED_SUBRESOURCE resource;
	mDeviceContext->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	SkeletonMeshShaderBuffer* buffer;
	buffer = (SkeletonMeshShaderBuffer*)resource.pData;
	buffer->World = pWorld;
	buffer->View = pView;
	buffer->Projection = pProjection;
	buffer->Scale = pScale;
	buffer->TextureScale = pMaterial.textureScale;

	unsigned int jointCount = pSkeleton->getHeader().jointCount;
	for (unsigned int i = 0; i < jointCount; i++)
	{
		AglMatrix am = pSkeleton->getInverseBindMatrix(i) * pSkeleton->getGlobalTransform(i);
		am = AglMatrix::transpose(am);
		buffer->Palette[i] = am;
	}

	mDeviceContext->Unmap(mBuffer, 0);

	unsigned int bufferNumber = 0;
	mDeviceContext->VSSetConstantBuffers(bufferNumber, 1, &mBuffer);

	//Copy the material buffer to the gpu
	mDeviceContext->Map(mMaterialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	MaterialBuffer* matbuffer;
	matbuffer = (MaterialBuffer*)resource.pData;
	matbuffer->AmbientOpacity = AglVector4(pMaterial.ambient, pMaterial.opacity);
	matbuffer->DiffuseReflectivity = AglVector4(pMaterial.diffuse, pMaterial.reflectivity);
	matbuffer->SpecularShininess = AglVector4(pMaterial.specular, pMaterial.shininess);
	matbuffer->EmissiveDiffuseMapped = AglVector4(pMaterial.emissive, float(pMaterial.diffuseTextureNameIndex >= 0 && DIFFUSEON));
	matbuffer->EyePositionSpecularMapped = AglVector4(Camera::GetInstance()->Position().x, Camera::GetInstance()->Position().y, Camera::GetInstance()->Position().z, float(pMaterial.specularTextureNameIndex >= 0 && SPECULARON));
	matbuffer->Flags = AglVector4((float)(pMaterial.glowTextureNameIndex >= 0 && GLOWON), (float)(pMaterial.normalTextureNameIndex >= 0  && NORMALON), (float)(pMaterial.gradientDataIndex >= 0 && pMaterial.gradientTextureNameIndex >= 0), 0);
	if (pMaterial.gradientDataIndex >= 0)
	{
		AglGradient* g = Scene::GetInstance()->GetGradient(pMaterial.gradientDataIndex);

		vector<AglGradientMaterial*> layers = g->getLayers();
		for (unsigned int i = 0; i < layers.size(); i++)
			matbuffer->gradientColors[i] = layers[i]->color;
		matbuffer->Flags.w = (float)layers.size();
	}
	mDeviceContext->Unmap(mMaterialBuffer, 0);

	mDeviceContext->PSSetConstantBuffers(bufferNumber, 1, &mMaterialBuffer);

	if (pMaterial.diffuseTextureNameIndex >= 0)
	{
		string s = Scene::GetInstance()->GetName(pMaterial.diffuseTextureNameIndex);
		TextureData* data = TextureManager::GetInstance()->GetTexture(s);
		if (data)
			mDeviceContext->PSSetShaderResources(0, 1, &data->SRV);
	}
	if (pMaterial.specularTextureNameIndex >= 0)
	{
		string s = Scene::GetInstance()->GetName(pMaterial.specularTextureNameIndex);
		TextureData* data = TextureManager::GetInstance()->GetTexture(s);
		if (data)
			mDeviceContext->PSSetShaderResources(1, 1, &data->SRV);
	}
	if (pMaterial.glowTextureNameIndex >= 0)
	{
		string s = Scene::GetInstance()->GetName(pMaterial.glowTextureNameIndex);
		TextureData* data = TextureManager::GetInstance()->GetTexture(s);
		if (data)
			mDeviceContext->PSSetShaderResources(2, 1, &data->SRV);
	}
	if (pMaterial.normalTextureNameIndex >= 0)
	{
		string s = Scene::GetInstance()->GetName(pMaterial.normalTextureNameIndex);
		TextureData* data = TextureManager::GetInstance()->GetTexture(s);
		if (data)
			mDeviceContext->PSSetShaderResources(3, 1, &data->SRV);
	}
	if (pMaterial.gradientTextureNameIndex >= 0)
	{
		string s = Scene::GetInstance()->GetName(pMaterial.gradientTextureNameIndex);
		TextureData* data = TextureManager::GetInstance()->GetTexture(s);
		if (data)
			mDeviceContext->PSSetShaderResources(4, 1, &data->SRV);
	}

	mDeviceContext->PSSetSamplers(0, 1, &mSampler);
	mDeviceContext->DSSetSamplers(0, 1, &mSampler);


	//Bone texture data
	mDeviceContext->VSSetSamplers(0, 1, &mBoneTextureSampler);

	D3D11_MAPPED_SUBRESOURCE mappedTex;
	mDeviceContext->Map(mBoneTexture, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE_DISCARD, 0, &mappedTex);

	float* values = (float*)mappedTex.pData;

	jointCount = pSkeleton->getHeader().jointCount;
	for (unsigned int i = 0; i < jointCount; i++)
	{
		AglMatrix am = pSkeleton->getInverseBindMatrix(i) * pSkeleton->getGlobalTransform(i);
		//am = AglMatrix::transpose(am);

		int pos = i*16;

		//Row1
		values[pos] = am[0];
		values[pos+1] = am[1];
		values[pos+2] = am[2];
		values[pos+3] = am[3];
		//Row2
		values[pos+4] = am[4];
		values[pos+5] = am[5];
		values[pos+6] = am[6]; 
		values[pos+7] = am[7]; 
		//Row3
		values[pos+8] = am[8];
		values[pos+9] = am[9];
		values[pos+10] =am[10];
		values[pos+11] =am[11];
		//Row4
		values[pos+12] = am[12];
		values[pos+13] = am[13];
		values[pos+14] = am[14];
		values[pos+15] = am[15];
	}

	mDeviceContext->Unmap(mBoneTexture, D3D11CalcSubresource(0, 0, 1));
	mDeviceContext->VSSetShaderResources(0, 1, &mBoneSRV);
}