//================================================================
// main function
//================================================================
int
#ifndef __ANSI__
    __cdecl
#endif // __ANSI__

jxrlibDecodeMain(int argc, char *argv[])
{
    ERR err = WMP_errSuccess;

    PKFactory *pFactory = NULL;
    PKCodecFactory *pCodecFactory = NULL;
    PKImageDecode *pDecoder = NULL;

    WMPDECAPPARGS args = {0};
    char *pExt = NULL;
    U32 cFrame = 0;
    U32 i = 0;
    PKPixelInfo PI;
    //    static size_t cChannels[CFT_MAX] = {1, 3, 3, 3, 4, 4, -1, 3, 3, -1};

    //================================
    // parse command line parameters
    if (1 == argc)
    {
        WmpDecAppUsage(argv[0]);
        return 0;
    }

    Call(WmpDecAppParseArgs(argc, argv, &args));

    if (args.bVerbose)
    {
        WmpDecAppShowArgs(&args);
    }

    //================================
    pExt = strrchr(args.szOutputFile, '.');
    FailIf(NULL == pExt, WMP_errUnsupportedFormat);

    //================================
    Call(PKCreateFactory(&pFactory, PK_SDK_VERSION));

    Call(PKCreateCodecFactory(&pCodecFactory, WMP_SDK_VERSION));
#if 0
    Call(pCodecFactory->CreateDecoderFromFile(args.szInputFile, &pDecoder));
#else
    Call(PKCodecFactory_CreateDecoderFromFile(args.szInputFile, &pDecoder));
#endif

    // Fix the wrong image plane byte count
    {
        long fileSize;
        FILE *pFile = pDecoder->pStream->state.file.pFile;
        fseek(pFile, 0, SEEK_END);
        fileSize = ftell(pFile);
        if (args.bVerbose) {
          printf("File size: %ld\n", fileSize);
        }
        fseek(pFile, 0, SEEK_SET);

        if ((U32)fileSize < pDecoder->WMP.wmiDEMisc.uImageOffset + pDecoder->WMP.wmiDEMisc.uImageByteCount)
        {
            size_t byteCount = fileSize - pDecoder->WMP.wmiDEMisc.uImageOffset;
            pDecoder->WMP.wmiDEMisc.uImageByteCount = byteCount;
            pDecoder->WMP.wmiI.uImageByteCount = byteCount;
        }

        // Circumvent the bug in JXELIB's JPEG-XR encoder that used to write wrong alpha plane byte count.
        // Adjust the alpha plane byte count if the value is wrong.
        if (pDecoder->WMP.wmiDEMisc.uAlphaOffset + pDecoder->WMP.wmiI_Alpha.uImageByteCount > (U32)fileSize)
            pDecoder->WMP.wmiI_Alpha.uImageByteCount = fileSize - pDecoder->WMP.wmiDEMisc.uAlphaOffset;
    }

    //////////////// Save color profile ///////////////////

    if (args.szColorProfileFile && pDecoder->WMP.wmiDEMisc.uColorProfileByteCount != 0)
    {
        size_t cb = pDecoder->WMP.wmiDEMisc.uColorProfileByteCount;
        void *buf = malloc(cb);

        if (buf)
        {
            U32 cbRead = cb;
            ERR err = PKImageDecode_GetColorContext_WMP(pDecoder, (U8 *)buf, &cbRead);

            if (WMP_errSuccess == err)
            {
                // Save color pfofile in a file
                FILE *pFile;
#ifdef WIN32
                FailIf(0 != fopen_s(&pFile, args.szColorProfileFile, "wb"), WMP_errFileIO);
#else
                pFile = fopen(args.szColorProfileFile, "wb");
                FailIf(NULL == pFile, WMP_errFileIO);
#endif
               FailIf(1 != fwrite(buf, cb, 1, pFile), WMP_errFileIO);
                fclose(pFile);
            }

            free(buf);
        }
    }

    ///////////////////////////////////////////////////////////////

    //==== set default color format
    if (IsEqualGUID(&args.guidPixFormat, &GUID_PKPixelFormatDontCare))
    {
        // take deocder color format and try to look up better one
        // (e.g. 32bppBGR -> 24bppBGR etc.)
        PKPixelInfo newPI;
        newPI.pGUIDPixFmt = PI.pGUIDPixFmt = &pDecoder->guidPixFormat;
        Call(PixelFormatLookup(&newPI, LOOKUP_FORWARD));
        Call(PixelFormatLookup(&newPI, LOOKUP_BACKWARD_TIF));
        args.guidPixFormat = *newPI.pGUIDPixFmt;
    }
    else
        PI.pGUIDPixFmt = &args.guidPixFormat;

    //    pDecoder->WMP.wmiI.bRGB = args.bFlagRGB_BGR;

    // == color transcoding,
    if (IsEqualGUID(&args.guidPixFormat, &GUID_PKPixelFormat8bppGray) ||
        IsEqualGUID(&args.guidPixFormat, &GUID_PKPixelFormat16bppGray))
    { // ** => Y transcoding
        pDecoder->guidPixFormat = args.guidPixFormat;
        pDecoder->WMP.wmiI.cfColorFormat = Y_ONLY;
    }
    else if (IsEqualGUID(&args.guidPixFormat, &GUID_PKPixelFormat24bppRGB) && pDecoder->WMP.wmiI.cfColorFormat == CMYK)
    {// CMYK = > RGB
        pDecoder->WMP.wmiI.cfColorFormat = CF_RGB;
        pDecoder->guidPixFormat = args.guidPixFormat;
        pDecoder->WMP.wmiI.bRGB = 1; //RGB
    }

    PixelFormatLookup(&PI, LOOKUP_FORWARD);

    if (255 == args.uAlphaMode) //user didn't set
    {
        if (!!(PI.grBit & PK_pixfmtHasAlpha))
            args.uAlphaMode = 2; //default is image & alpha for formats with alpha
        else
            args.uAlphaMode = 0; //otherwise, 0
    }

    pDecoder->WMP.wmiSCP.bfBitstreamFormat = args.bfBitstreamFormat;
    pDecoder->WMP.wmiSCP.uAlphaMode = args.uAlphaMode;

    pDecoder->WMP.wmiSCP.sbSubband = args.sbSubband;

    pDecoder->WMP.bIgnoreOverlap = args.bIgnoreOverlap;

    pDecoder->WMP.wmiI.cfColorFormat = PI.cfColorFormat;

    pDecoder->WMP.wmiI.bdBitDepth = PI.bdBitDepth;
    pDecoder->WMP.wmiI.cBitsPerUnit = PI.cbitUnit;

    //==== Validate thumbnail decode parameters =====
    pDecoder->WMP.wmiI.cThumbnailWidth = pDecoder->WMP.wmiI.cWidth;
    pDecoder->WMP.wmiI.cThumbnailHeight = pDecoder->WMP.wmiI.cHeight;
    pDecoder->WMP.wmiI.bSkipFlexbits = FALSE;

    if (args.tThumbnailFactor > 0 && args.tThumbnailFactor != SKIPFLEXBITS)
    {
        size_t tSize = ((size_t)1 << args.tThumbnailFactor);

        pDecoder->WMP.wmiI.cThumbnailWidth = (pDecoder->WMP.wmiI.cWidth + tSize - 1) / tSize;
        pDecoder->WMP.wmiI.cThumbnailHeight = (pDecoder->WMP.wmiI.cHeight + tSize - 1) / tSize;

        if (pDecoder->WMP.wmiI.cfColorFormat == YUV_420 || pDecoder->WMP.wmiI.cfColorFormat == YUV_422)
        { // unsupported thumbnail format
            pDecoder->WMP.wmiI.cfColorFormat = YUV_444;
        }
    }
    else if (args.tThumbnailFactor == SKIPFLEXBITS)
    {
        pDecoder->WMP.wmiI.bSkipFlexbits = TRUE;
    }

    if (args.rWidth == 0 || args.rHeight == 0)
    { // no region decode
        args.rLeftX = args.rTopY = 0;
        args.rWidth = pDecoder->WMP.wmiI.cThumbnailWidth;
        args.rHeight = pDecoder->WMP.wmiI.cThumbnailHeight;
    }

    pDecoder->WMP.wmiI.cROILeftX = args.rLeftX;
    pDecoder->WMP.wmiI.cROITopY = args.rTopY;
    pDecoder->WMP.wmiI.cROIWidth = args.rWidth;
    pDecoder->WMP.wmiI.cROIHeight = args.rHeight;

    pDecoder->WMP.wmiI.oOrientation = args.oOrientation;

    pDecoder->WMP.wmiI.cPostProcStrength = args.cPostProcStrength;

    pDecoder->WMP.wmiSCP.bVerbose = args.bVerbose;

    Call(pDecoder->GetFrameCount(pDecoder, &cFrame));

    //================================
    for (i = 0; ; ++i)
    {
        struct WMPStream *pEncodeStream = NULL;
        PKImageEncode *pEncoder = NULL;

        PKFormatConverter *pConverter = NULL;

        Float rX = 0.0, rY = 0.0;
        PKRect rect = {0, 0, 0, 0};

        //================================
#if 0
        Call(pCodecFactory->CreateFormatConverter(&pConverter));
#else
        Call(PKCodecFactory_CreateFormatConverter(&pConverter));
#endif

        Call(pConverter->Initialize(pConverter, pDecoder, pExt, args.guidPixFormat));

        //================================
        Call(pFactory->CreateStreamFromFilename(&pEncodeStream, args.szOutputFile, "wb"));
        Call(WmpDecAppCreateEncoderFromExt(pCodecFactory, pExt, &pEncoder));

        if (pEncoder->bWMP)
            Call(pEncoder->Initialize(pEncoder, pEncodeStream, &args.wmiSCP, sizeof(args.wmiSCP)));
        else
            Call(pEncoder->Initialize(pEncoder, pEncodeStream, NULL, 0));

        //!!! Do it here instead of JXRGlueEnc.c in order to avoid dependence of purely encoding applications on JXRDecodeLib.lib!!!
        pEncoder->Transcode = PKImageEncode_Transcode_WMP;

        //================================
        Call(pEncoder->SetPixelFormat(pEncoder, args.guidPixFormat));
        pEncoder->WMP.wmiSCP.bBlackWhite = pDecoder->WMP.wmiSCP.bBlackWhite;

        //Call(pDecoder->GetSize(pDecoder, &rect.Width, &rect.Height));
        rect.Width = (I32)(pDecoder->WMP.wmiI.cROIWidth);
        rect.Height = (I32)(pDecoder->WMP.wmiI.cROIHeight);

        if (args.oOrientation > O_FLIPVH)
        { // allocate memory for rotated image!
            I32 bah = rect.Width;

            rect.Width = rect.Height;
            rect.Height = bah;
        }

        Call(pEncoder->SetSize(pEncoder, rect.Width, rect.Height));
        Call(pDecoder->GetResolution(pDecoder, &rX, &rY));

        if (args.oOrientation > O_FLIPVH)
            Call(pEncoder->SetResolution(pEncoder, rY, rX));
        else
            Call(pEncoder->SetResolution(pEncoder, rX, rY));

        if (pEncoder->bWMP && args.tThumbnailFactor > 0)
        {
            printf("-T can not be used for compressed domain operation!\n");
            return 0;
        }

        //================================
        pEncoder->WriteSource = PKImageEncode_Transcode;
        Call(pEncoder->WriteSource(pEncoder, pConverter, &rect));

        //================================
        //        Call(pEncoder->Terminate(pEncoder));
        pEncoder->Release(&pEncoder);

        // multi-frame support NYI
        if (i + 1 == cFrame)
            break;

        Call(pDecoder->SelectFrame(pDecoder, i + 1));
    }

    pDecoder->Release(&pDecoder);

Cleanup:
    if (WMP_errUnsupportedFormat == err)
    {
        printf("*** ERROR: Unsupported format in JPEG XR ***\n");
    }

    return (int)err;
}