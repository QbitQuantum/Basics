UInt32 GUCEF_PLUGIN_CALLSPEC_PREFIX
IMGCODECPLUGIN_EncodeImage( void* pluginData      ,
                            void* codecData       ,
                            const char* codecType ,
                            TImage* inputImage    ,
                            TIOAccess* output     )
{
    UInt32 i = 0;
    UInt32 n = 0;
    TImageInfo* imageInfo = NULL;
    char codecTypeExt[ 256 ];

    /* generate an image ID and make that ID the ID of the current image */
    ilBindImage( ilGenImage() );

    /* Only 1 layer is supported atm */
    ilActiveLayer( 0 );

    imageInfo = &inputImage->imageInfo;
    for ( i=0; i<imageInfo->nrOfFramesInImage; ++i )
    {
        TImageFrameInfo* imageFrameInfo = &inputImage->frames[ i ].frameInfo;
        
        /* activate the frame */
        ilActiveImage( i );        

        for ( n=0; n<imageFrameInfo->nrOfMipmapLevels; ++n )
        {
            /* create a shortcut */
            TImageMipMapLevelInfo* mipInfo = &inputImage->frames[ i ].mipmapLevel[ n ].mipLevelInfo;
            void* imageBuffer = inputImage->frames[ i ].mipmapLevel[ n ].pixelData;

            /* activate the mip-map */
            ilActiveMipmap( n );
            
            /* hand the data over to DevIL */
            if ( IL_TRUE != ilTexImage( (ILuint)mipInfo->frameWidth                                                   ,
                                        (ILuint)mipInfo->frameHeight                                                  ,
                                        (ILuint)1                                                                     ,
                                        (ILubyte) GetChannelCountForFormat( mipInfo->pixelStorageFormat )             ,
                                        (ILenum)ConvertGUCEFPixelFormatToILPixelFormat( mipInfo->pixelStorageFormat ) ,
                                        (ILenum)ConvertGUCEFTypeToILType( mipInfo->pixelComponentDataType )           ,
                                        (void*)imageBuffer                                                            ) )
            {
                /* Failed to transfer the data over to DevIL */
                return 0;
            }
                        
        }
    }
    
    /* Make sure we prefix a dot before the codecType */    
    strcpy_s( codecTypeExt+1, 255, codecType );
    codecTypeExt[ 0 ] = '.';

    /* now we can perform the actual save */
    currentResource = output;
    if ( IL_TRUE == ilSaveF( ilTypeFromExt( codecTypeExt ), output ) )
    {
        currentResource = NULL;
        return 1;
    }
    
    currentResource = NULL;
    return 0;
}