    virtual void on_init()
    {
        // Generate the texture
        AggOO::Rect texRect( 0, 0, 40, 40 );
        mTexture = new AggOO::Bitmap( texRect.Width, texRect.Height, AggOO::PixelFormat32bppARGB );
//        AggOO::Bitmap tex( texRect.Width, texRect.Height, AggOO::PixelFormat32bppARGB );
        AggOO::BitmapData texData;
        mTexture->LockBits( &texRect, AggOO::ImageLockModeWrite, mTexture->GetPixelFormat(), &texData );
//        tex.LockBits( &texRect, AggOO::ImageLockModeWrite, tex.GetPixelFormat(), &texData );

        unsigned char *pixels = (unsigned char*)texData.Scan0;
        for ( size_t y = 0; y < texRect.Height; y++ )
        {
            AggOO::REAL yRatio = y / AggOO::REAL( texRect.Height );
            for ( size_t x = 0; x < texRect.Width; x++ )
            {
                AggOO::REAL xRatio = x / AggOO::REAL( texRect.Width );

                *pixels++ = 255;
                *pixels++ = 255 * xRatio;
                *pixels++ = 255 * yRatio;
                *pixels++ = 0;
            }
        }

        mTexture->UnlockBits( &texData );
//        tex.UnlockBits( &texData );

        // Create a brush:
        mBrush = new AggOO::TextureBrush( mTexture, AggOO::WrapModeTileFlipXY );
        mBrush->RotateTransform( 45 );
        mBrush->ScaleTransform( 0.5, 0.5 );
//        mBrush = new AggOO::TextureBrush( &tex, AggOO::WrapModeTileFlipXY );
    }