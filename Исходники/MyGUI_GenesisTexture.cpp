	GPtr<RenderBase::Texture> _BuildTextureData(const GPtr<Resources::ImageRes>& image, GPtr<IO::MemoryStream>& memStream)
	{
		n_assert(image.isvalid());

		if ( !image.isvalid() )
		{
			return GPtr<RenderBase::Texture>();
		}

		if ( !image->Validata() )
		{
			return GPtr<RenderBase::Texture>();
		}

		GPtr<RenderBase::Texture> tex = RenderBase::Texture::Create();
		tex->Setup();

		// set type
		RenderBase::Texture::Type texType = RenderBase::Texture::InvalidType;

		if ( image->GetNumFace() == 1 )
		{
			if ( image->GetDepth() == 1)
			{
				texType = RenderBase::Texture::Texture2D; 
			}
			else
			{
				n_assert( image->GetDepth() > 1);
				texType = RenderBase::Texture::Texture3D; 
			}
		}
		else 
		{
			n_assert( image->GetNumFace() > 1);
			texType = RenderBase::Texture::TextureCube;
		}
		n_assert( texType != RenderBase::Texture::InvalidType)
			tex->SetType( texType );

		tex->SetWidth( image->GetWidth() );
		tex->SetHeight( image->GetHeight() );
		tex->SetDepth( image->GetDepth() );
		tex->SetNumMipLevels( image->GetMipMapLevel() + 1 );
		tex->SetPixelFormat( image->GetPixelFormat() );

		// dummy
		tex->SetSkippedMips( 0 );
		tex->SetUnitIndex( 0 );

		n_assert( image->GetResourceId().IsValid() );
		tex->SetTexturePath(image->GetResourceId());

		const GPtr<ImageData>& imageData = image->GetImageData();
		n_assert( imageData.isvalid() );
		if (memStream)
		{	
			memStream = NULL;
		}
		memStream = IO::MemoryStream::Create();

		memStream->SetAccessMode( IO::Stream::ReadWriteAccess );
		if( memStream->Open() )
		{
			memStream->Write( imageData->Ptr(), imageData->Size() );
			tex->SetStream( memStream.upcast<IO::Stream>() );
			memStream->Close();
			return tex;
		}

		return GPtr<RenderBase::Texture>();
	}