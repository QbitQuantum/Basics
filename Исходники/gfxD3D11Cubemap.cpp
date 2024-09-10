void GFXD3D11Cubemap::initStatic(GFXTexHandle *faces)
{
   AssertFatal( faces, "GFXD3D11Cubemap::initStatic - Got null GFXTexHandle!" );
	AssertFatal( *faces, "empty texture passed to CubeMap::create" );
  
	// NOTE - check tex sizes on all faces - they MUST be all same size
	mTexSize = faces->getWidth();
	mFaceFormat = faces->getFormat();
   bool compressed = isCompressed(mFaceFormat);

   UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
   UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
   if (!compressed)
   {
      bindFlags |= D3D11_BIND_RENDER_TARGET;
      miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
   }

   U32 mipLevels = faces->getPointer()->getMipLevels();
   if (mipLevels > 1)
      mAutoGenMips = true;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = mTexSize;
	desc.Height = mTexSize;
   desc.MipLevels = mAutoGenMips ? 0 : mipLevels;
	desc.ArraySize = 6;
	desc.Format = GFXD3D11TextureFormat[mFaceFormat];
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlags;
	desc.MiscFlags = miscFlags;
	desc.CPUAccessFlags = 0;

	HRESULT hr = D3D11DEVICE->CreateTexture2D(&desc, NULL, &mTexture);

	if (FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap:initStatic(GFXTexhandle *faces) - failed to create texcube texture");
	}

   for (U32 i = 0; i < CubeFaces; i++)
   {
      GFXD3D11TextureObject *texObj = static_cast<GFXD3D11TextureObject*>((GFXTextureObject*)faces[i]);
      U32 subResource = D3D11CalcSubresource(0, i, mipLevels);
      D3D11DEVICECONTEXT->CopySubresourceRegion(mTexture, subResource, 0, 0, 0, texObj->get2DTex(), 0, NULL);
   }
   
	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = GFXD3D11TextureFormat[mFaceFormat];
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
   SMViewDesc.TextureCube.MipLevels = mAutoGenMips ? -1 : mipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	hr = D3D11DEVICE->CreateShaderResourceView(mTexture, &SMViewDesc, &mSRView);
	if (FAILED(hr))
	{
		AssertFatal(false, "GFXD3D11Cubemap::initStatic(GFXTexHandle *faces) - texcube shader resource view  creation failure");
	} 

   if (mAutoGenMips && !compressed)
      D3D11DEVICECONTEXT->GenerateMips(mSRView);
}