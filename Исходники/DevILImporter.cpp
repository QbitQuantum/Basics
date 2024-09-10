Resource* DevILImporter::Import( const String& pFilename, const String& /*pParams*/ )
{
    ILuint  imageName;

    // Load the image. DevIL will guess the type of the image file using it's extension and if needed it's header.
    ilGenImages( 1, &imageName );
    ilBindImage( imageName );

    // Load the image.
    if( !ilLoadImage( const_cast<char*>(pFilename.c_str()) ) )
        throw ResourceImportException( ToString(ilGetError()), Here );

    // Get the image params.
    ILint bytesPerPixel   = ilGetInteger( IL_IMAGE_BYTES_PER_PIXEL );
    ILint imgFormat       = ilGetInteger( IL_IMAGE_FORMAT );
    ILint imgWidth        = ilGetInteger( IL_IMAGE_WIDTH );
    ILint imgHeight       = ilGetInteger( IL_IMAGE_HEIGHT );

    // We do not support palettized texture currently, so un-palettize them!
    if( imgFormat == IL_COLOR_INDEX )
    {
        switch( ilGetInteger( IL_PALETTE_TYPE ) )
        {
        case IL_PAL_RGB24:
        case IL_PAL_RGB32:
            imgFormat = IL_RGB;
            break;
        case IL_PAL_BGR24:
        case IL_PAL_BGR32:
            imgFormat = IL_BGR;
            break;
        case IL_PAL_RGBA32:
            imgFormat = IL_RGBA;
            break;
        case IL_PAL_BGRA32:
            imgFormat = IL_BGRA;
            break;
        default:
            debugBreak();
        }

        ilConvertImage( imgFormat, IL_UNSIGNED_BYTE );
        bytesPerPixel = ilGetInteger( IL_IMAGE_BYTES_PER_PIXEL );
        imgFormat     = ilGetInteger( IL_IMAGE_FORMAT );
    }

    // Find what is the gamedesk internal image format that will be used.
    Image::Format gdImgFormat = GetImageFormat( imgFormat, bytesPerPixel );

    Image newImage;
    newImage.Create( imgWidth, imgHeight, gdImgFormat );
    memcpy( newImage.GetData(), ilGetData(), imgWidth*imgHeight*bytesPerPixel );

    Texture* newTexture = NULL;

    // Allocate and create using image.
    if( imgWidth == 1 || imgHeight == 1 )
    {
        Texture1D* tex = Cast<Texture1D>(Texture1D::StaticClass()->AllocateNew( pFilename ));
        tex->Create( newImage );
        newTexture = tex;
    }
    else
    {
        Texture2D* tex = Cast<Texture2D>(Texture2D::StaticClass()->AllocateNew( pFilename ));
        tex->Create( newImage );
        newTexture = tex;
    }

    // The DevIL copy of the image is not needed anymore, so destroy it.
    ilDeleteImages( 1, &imageName );

    return newTexture;
}