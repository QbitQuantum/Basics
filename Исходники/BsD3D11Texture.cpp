	void D3D11TextureCore::writeData(const PixelData& src, UINT32 mipLevel, UINT32 face, bool discardWholeBuffer)
	{
		PixelFormat format = mProperties.getFormat();

		if (mProperties.getMultisampleCount() > 1)
			BS_EXCEPT(InvalidStateException, "Multisampled textures cannot be accessed from the CPU directly.");

		mipLevel = Math::clamp(mipLevel, (UINT32)mipLevel, mProperties.getNumMipmaps());
		face = Math::clamp(face, (UINT32)0, mProperties.getNumFaces() - 1);

		if (face > 0 && mProperties.getTextureType() == TEX_TYPE_3D)
			BS_EXCEPT(InvalidStateException, "3D texture arrays are not supported.");

		if ((mProperties.getUsage() & TU_DYNAMIC) != 0)
		{
			PixelData myData = lock(discardWholeBuffer ? GBL_WRITE_ONLY_DISCARD : GBL_WRITE_ONLY, mipLevel, face);
			PixelUtil::bulkPixelConversion(src, myData);
			unlock();
		}
		else if ((mProperties.getUsage() & TU_DEPTHSTENCIL) == 0)
		{
			D3D11RenderAPI* rs = static_cast<D3D11RenderAPI*>(RenderAPICore::instancePtr());
			D3D11Device& device = rs->getPrimaryDevice();

			UINT subresourceIdx = D3D11CalcSubresource(mipLevel, face, mProperties.getNumMipmaps() + 1);
			UINT32 rowWidth = D3D11Mappings::getSizeInBytes(format, src.getWidth());
			UINT32 sliceWidth = D3D11Mappings::getSizeInBytes(format, src.getWidth(), src.getHeight());

			device.getImmediateContext()->UpdateSubresource(mTex, subresourceIdx, nullptr, src.getData(), rowWidth, sliceWidth);

			if (device.hasError())
			{
				String errorDescription = device.getErrorDescription();
				BS_EXCEPT(RenderingAPIException, "D3D11 device cannot map texture\nError Description:" + errorDescription);
			}

			BS_INC_RENDER_STAT_CAT(ResWrite, RenderStatObject_Texture);
		}
		else
		{
			BS_EXCEPT(RenderingAPIException, "Trying to write into a buffer with unsupported usage: " + toString(mProperties.getUsage()));
		}
	}