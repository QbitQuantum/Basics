// Returns malNoError if successful, or comp_CompileAbort if user aborted
prMALError RenderAndWriteVideoFrame(
    const PrTime				videoTime,
    exDoExportRec				*exportInfoP)
{
    csSDK_int32					resultS					= malNoError;
    csSDK_uint32				exID					= exportInfoP->exporterPluginID;
    ExportSettings				*mySettings = reinterpret_cast<ExportSettings *>(exportInfoP->privateData);
    csSDK_int32					rowbytes				= 0;
    csSDK_int32					renderedPixelSize		= 0;
    exParamValues				width,
                                height,
                                pixelAspectRatio,
                                fieldType,
                                codecSubType;
    PrPixelFormat				renderedPixelFormat;
    csSDK_uint32				bytesToWriteLu			= 0;
    char						*frameBufferP			= NULL,
                                         *f32BufferP				= NULL,
                                                   *frameNoPaddingP		= NULL,
                                                          *v410Buffer				= NULL;
    SequenceRender_ParamsRec renderParms;
    PrPixelFormat pixelFormats[] = {PrPixelFormat_BGRA_4444_8u, PrPixelFormat_BGRA_4444_8u};

    renderParms.inRequestedPixelFormatArray = pixelFormats;
    renderParms.inRequestedPixelFormatArrayCount = 1;

    mySettings->exportParamSuite->GetParamValue(exID, 0, ADBEVideoWidth, &width);
    renderParms.inWidth = width.value.intValue;
    mySettings->exportParamSuite->GetParamValue(exID, 0, ADBEVideoHeight, &height);
    renderParms.inHeight = height.value.intValue;
    mySettings->exportParamSuite->GetParamValue(exID, 0, ADBEVideoAspect, &pixelAspectRatio);
    renderParms.inPixelAspectRatioNumerator = pixelAspectRatio.value.ratioValue.numerator;
    renderParms.inPixelAspectRatioDenominator = pixelAspectRatio.value.ratioValue.denominator;

    renderParms.inRenderQuality = kPrRenderQuality_High;
    mySettings->exportParamSuite->GetParamValue(exID, 0, ADBEVideoFieldType, &fieldType);
    renderParms.inFieldType = fieldType.value.intValue;
    // By setting this to false, we basically leave deinterlacing up to the host logic
    // We could set it to true if we wanted to force deinterlacing
    renderParms.inDeinterlace = kPrFalse;
    renderParms.inDeinterlaceQuality = kPrRenderQuality_High;

    mySettings->exportParamSuite->GetParamValue(exID, 0, ADBEVideoCodec, &codecSubType);

    switch(codecSubType.value.intValue)
    {
    case SDK_8_BIT_RGB:
        renderParms.inCompositeOnBlack = kPrFalse;
        break;

    case SDK_10_BIT_YUV:
        renderParms.inCompositeOnBlack = kPrTrue;
        renderParms.inRequestedPixelFormatArrayCount = 2;
        pixelFormats[0] = PrPixelFormat_VUYA_4444_32f;
        break;
    }

    SequenceRender_GetFrameReturnRec renderResult;

    resultS = mySettings->sequenceRenderSuite->RenderVideoFrame(mySettings->videoRenderID,
              videoTime,
              &renderParms,
              kRenderCacheType_None,	// [TODO] Try different settings
              &renderResult);
    mySettings->ppixSuite->GetPixels(	renderResult.outFrame,
                                        PrPPixBufferAccess_ReadOnly,
                                        &frameBufferP);
    mySettings->ppixSuite->GetRowBytes(renderResult.outFrame, &rowbytes);
    mySettings->ppixSuite->GetPixelFormat(renderResult.outFrame, &renderedPixelFormat);
    renderedPixelSize = GetPixelFormatSize(renderedPixelFormat);

    // If user hit cancel
    if (resultS == suiteError_CompilerCompileAbort)
    {
        // Just return the abort
    }
    else
    {
        // If there is extra row padding, trim it off.
        // Currently, rows are aligned to 128 bytes for optimizations.
        // So, for example a width of 320 * 4 bytes per pixel = 1280 = 128 * 10 = no padding
        // But a width of 720 * 4 bytes per pixel = 2880 = 128 * 22.5 = padding
        if (rowbytes != width.value.intValue * renderedPixelSize)
        {
            frameNoPaddingP = new char[width.value.intValue  * height.value.intValue  * renderedPixelSize];
            RemoveRowPadding(	frameBufferP,
                                frameNoPaddingP,
                                rowbytes,
                                renderedPixelSize,
                                width.value.intValue,
                                height.value.intValue);
            rowbytes		= width.value.intValue * renderedPixelSize;
            frameBufferP	= frameNoPaddingP;
        }

        if (codecSubType.value.intValue == SDK_10_BIT_YUV)
        {
            // Check for returned pixel format and convert if necessary
            if (renderedPixelFormat == PrPixelFormat_BGRA_4444_8u)
            {
                f32BufferP = new char[width.value.intValue * height.value.intValue * GetPixelFormatSize(PrPixelFormat_VUYA_4444_32f)];
                ConvertFrom8uTo32f(	frameBufferP,
                                    f32BufferP,
                                    width.value.intValue,
                                    height.value.intValue);
                ConvertFromBGRA32fToVUYA32f(f32BufferP,
                                            width.value.intValue,
                                            height.value.intValue);
                frameBufferP = f32BufferP;
            }

            v410Buffer = new char[width.value.intValue * height.value.intValue * GetPixelFormatSize(codecSubType.value.intValue)];
            ConvertFrom32fToV410(	frameBufferP,
                                    v410Buffer,
                                    width.value.intValue,
                                    height.value.intValue);
            rowbytes		= width.value.intValue * GetPixelFormatSize(codecSubType.value.intValue);
            frameBufferP	= v410Buffer;
        }

        // Save the uncompressed frames to disk
        if (codecSubType.value.intValue != SDK_RLE)
        {
            bytesToWriteLu = rowbytes * height.value.intValue;
            mySettings->exportFileSuite->Write(exportInfoP->fileObject,
                                               frameBufferP,
                                               bytesToWriteLu);
        }
        /*
        else (codecSubType.value.intValue == SDK_RLE)
        {
        	// Currently the SDK import cannot read RLE
        	WriteRLE(	reinterpret_cast<long*>(frameBufferP),
        				exportInfoP->outputFileRef,
        				(height.value.intValue * width.value.intValue));
        }
        */

        // Write divider between frames
        bytesToWriteLu = PLUS_LINE_LENGTH;
        mySettings->exportFileSuite->Write(exportInfoP->fileObject,
                                           const_cast<char *>(PLUS_LINE),
                                           bytesToWriteLu);

        // Now that buffer is written to disk, we can dispose of memory
        mySettings->ppixSuite->Dispose(renderResult.outFrame);
        if (frameNoPaddingP)
        {
            delete(frameNoPaddingP);
            frameNoPaddingP = NULL;
        }
        if (f32BufferP)
        {
            delete(f32BufferP);
            f32BufferP = NULL;
        }
        if (v410Buffer)
        {
            delete(v410Buffer);
            v410Buffer = NULL;
        }
    }

    return resultS;
}