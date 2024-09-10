bool GFXD3D11TextureManager::_loadTexture(GFXTextureObject *aTexture, GBitmap *pDL)
{
   PROFILE_SCOPE(GFXD3D11TextureManager_loadTexture);

   GFXD3D11TextureObject *texture = static_cast<GFXD3D11TextureObject*>(aTexture);

   // Check with profiler to see if we can do automatic mipmap generation.
   const bool supportsAutoMips = GFX->getCardProfiler()->queryProfile("autoMipMapLevel", true);

   // Helper bool
   const bool isCompressedTexFmt = ImageUtil::isCompressedFormat(aTexture->mFormat);

   // Settings for mipmap generation
   U32 maxDownloadMip = pDL->getNumMipLevels();
   U32 nbMipMapLevel  = pDL->getNumMipLevels();

   if( supportsAutoMips && !isCompressedTexFmt )
   {
      maxDownloadMip = 1;
      nbMipMapLevel  = aTexture->mMipLevels;
   }
   GFXD3D11Device* dev = D3D11;

   bool isDynamic = texture->mProfile->isDynamic();
   // Fill the texture...
   for( U32 i = 0; i < maxDownloadMip; i++ )
   {
	   U32 subResource = D3D11CalcSubresource(i, 0, aTexture->mMipLevels);

	   if(!isDynamic)
	   {
		   U8* copyBuffer = NULL;

		   switch(texture->mFormat)
			{
            case GFXFormatR8G8B8:
            case GFXFormatR8G8B8_SRGB:
				{
					PROFILE_SCOPE(Swizzle24_Upload);

					U8* Bits = new U8[pDL->getWidth(i) * pDL->getHeight(i) * 4];
					dMemcpy(Bits, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * 3);
					bitmapConvertRGB_to_RGBX(&Bits, pDL->getWidth(i) * pDL->getHeight(i));
					copyBuffer = new U8[pDL->getWidth(i) * pDL->getHeight(i) * 4];
					
					dev->getDeviceSwizzle32()->ToBuffer(copyBuffer, Bits, pDL->getWidth(i) * pDL->getHeight(i) * 4);
					dev->getDeviceContext()->UpdateSubresource(texture->get2DTex(), subResource, NULL, copyBuffer, pDL->getWidth() * 4, pDL->getHeight() *4);
               SAFE_DELETE_ARRAY(Bits);
					break;
				}

				case GFXFormatR8G8B8A8:
				case GFXFormatR8G8B8X8:
            case GFXFormatR8G8B8A8_SRGB:
				{
               PROFILE_SCOPE(Swizzle32_Upload);
               copyBuffer = new U8[pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel()];
               dev->getDeviceSwizzle32()->ToBuffer(copyBuffer, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel());
               dev->getDeviceContext()->UpdateSubresource(texture->get2DTex(), subResource, NULL, copyBuffer, pDL->getWidth() * pDL->getBytesPerPixel(), pDL->getHeight() *pDL->getBytesPerPixel());
					break;
				}

				default:
				{
               // Just copy the bits in no swizzle or padding
               PROFILE_SCOPE(SwizzleNull_Upload);
               AssertFatal( pDL->getFormat() == texture->mFormat, "Format mismatch");
               dev->getDeviceContext()->UpdateSubresource(texture->get2DTex(), subResource, NULL, pDL->getBits(i), pDL->getWidth() *pDL->getBytesPerPixel(), pDL->getHeight() *pDL->getBytesPerPixel());
				}
			}

         SAFE_DELETE_ARRAY(copyBuffer);
	    }
	  
	   else
	   {
			D3D11_MAPPED_SUBRESOURCE mapping;
			HRESULT res =  dev->getDeviceContext()->Map(texture->get2DTex(), subResource, D3D11_MAP_WRITE, 0, &mapping);

			AssertFatal(res, "tex2d map call failure");

			switch( texture->mFormat )
			{
				case GFXFormatR8G8B8:
            case GFXFormatR8G8B8_SRGB:
				{
					PROFILE_SCOPE(Swizzle24_Upload);

					U8* Bits = new U8[pDL->getWidth(i) * pDL->getHeight(i) * 4];
					dMemcpy(Bits, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * 3);
					bitmapConvertRGB_to_RGBX(&Bits, pDL->getWidth(i) * pDL->getHeight(i));					

					dev->getDeviceSwizzle32()->ToBuffer(mapping.pData, Bits, pDL->getWidth(i) * pDL->getHeight(i) * 4);
               SAFE_DELETE_ARRAY(Bits);
				}
				break;

            case GFXFormatR8G8B8A8:
            case GFXFormatR8G8B8X8:
            case GFXFormatR8G8B8A8_SRGB:
            {
               PROFILE_SCOPE(Swizzle32_Upload);
               dev->getDeviceSwizzle32()->ToBuffer(mapping.pData, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel());
            }
				break;

				default:
				{
               // Just copy the bits in no swizzle or padding
               PROFILE_SCOPE(SwizzleNull_Upload);
               AssertFatal( pDL->getFormat() == texture->mFormat, "Format mismatch");
               dMemcpy(mapping.pData, pDL->getBits(i), pDL->getWidth(i) * pDL->getHeight(i) * pDL->getBytesPerPixel());
				}
			}

			dev->getDeviceContext()->Unmap(texture->get2DTex(), subResource);
	   }
   }

   D3D11_TEXTURE2D_DESC desc;
   // if the texture asked for mip generation. lets generate it.
   texture->get2DTex()->GetDesc(&desc);
   if (desc.MiscFlags &D3D11_RESOURCE_MISC_GENERATE_MIPS)
   {
      dev->getDeviceContext()->GenerateMips(texture->getSRView());
      //texture->mMipLevels = desc.MipLevels;
   }

   return true;          
}