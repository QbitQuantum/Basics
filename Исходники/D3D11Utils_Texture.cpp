// static
void D3D11Utils_Texture::copyTextureToImage( ID3D11Device* pDevice, ID3D11Texture2D* pTexture, Image4f& im )
{
	D3D11_TEXTURE2D_DESC desc;
	pTexture->GetDesc( &desc );

	int width = desc.Width;
	int height = desc.Height;

	std::shared_ptr< StagingTexture2D > pST;

	if( desc.Format == DXGI_FORMAT_R32G32_FLOAT )
	{
		pST.reset( StagingTexture2D::createFloat2( pDevice, width, height ) );
	}
	else if( desc.Format == DXGI_FORMAT_R32G32B32A32_FLOAT )
	{
		pST.reset( StagingTexture2D::createFloat4( pDevice, width, height ) );
	}

	if( desc.Format == DXGI_FORMAT_R32G32_FLOAT )
	{
		pST->copyFrom( pTexture );
		D3D11_MAPPED_SUBRESOURCE mt = pST->mapForReadWrite();
		ubyte* sourceData = reinterpret_cast< ubyte* >( mt.pData );

		for( int y = 0; y < height; ++y )
		{
			float* sourceRow = reinterpret_cast< float* >( &( sourceData[ y * mt.RowPitch ] ) );
			for( int x = 0; x < width; ++x )
			{
				float r = sourceRow[ 2 * x ];
				float g = sourceRow[ 2 * x + 1 ];
				im.setPixel( x, y, Vector4f( r, g, 0, 1 ) );
			}
		}
		pST->unmap();
	}
	else if( desc.Format == DXGI_FORMAT_R32G32B32A32_FLOAT )
	{
		pST->copyFrom( pTexture );
		D3D11_MAPPED_SUBRESOURCE mapping = pST->mapForReadWrite();
		ubyte* sourceData = reinterpret_cast< ubyte* >( mapping.pData );

		if( mapping.RowPitch == 4 * width * sizeof( float ) )
		{
			memcpy( im.pixels(), sourceData, 4 * width * height * sizeof( float ) );
		}
		else
		{
			for( int y = 0; y < height; ++y )
			{
				float* sourceRow = reinterpret_cast< float* >( &( sourceData[ y * mapping.RowPitch ] ) );
				float* destinationRow = im.rowPointer( y );
				memcpy( destinationRow, sourceRow, 4 * width * sizeof( float ) );
			}
		}
		pST->unmap();
	}
	else
	{
		printf( "Warning: unable to copy texture to image, format is unsupported\n" );
	}
}