ILboolean iLoadWdpInternal(/*ILconst_string FileName*/)
{
	ERR err = WMP_errSuccess;
	PKFactory* pFactory = NULL;
	PKCodecFactory* pCodecFactory = NULL;
	PKImageDecode* pDecoder = NULL;
    PKPixelInfo PI;
	PKPixelFormatGUID guidPixFormat;
	PKFormatConverter* pConverter = NULL;
    U32 cFrame = 0, i = 0;
	PKRect Rect;
    struct WMPStream* pEncodeStream = NULL;
    PKImageEncode* pEncoder = NULL;

	//Call(PKCreateFactory(&pFactory, PK_SDK_VERSION));
	//Call(PKCreateCodecFactory(&pCodecFactory, WMP_SDK_VERSION));
	//Call(pCodecFactory->CreateDecoderFromFile(FileName, &pDecoder));
	Call(ilPKCreateFactory(&pFactory, PK_SDK_VERSION));
	Call(PKCreateCodecFactory(&pCodecFactory, WMP_SDK_VERSION));
	Call(ilPKCodecFactory_CreateDecoderFromFile(&pDecoder));

	//guidPixFormat = GUID_PKPixelFormat24bppRGB;
	guidPixFormat = GUID_PKPixelFormat32bppBGRA;
	//guidPixFormat = GUID_PKPixelFormat8bppGray;
	//guidPixFormat = GUID_PKPixelFormat16bppGray;

    // Color transcoding
    if (IsEqualGUID(&guidPixFormat, &GUID_PKPixelFormat8bppGray) || IsEqualGUID(&guidPixFormat, &GUID_PKPixelFormat16bppGray)){ // ** => Y transcoding
        pDecoder->guidPixFormat = guidPixFormat;
        pDecoder->WMP.wmiI.cfColorFormat = Y_ONLY;
    }
	else if(IsEqualGUID(&guidPixFormat, &GUID_PKPixelFormat24bppRGB) && pDecoder->WMP.wmiI.cfColorFormat == CMYK){ // CMYK = > RGB
		pDecoder->WMP.wmiI.cfColorFormat = CF_RGB;
		pDecoder->guidPixFormat = guidPixFormat;
		pDecoder->WMP.wmiI.bRGB = 1; //RGB
	}

	PI.pGUIDPixFmt = &guidPixFormat;
    PixelFormatLookup(&PI, LOOKUP_FORWARD);

    pDecoder->WMP.wmiSCP.bfBitstreamFormat = 0;
    pDecoder->WMP.wmiSCP.uAlphaMode = 0;
    pDecoder->WMP.wmiSCP.sbSubband = SB_ALL;
    pDecoder->WMP.bIgnoreOverlap = FALSE;

    pDecoder->WMP.wmiI.cfColorFormat = PI.cfColorFormat;

    pDecoder->WMP.wmiI.bdBitDepth = PI.bdBitDepth;
    pDecoder->WMP.wmiI.cBitsPerUnit = PI.cbitUnit;

	//==== Validate thumbnail decode parameters =====
    pDecoder->WMP.wmiI.cThumbnailWidth = pDecoder->WMP.wmiI.cWidth;
    pDecoder->WMP.wmiI.cThumbnailHeight = pDecoder->WMP.wmiI.cHeight;
    pDecoder->WMP.wmiI.bSkipFlexbits = FALSE;

	pCodecFactory->CreateFormatConverter(&pConverter);
	pConverter->Initialize(pConverter, pDecoder, NULL, guidPixFormat);

	// Right now, we are just assuming one frame.
	// @TODO: Deal with multiple frames.
    //pDecoder->GetFrameCount(pDecoder, &cFrame);
	//pDecoder->SelectFrame(pDecoder, 1);

	if (!ilTexImage(pDecoder->uWidth, pDecoder->uHeight, 1, 4, IL_BGRA, IL_UNSIGNED_BYTE, NULL))
		goto Cleanup;
	//ilTexImage(pDecoder->uWidth, pDecoder->uHeight, 1, 1, IL_LUMINANCE, IL_UNSIGNED_BYTE, Data);

	pFactory->CreateStreamFromMemory(&pEncodeStream, iCurImage->Data, iCurImage->SizeOfData);
    iWmpDecAppCreateEncoderFromExt(pCodecFactory, ".wdp", &pEncoder);
	pEncoder->Initialize(pEncoder, pEncodeStream, ".wdp", 0);

    pEncoder->pStream->GetPos(pEncoder->pStream, &pEncoder->offStart);

	// Set the region that we want to be the whole image.
	Rect.X = 0; Rect.Y = 0; Rect.Height = pDecoder->uHeight; Rect.Width = pDecoder->uWidth;
	pEncoder->SetPixelFormat(pEncoder, guidPixFormat);
    pEncoder->SetSize(pEncoder, Rect.Width, Rect.Height);
	pEncoder->WriteSource = PKImageEncode_Transcode;
    pEncoder->WriteSource(pEncoder, pConverter, &Rect);


Cleanup:
	// Release everything all at the end.
	PKImageDecode_Release(&pDecoder);
	if (pEncoder)
		PKImageEncode_Release(&pEncoder);
	PKCreateCodecFactory_Release(&pCodecFactory);
	PKCreateFactory_Release(&pFactory);
	PKFormatConverter_Release(&pConverter);

	if (err != WMP_errSuccess)
		return IL_FALSE;
	return IL_TRUE;
}