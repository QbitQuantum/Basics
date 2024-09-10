void CDDS::LoadFile( const wchar_t *filename )
{

	if(!glewIsSupported("GL_EXT_texture_compression_s3tc"))
	{
		DDSerror=DDS_ERROR_NO_SUPPOT;
		return;
	}
   // DDS_IMAGE_DATA *pDDSImageData;
    DDSURFACEDESC2 ddsd;

    char filecode[4];
    FILE *pFile;
    int factor;
    int bufferSize; 

    // Open the file
    _wfopen_s(&pFile, filename, L"rb" ); 

    if( pFile == NULL )
    {
       // char str[255];
       // sprintf( str, "LoadFile couldn't find, or failed to load \"%s\"", filename );
       // MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        return ;
    } 

    // Verify the file is a true .dds file
    fread( filecode, 1, 4, pFile ); 

    if( strncmp( filecode, "DDS ", 4 ) != 0 )
    {

      //  char str[255];
     //   sprintf( str, "The file \"%s\" doesn't appear to be a valid .dds file!", filename );
    //    MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );

		DDSerror=DDS_ERROR_NOT_OPEN_FILE;
        fclose( pFile );
        return ;
    } 

    // Get the surface descriptor
    fread( &ddsd, sizeof(ddsd), 1, pFile ); 

    pDDSImageData = (DDS_IMAGE_DATA*) malloc(sizeof(DDS_IMAGE_DATA)); 

    memset( pDDSImageData, 0, sizeof(DDS_IMAGE_DATA) ); 

    //
    // This .dds loader supports the loading of compressed formats DXT1, DXT3 
    // and DXT5.
    // 

    switch( ddsd.ddpfPixelFormat.dwFourCC )
    {
        case FOURCC_DXT1:
            // DXT1's compression ratio is 8:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
			UseAlpha=false;
            break; 

        case FOURCC_DXT3:
            // DXT3's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        case FOURCC_DXT5:
            // DXT5's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
			UseAlpha=true;
            break; 

        default:
//#ifdef _WIN32
//            char str[255];
//            sprintf( str, "The file \"%s\" doesn't appear to be compressed "
//                "using DXT1, DXT3, or DXT5!", filename );
//            MessageBox( NULL, str, "ERROR", MB_OK|MB_ICONEXCLAMATION );
//#endif
			DDSerror=DDS_ERROR_DDS_FORMAT;
            return ;
    } 

    //
    // How big will the buffer need to be to load all of the pixel data 
    // including mip-maps?
    // 

    if( ddsd.dwLinearSize == 0 )
    {
//#ifdef _WIN32
//        MessageBox( NULL, "dwLinearSize is 0!","ERROR",
//            MB_OK|MB_ICONEXCLAMATION);
//#endif
		DDSerror=DDS_ERROR_DDS_FORMAT;
		return ;
    } 

    if( ddsd.dwMipMapCount > 1 )
        bufferSize = ddsd.dwLinearSize * factor;
    else
        bufferSize = ddsd.dwLinearSize; 

    pDDSImageData->pixels = (unsigned char*)malloc(bufferSize * sizeof(unsigned char)); 

    fread( pDDSImageData->pixels, 1, bufferSize, pFile ); 

    // Close the file
    fclose( pFile ); 

    pDDSImageData->width      = ddsd.dwWidth;
    pDDSImageData->height     = ddsd.dwHeight;
    pDDSImageData->numMipMaps = ddsd.dwMipMapCount; 
	TexW=ddsd.dwWidth;
	TexH=ddsd.dwHeight;


    if( ddsd.ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        pDDSImageData->components = 3;
    else
        pDDSImageData->components = 4; 

	isRAM=true;
    //return pDDSImageData;
}