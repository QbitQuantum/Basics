//================================================================
// main function
//================================================================
int 
#ifndef __ANSI__
__cdecl 
#endif // __ANSI__
main(int argc, char* argv[])
{
    if (argc != 5) {
        fprintf(stderr, "Required arguments:\n");
        fprintf(stderr, "1. JPEG quality value, 0-100\n");
        fprintf(stderr, "2. Image size (e.g. '512x512')\n");
        fprintf(stderr, "3. Path to YUV input file\n");
        fprintf(stderr, "4. Path to JXR output file\n");
        return 1;
    }

    errno = 0;

    long quality = strtol(argv[1], NULL, 10);
    if (errno != 0 || quality < 0 || quality > 100) {
        fprintf(stderr, "Invalid JPEG quality value!\n");
        return 1;
    }

    const char *size = argv[2];
    const char *x = strchr(size, 'x');
    if (!x && x != size && x != (x + strlen(x) - 1)) {
        fprintf(stderr, "Invalid image size input!\n");
        return 1;
    }
    long width = strtol(size, NULL, 10);
    if (errno != 0) {
        fprintf(stderr, "Invalid image size input!\n");
        return 1;
    }
    long height = strtol(x + 1, NULL, 10);
    if (errno != 0) {
        fprintf(stderr, "Invalid image size input!\n");
        return 1;
    }
    /* Right now we only support dimensions that are multiples of 16. */
    if ((width % 16) != 0 || (height % 16) != 0) {
        fprintf(stderr, "Image dimensions must be multiples of 16!\n");
        return 1;
    }

    /* Will check these for validity when opening via 'fopen'. */
    const char *yuv_path = argv[3];
    const char *jxr_path = argv[4];

    int yuv_size = width*height+2*(width>>1)*(height>>1);

    unsigned char *image_buffer = (unsigned char*)malloc(yuv_size);

    // set encoder parameters including quality
    {
        CWMIStrCodecParam params;
        init_encoder_params(&params, quality);
    
        // run encoder
        ERR err;
        PKFactory*        pFactory      = NULL;
        PKCodecFactory*   pCodecFactory = NULL;
        struct WMPStream* pEncodeStream = NULL;
        PKImageEncode*    pEncoder      = NULL;
        const PKIID*      pIID          = NULL;
        struct WMPStream* pDecodeStream = NULL;
        PKImageDecode*    pDecoder      = NULL;
    
        Call( PKCreateFactory(&pFactory, PK_SDK_VERSION) );
        Call( pFactory->CreateStreamFromFilename(&pEncodeStream, jxr_path, "wb") );
        Call( pFactory->CreateStreamFromFilename(&pDecodeStream, yuv_path, "rb") );
 
        // decode
        PKRect rc;
        rc.X = 0;
        rc.Y = 0;
        rc.Width  = width;
        rc.Height = height;
   
        Call( GetTestDecodeIID(".iyuv", &pIID) );
        Call( PKTestFactory_CreateCodec(pIID, (void **) &pDecoder) );
        Call( pDecoder->Initialize(pDecoder, pDecodeStream) );
        pDecoder->uWidth = width;
        pDecoder->uHeight = height;
        Call( pDecoder->Copy(pDecoder, &rc, (U8*)image_buffer, width) );

        Call( PKCreateCodecFactory(&pCodecFactory, WMP_SDK_VERSION) );
        Call( pCodecFactory->CreateCodec(&IID_PKImageWmpEncode, (void**)&pEncoder) );
        Call( pEncoder->Initialize(pEncoder, pEncodeStream, &params, sizeof(params)) );
        Call( pEncoder->SetPixelFormat(pEncoder, GUID_PKPixelFormat12bppYCC420) );
        Call( pEncoder->SetSize(pEncoder, width, height) );
        Call( pEncoder->WritePixels(pEncoder, height, (U8*)image_buffer, width*3) ); 

Cleanup:
         if( pDecoder )      pDecoder->Release(&pDecoder);
         if( pEncoder )      pEncoder->Release(&pEncoder);
         if( pCodecFactory ) pCodecFactory->Release(&pCodecFactory);
         if( pFactory )      pFactory->Release(&pFactory);
    }

    free(image_buffer);

    return 0;
}