TInt COpenWFC_RI_DisplayUpdater::UpdateDisplay()
    {
    TInt err = KErrNone;

    SymbianStreamBuffer readBuffer = iNextReadBuffer;
    iNextReadBuffer = SYMBIAN_INVALID_HANDLE;
    if (!iNextSceneStream)
        {
        LOG((" !!! COpenWFC_RI_DisplayUpdater::UpdateDisplay() ASSERT: No top layer has been set!"));
        return KErrNotReady;
        }
    if (readBuffer == SYMBIAN_INVALID_HANDLE)
        {
        if ((err = SymbianStreamAcquireReadBuffer(iNextSceneStream, &readBuffer)) != KErrNone)
            {   //AcquireReadBuffer "Can't fail" in theory, but just incase....
            LOG((" !!! COpenWFC_RI_DisplayUpdater::UpdateDisplay() Acquire failed: %d", err));
            return err;
            }
        }
    TBufferInfo bufferInfo;
    khronos_int32_t width, height, stride;
    SymbianStreamGetHeader(iNextSceneStream, &width, &height, &stride, NULL, NULL);
    bufferInfo.iBufferWidth = (TInt16)width;
    bufferInfo.iBufferHeight = (TInt16)height;
    bufferInfo.iStride = (TInt16)stride;
    bufferInfo.iBufferFormat = EPixelFormatXRgb8888Le;
    bufferInfo.iLinearAddress = 0;
    err = SymbianStreamGetBufferPointer(iNextSceneStream, readBuffer,&bufferInfo.iLinearAddress);
    if (err == KErrNone)
        {
        err = SymbianStreamGetChunkHandle(iNextSceneStream, &bufferInfo.iBufferRChunkHandle);
        }

    if (err != KErrNone)
        {
        LOG((" !!! COpenWFC_RI_DisplayUpdater::UpdateDisplay() error %d getting stream data", err));
        SymbianStreamReleaseReadBuffer(iNextSceneStream, readBuffer);
        return err;
        }

    TRect displayRect;
    displayRect.SetRect(TPoint(0, 0), TSize(bufferInfo.iBufferWidth, bufferInfo.iBufferHeight ));
    
    TDisplayViewSettings viewSettings; // Default
    viewSettings.iSourceScissor         = displayRect;
    viewSettings.iDestinationScaledRect = displayRect;
    viewSettings.iLayerRotation         = ERotate0Deg;
    viewSettings.iUsageHint             = EPurposeUi;
    viewSettings.iTearingFree           = ETrue;
      
    LOG((" $$$*** bufferInfo.iBufferWidth %d", bufferInfo.iBufferWidth));
    LOG((" $$$*** bufferInfo.iBufferHeight %d", bufferInfo.iBufferHeight));
    LOG((" $$$*** bufferInfo.iStride %d", bufferInfo.iStride));
    LOG((" $$$*** bufferInfo.iBufferFormat %d", bufferInfo.iBufferFormat));
    LOG((" $$$*** bufferInfo.iLinearAddress %08x", bufferInfo.iLinearAddress));
    LOG((" $$$*** bufferInfo.iBufferRChunkHandle %d", bufferInfo.iBufferRChunkHandle));

    LOG((" $$$*** viewSettings iSourceScissor width %d", viewSettings.iSourceScissor.Width()));
    LOG((" $$$*** viewSettings iSourceScissor height %d", viewSettings.iSourceScissor.Height()));
    LOG((" $$$*** viewSettings iDestinationScaledRect width %d", viewSettings.iDestinationScaledRect.Width()));
    LOG((" $$$*** viewSettings iDestinationScaledRect height %d", viewSettings.iDestinationScaledRect.Height()));
    LOG((" $$$*** viewSettings iLayerRotation %d", viewSettings.iLayerRotation));
    LOG((" $$$*** viewSettings iUsageHint %d", viewSettings.iUsageHint));
    LOG((" $$$*** viewSettings iTearingFree %d", viewSettings.iTearingFree));

    TRequestStatus completedWhenReady = KRequestPending;
    viewSettings.iLayerRotation = iCurrentRotation;

    err = iDisplayUpdater->SetView(KTopMostLayer, viewSettings, bufferInfo);
    
    if (err != KErrNone)
        {
        LOG((" !!! COpenWFC_RI_DisplayUpdater::UpdateDisplay()ERROR: Display update set view failed %d", err));
        }
    else
        {
        err = iDisplayUpdater->SetBuffer(KTopMostLayer, displayRect, bufferInfo );
        if (err != KErrNone)
            {
            LOG((" !!! COpenWFC_RI_DisplayUpdater::UpdateDisplay()ERROR: Display Update set buffer failed %d", err));
            }
        }

    ////////////////////////////////////////////////////////////////////////////////////////////
    iDisplayUpdater->Flush(completedWhenReady);
    
    /* The TRequestStatus& aCompletedWhenReady parameter is signalled 
     * either when the buffer has been copied, 
     * or it is streaming the first pixel to the display
     * In either case this indicates that the previous buffer is no longer required.
     * By waiting here we guarantee that the previous iCurrentReadBuffer is no longer required,
     * but here are more intelligent ways to wait, I am sure!
     */
    User::WaitForRequest(completedWhenReady);
    if (iCurrentReadBuffer != SYMBIAN_INVALID_HANDLE)
        {
        // Release the previous update's read buffer.
        /* This ensures that a lock is held on the displayed buffer until the next commit/compose
         * This is correct behaviour for streaming direct to the display, but is actually not
         * necessary if the display makes its own copy.
         * However, PlatSim currently supports only the latter, and we think the former is important,
         * so this implementation allows us to validate that the behaviour is correct in direct streaming.
         */
        SymbianStreamReleaseReadBuffer(iCurrentSceneStream, iCurrentReadBuffer);
        }
    iCurrentReadBuffer = readBuffer;
    iCurrentSceneStream = iNextSceneStream;
    return err;
    }