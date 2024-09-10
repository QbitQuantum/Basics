//todo: this function is an abomination, this is just disgusting.  fix it.
//...seriously, this is really, really horrible.  I mean this is amazingly bad.
void OBS::MainCaptureLoop()
{
    int curRenderTarget = 0, curYUVTexture = 0, curCopyTexture = 0;
    int copyWait = NUM_RENDER_BUFFERS-1;

    bSentHeaders = false;
    bFirstAudioPacket = true;

    bool bLogLongFramesProfile = GlobalConfig->GetInt(TEXT("General"), TEXT("LogLongFramesProfile"), LOGLONGFRAMESDEFAULT) != 0;
    float logLongFramesProfilePercentage = GlobalConfig->GetFloat(TEXT("General"), TEXT("LogLongFramesProfilePercentage"), 10.f);

    Vect2 baseSize    = Vect2(float(baseCX), float(baseCY));
    Vect2 outputSize  = Vect2(float(outputCX), float(outputCY));
    Vect2 scaleSize   = Vect2(float(scaleCX), float(scaleCY));

    HANDLE hMatrix   = yuvScalePixelShader->GetParameterByName(TEXT("yuvMat"));
    HANDLE hScaleVal = yuvScalePixelShader->GetParameterByName(TEXT("baseDimensionI"));

    //----------------------------------------
    // x264 input buffers

    int curOutBuffer = 0;

    bool bUsingQSV = videoEncoder->isQSV();//GlobalConfig->GetInt(TEXT("Video Encoding"), TEXT("UseQSV")) != 0;
    bUsing444 = false;

    EncoderPicture lastPic;
    EncoderPicture outPics[NUM_OUT_BUFFERS];

    for(int i=0; i<NUM_OUT_BUFFERS; i++)
    {
        if(bUsingQSV)
        {
            outPics[i].mfxOut = new mfxFrameSurface1;
            memset(outPics[i].mfxOut, 0, sizeof(mfxFrameSurface1));
            mfxFrameData& data = outPics[i].mfxOut->Data;
            videoEncoder->RequestBuffers(&data);
        }
        else
        {
            outPics[i].picOut = new x264_picture_t;
            x264_picture_init(outPics[i].picOut);
        }
    }

    if(bUsing444)
    {
        for(int i=0; i<NUM_OUT_BUFFERS; i++)
        {
            outPics[i].picOut->img.i_csp   = X264_CSP_BGRA; //although the x264 input says BGR, x264 actually will expect packed UYV
            outPics[i].picOut->img.i_plane = 1;
        }
    }
    else
    {
        if(!bUsingQSV)
            for(int i=0; i<NUM_OUT_BUFFERS; i++)
                x264_picture_alloc(outPics[i].picOut, X264_CSP_NV12, outputCX, outputCY);
    }

    int bCongestionControl = AppConfig->GetInt (TEXT("Video Encoding"), TEXT("CongestionControl"), 0);
    bool bDynamicBitrateSupported = App->GetVideoEncoder()->DynamicBitrateSupported();
    int defaultBitRate = AppConfig->GetInt(TEXT("Video Encoding"), TEXT("MaxBitrate"), 1000);
    int currentBitRate = defaultBitRate;
    QWORD lastAdjustmentTime = 0;
    UINT adjustmentStreamId = 0;

    //std::unique_ptr<ProfilerNode> encodeThreadProfiler;

    //----------------------------------------
    // time/timestamp stuff

    bool bWasLaggedFrame = false;

    totalStreamTime = 0;
    lastAudioTimestamp = 0;

    //----------------------------------------
    // start audio capture streams

    desktopAudio->StartCapture();
    if(micAudio) micAudio->StartCapture();

    //----------------------------------------
    // status bar/statistics stuff

    DWORD fpsCounter = 0;

    int numLongFrames = 0;
    int numTotalFrames = 0;

    bytesPerSec = 0;
    captureFPS = 0;
    curFramesDropped = 0;
    curStrain = 0.0;
    PostMessage(hwndMain, OBS_UPDATESTATUSBAR, 0, 0);

    QWORD lastBytesSent[3] = {0, 0, 0};
    DWORD lastFramesDropped = 0;
    double bpsTime = 0.0;

    double lastStrain = 0.0f;
    DWORD numSecondsWaited = 0;

    //----------------------------------------
    // 444->420 thread data

    int numThreads = MAX(OSGetTotalCores()-2, 1);
    HANDLE *h420Threads = (HANDLE*)Allocate(sizeof(HANDLE)*numThreads);
    Convert444Data *convertInfo = (Convert444Data*)Allocate(sizeof(Convert444Data)*numThreads);

    zero(h420Threads, sizeof(HANDLE)*numThreads);
    zero(convertInfo, sizeof(Convert444Data)*numThreads);

    for(int i=0; i<numThreads; i++)
    {
        convertInfo[i].width  = outputCX;
        convertInfo[i].height = outputCY;
        convertInfo[i].hSignalConvert  = CreateEvent(NULL, FALSE, FALSE, NULL);
        convertInfo[i].hSignalComplete = CreateEvent(NULL, FALSE, FALSE, NULL);
        convertInfo[i].bNV12 = bUsingQSV;
        convertInfo[i].numThreads = numThreads;

        if(i == 0)
            convertInfo[i].startY = 0;
        else
            convertInfo[i].startY = convertInfo[i-1].endY;

        if(i == (numThreads-1))
            convertInfo[i].endY = outputCY;
        else
            convertInfo[i].endY = ((outputCY/numThreads)*(i+1)) & 0xFFFFFFFE;
    }

    bool bEncode;
    bool bFirstFrame = true;
    bool bFirstImage = true;
    bool bFirstEncode = true;
    bool bUseThreaded420 = bUseMultithreadedOptimizations && (OSGetTotalCores() > 1) && !bUsing444;

    List<HANDLE> completeEvents;

    if(bUseThreaded420)
    {
        for(int i=0; i<numThreads; i++)
        {
            h420Threads[i] = OSCreateThread((XTHREAD)Convert444Thread, convertInfo+i);
            completeEvents << convertInfo[i].hSignalComplete;
        }
    }

    //----------------------------------------

    QWORD streamTimeStart  = GetQPCTimeNS();
    QWORD lastStreamTime   = 0;
    QWORD firstFrameTimeMS = streamTimeStart/1000000;
    QWORD frameLengthNS    = 1000000000/fps;

    while(WaitForSingleObject(hVideoEvent, INFINITE) == WAIT_OBJECT_0)
    {
        if (bShutdownVideoThread)
            break;

        QWORD renderStartTime = GetQPCTimeNS();
        totalStreamTime = DWORD((renderStartTime-streamTimeStart)/1000000);

        bool bRenderView = !IsIconic(hwndMain) && bRenderViewEnabled;

        QWORD renderStartTimeMS = renderStartTime/1000000;

        QWORD curStreamTime = latestVideoTimeNS;
        if (!lastStreamTime)
            lastStreamTime = curStreamTime-frameLengthNS;
        QWORD frameDelta = curStreamTime-lastStreamTime;
        //if (!lastStreamTime)
        //    lastStreamTime = renderStartTime-frameLengthNS;
        //QWORD frameDelta = renderStartTime-lastStreamTime;
        double fSeconds = double(frameDelta)*0.000000001;
        //lastStreamTime = renderStartTime;

        bool bUpdateBPS = false;

        profileIn("video thread frame");

        //Log(TEXT("Stream Time: %llu"), curStreamTime);
        //Log(TEXT("frameDelta: %lf"), fSeconds);

        //------------------------------------

        if(bRequestKeyframe && keyframeWait > 0)
        {
            keyframeWait -= int(frameDelta);

            if(keyframeWait <= 0)
            {
                GetVideoEncoder()->RequestKeyframe();
                bRequestKeyframe = false;
            }
        }

        if(!bPushToTalkDown && pushToTalkTimeLeft > 0)
        {
            pushToTalkTimeLeft -= int(frameDelta);
            OSDebugOut(TEXT("time left: %d\r\n"), pushToTalkTimeLeft);
            if(pushToTalkTimeLeft <= 0)
            {
                pushToTalkTimeLeft = 0;
                bPushToTalkOn = false;
            }
        }

        //------------------------------------

        OSEnterMutex(hSceneMutex);

        if (bPleaseEnableProjector)
            ActuallyEnableProjector();
        else if(bPleaseDisableProjector)
            DisableProjector();

        if(bResizeRenderView)
        {
            GS->ResizeView();
            bResizeRenderView = false;
        }

        //------------------------------------

        if(scene)
        {
            profileIn("scene->Preprocess");
            scene->Preprocess();

            for(UINT i=0; i<globalSources.Num(); i++)
                globalSources[i].source->Preprocess();

            profileOut;

            scene->Tick(float(fSeconds));

            for(UINT i=0; i<globalSources.Num(); i++)
                globalSources[i].source->Tick(float(fSeconds));
        }

        //------------------------------------

        QWORD curBytesSent = network->GetCurrentSentBytes();
        curFramesDropped = network->NumDroppedFrames();

        bpsTime += fSeconds;
        if(bpsTime > 1.0f)
        {
            if(numSecondsWaited < 3)
                ++numSecondsWaited;

            //bytesPerSec = DWORD(curBytesSent - lastBytesSent);
            bytesPerSec = DWORD(curBytesSent - lastBytesSent[0]) / numSecondsWaited;

            if(bpsTime > 2.0)
                bpsTime = 0.0f;
            else
                bpsTime -= 1.0;

            if(numSecondsWaited == 3)
            {
                lastBytesSent[0] = lastBytesSent[1];
                lastBytesSent[1] = lastBytesSent[2];
                lastBytesSent[2] = curBytesSent;
            }
            else
                lastBytesSent[numSecondsWaited] = curBytesSent;

            captureFPS = fpsCounter;
            fpsCounter = 0;

            bUpdateBPS = true;
        }

        fpsCounter++;

        curStrain = network->GetPacketStrain();

        EnableBlending(TRUE);
        BlendFunction(GS_BLEND_SRCALPHA, GS_BLEND_INVSRCALPHA);

        //------------------------------------
        // render the mini render texture

        LoadVertexShader(mainVertexShader);
        LoadPixelShader(mainPixelShader);

        SetRenderTarget(mainRenderTextures[curRenderTarget]);

        Ortho(0.0f, baseSize.x, baseSize.y, 0.0f, -100.0f, 100.0f);
        SetViewport(0, 0, baseSize.x, baseSize.y);

        if(scene)
            scene->Render();

        //------------------------------------

        if(bTransitioning)
        {
            if(!transitionTexture)
            {
                transitionTexture = CreateTexture(baseCX, baseCY, GS_BGRA, NULL, FALSE, TRUE);
                if(transitionTexture)
                {
                    D3D10Texture *d3dTransitionTex = static_cast<D3D10Texture*>(transitionTexture);
                    D3D10Texture *d3dSceneTex = static_cast<D3D10Texture*>(mainRenderTextures[lastRenderTarget]);
                    GetD3D()->CopyResource(d3dTransitionTex->texture, d3dSceneTex->texture);
                }
                else
                    bTransitioning = false;
            }
            else if(transitionAlpha >= 1.0f)
            {
                delete transitionTexture;
                transitionTexture = NULL;

                bTransitioning = false;
            }
        }

        if(bTransitioning)
        {
            EnableBlending(TRUE);
            transitionAlpha += float(fSeconds)*5.0f;
            if(transitionAlpha > 1.0f)
                transitionAlpha = 1.0f;
        }
        else
            EnableBlending(FALSE);

        //------------------------------------
        // render the mini view thingy

        if (bProjector) {
            SetRenderTarget(projectorTexture);

            Vect2 renderFrameSize, renderFrameOffset;
            Vect2 projectorSize = Vect2(float(projectorWidth), float(projectorHeight));

            float projectorAspect = (projectorSize.x / projectorSize.y);
            float baseAspect = (baseSize.x / baseSize.y);

            if (projectorAspect < baseAspect) {
                float fProjectorWidth = float(projectorWidth);

                renderFrameSize   = Vect2(fProjectorWidth, fProjectorWidth / baseAspect);
                renderFrameOffset = Vect2(0.0f, (projectorSize.y-renderFrameSize.y) * 0.5f);
            } else {
                float fProjectorHeight = float(projectorHeight);

                renderFrameSize   = Vect2(fProjectorHeight * baseAspect, fProjectorHeight);
                renderFrameOffset = Vect2((projectorSize.x-renderFrameSize.x) * 0.5f, 0.0f);
            }

            DrawPreview(renderFrameSize, renderFrameOffset, projectorSize, curRenderTarget, Preview_Projector);

            SetRenderTarget(NULL);
        }

        if(bRenderView)
        {
            // Cache
            const Vect2 renderFrameSize = GetRenderFrameSize();
            const Vect2 renderFrameOffset = GetRenderFrameOffset();
            const Vect2 renderFrameCtrlSize = GetRenderFrameControlSize();

            SetRenderTarget(NULL);
            DrawPreview(renderFrameSize, renderFrameOffset, renderFrameCtrlSize, curRenderTarget,
                    bFullscreenMode ? Preview_Fullscreen : Preview_Standard);

            //draw selections if in edit mode
            if(bEditMode && !bSizeChanging)
            {
                if(scene) {
                    LoadVertexShader(solidVertexShader);
                    LoadPixelShader(solidPixelShader);
                    solidPixelShader->SetColor(solidPixelShader->GetParameter(0), 0xFF0000);
                    scene->RenderSelections(solidPixelShader);
                }
            }
        }
        else if(bForceRenderViewErase)
        {
            InvalidateRect(hwndRenderFrame, NULL, TRUE);
            UpdateWindow(hwndRenderFrame);
            bForceRenderViewErase = false;
        }

        //------------------------------------
        // actual stream output

        LoadVertexShader(mainVertexShader);
        LoadPixelShader(yuvScalePixelShader);

        Texture *yuvRenderTexture = yuvRenderTextures[curRenderTarget];
        SetRenderTarget(yuvRenderTexture);

        switch(colorDesc.matrix)
        {
        case ColorMatrix_GBR:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[0] : (float*)yuvMat[0]);
            break;
        case ColorMatrix_YCgCo:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[1] : (float*)yuvMat[1]);
            break;
        case ColorMatrix_BT2020NCL:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[2] : (float*)yuvMat[2]);
            break;
        case ColorMatrix_BT709:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[3] : (float*)yuvMat[3]);
            break;
        case ColorMatrix_SMPTE240M:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[4] : (float*)yuvMat[4]);
            break;
        default:
            yuvScalePixelShader->SetMatrix(hMatrix, colorDesc.fullRange ? (float*)yuvFullMat[5] : (float*)yuvMat[5]);
        }

        if(downscale < 2.01)
            yuvScalePixelShader->SetVector2(hScaleVal, 1.0f/baseSize);
        else if(downscale < 3.01)
            yuvScalePixelShader->SetVector2(hScaleVal, 1.0f/(outputSize*3.0f));

        Ortho(0.0f, outputSize.x, outputSize.y, 0.0f, -100.0f, 100.0f);
        SetViewport(0.0f, 0.0f, outputSize.x, outputSize.y);

        //why am I using scaleSize instead of outputSize for the texture?
        //because outputSize can be trimmed by up to three pixels due to 128-bit alignment.
        //using the scale function with outputSize can cause slightly inaccurate scaled images
        if(bTransitioning)
        {
            BlendFunction(GS_BLEND_ONE, GS_BLEND_ZERO);
            DrawSpriteEx(transitionTexture, 0xFFFFFFFF, 0.0f, 0.0f, scaleSize.x, scaleSize.y, 0.0f, 0.0f, 1.0f, 1.0f);
            BlendFunction(GS_BLEND_FACTOR, GS_BLEND_INVFACTOR, transitionAlpha);
        }

        DrawSpriteEx(mainRenderTextures[curRenderTarget], 0xFFFFFFFF, 0.0f, 0.0f, outputSize.x, outputSize.y, 0.0f, 0.0f, 1.0f, 1.0f);

        //------------------------------------

        if (bProjector && !copyWait)
            projectorSwap->Present(0, 0);

        if(bRenderView && !copyWait)
            static_cast<D3D10System*>(GS)->swap->Present(0, 0);

        OSLeaveMutex(hSceneMutex);

        //------------------------------------
        // present/upload

        profileIn("GPU download and conversion");

        bEncode = true;

        if(copyWait)
        {
            copyWait--;
            bEncode = false;
        }
        else
        {
            //audio sometimes takes a bit to start -- do not start processing frames until audio has started capturing
            if(!bRecievedFirstAudioFrame)
            {
                static bool bWarnedAboutNoAudio = false;
                if (renderStartTimeMS-firstFrameTimeMS > 10000 && !bWarnedAboutNoAudio)
                {
                    bWarnedAboutNoAudio = true;
                    //AddStreamInfo (TEXT ("WARNING: OBS is not receiving audio frames. Please check your audio devices."), StreamInfoPriority_Critical); 
                }
                bEncode = false;
            }
            else if(bFirstFrame)
            {
                firstFrameTimestamp = lastStreamTime/1000000;
                bFirstFrame = false;
            }

            if(!bEncode)
            {
                if(curYUVTexture == (NUM_RENDER_BUFFERS-1))
                    curYUVTexture = 0;
                else
                    curYUVTexture++;
            }
        }

        lastStreamTime = curStreamTime;

        if(bEncode)
        {
            UINT prevCopyTexture = (curCopyTexture == 0) ? NUM_RENDER_BUFFERS-1 : curCopyTexture-1;

            ID3D10Texture2D *copyTexture = copyTextures[curCopyTexture];
            profileIn("CopyResource");

            if(!bFirstEncode && bUseThreaded420)
            {
                WaitForMultipleObjects(completeEvents.Num(), completeEvents.Array(), TRUE, INFINITE);
                copyTexture->Unmap(0);
            }

            D3D10Texture *d3dYUV = static_cast<D3D10Texture*>(yuvRenderTextures[curYUVTexture]);
            GetD3D()->CopyResource(copyTexture, d3dYUV->texture);
            profileOut;

            ID3D10Texture2D *prevTexture = copyTextures[prevCopyTexture];

            if(bFirstImage) //ignore the first frame
                bFirstImage = false;
            else
            {
                HRESULT result;
                D3D10_MAPPED_TEXTURE2D map;
                if(SUCCEEDED(result = prevTexture->Map(0, D3D10_MAP_READ, 0, &map)))
                {
                    int prevOutBuffer = (curOutBuffer == 0) ? NUM_OUT_BUFFERS-1 : curOutBuffer-1;
                    int nextOutBuffer = (curOutBuffer == NUM_OUT_BUFFERS-1) ? 0 : curOutBuffer+1;

                    EncoderPicture &prevPicOut = outPics[prevOutBuffer];
                    EncoderPicture &picOut = outPics[curOutBuffer];
                    EncoderPicture &nextPicOut = outPics[nextOutBuffer];

                    if(!bUsing444)
                    {
                        profileIn("conversion to 4:2:0");

                        if(bUseThreaded420)
                        {
                            for(int i=0; i<numThreads; i++)
                            {
                                convertInfo[i].input     = (LPBYTE)map.pData;
                                convertInfo[i].inPitch   = map.RowPitch;
                                if(bUsingQSV)
                                {
                                    mfxFrameData& data = nextPicOut.mfxOut->Data;
                                    videoEncoder->RequestBuffers(&data);
                                    convertInfo[i].outPitch  = data.Pitch;
                                    convertInfo[i].output[0] = data.Y;
                                    convertInfo[i].output[1] = data.UV;
                                }
                                else
                                {
                                    convertInfo[i].output[0] = nextPicOut.picOut->img.plane[0];
                                    convertInfo[i].output[1] = nextPicOut.picOut->img.plane[1];
                                    convertInfo[i].output[2] = nextPicOut.picOut->img.plane[2];
								}
                                SetEvent(convertInfo[i].hSignalConvert);
                            }

                            if(bFirstEncode)
                                bFirstEncode = bEncode = false;
                        }
                        else
                        {
                            if(bUsingQSV)
                            {
                                mfxFrameData& data = picOut.mfxOut->Data;
                                videoEncoder->RequestBuffers(&data);
                                LPBYTE output[] = {data.Y, data.UV};
                                Convert444toNV12((LPBYTE)map.pData, outputCX, map.RowPitch, data.Pitch, outputCY, 0, outputCY, output);
                            }
                            else
                                Convert444toNV12((LPBYTE)map.pData, outputCX, map.RowPitch, outputCX, outputCY, 0, outputCY, picOut.picOut->img.plane);
                            prevTexture->Unmap(0);
                        }

                        profileOut;
                    }

                    if(bEncode)
                    {
                        //encodeThreadProfiler.reset(::new ProfilerNode(TEXT("EncodeThread"), true));
                        //encodeThreadProfiler->MonitorThread(hEncodeThread);
                        curFramePic = &picOut;
                    }

                    curOutBuffer = nextOutBuffer;
                }
                else
                {
                    //We have to crash, or we end up deadlocking the thread when the convert threads are never signalled
                    if (result == DXGI_ERROR_DEVICE_REMOVED)
                    {
                        String message;

                        HRESULT reason = GetD3D()->GetDeviceRemovedReason();

                        switch (reason)
                        {
                        case DXGI_ERROR_DEVICE_RESET:
                        case DXGI_ERROR_DEVICE_HUNG:
                            message = TEXT("Your video card or driver froze and was reset. Please check for possible hardware / driver issues.");
                            break;
                        case DXGI_ERROR_DEVICE_REMOVED:
                            message = TEXT("Your video card disappeared from the system. Please check for possible hardware / driver issues.");
                            break;
                        case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
                            message = TEXT("Your video driver reported an internal error. Please check for possible hardware / driver issues.");
                            break;
                        case DXGI_ERROR_INVALID_CALL:
                            message = TEXT("Your video driver reported an invalid call. Please check for possible driver issues.");
                            break;
                        default:
                            message = TEXT("DXGI_ERROR_DEVICE_REMOVED");
                            break;
                        }

                        message << TEXT(" This error can also occur if you have enabled opencl in x264 custom settings.");

                        CrashError (TEXT("Texture->Map failed: 0x%08x 0x%08x\r\n\r\n%s"), result, reason, message.Array());
                    }
                    else
                        CrashError (TEXT("Texture->Map failed: 0x%08x"), result);
                }
            }

            if(curCopyTexture == (NUM_RENDER_BUFFERS-1))
                curCopyTexture = 0;
            else
                curCopyTexture++;

            if(curYUVTexture == (NUM_RENDER_BUFFERS-1))
                curYUVTexture = 0;
            else
                curYUVTexture++;

            if (bCongestionControl && bDynamicBitrateSupported && !bTestStream && totalStreamTime > 15000)
            {
                if (curStrain > 25)
                {
                    if (renderStartTimeMS - lastAdjustmentTime > 1500)
                    {
                        if (currentBitRate > 100)
                        {
                            currentBitRate = (int)(currentBitRate * (1.0 - (curStrain / 400)));
                            App->GetVideoEncoder()->SetBitRate(currentBitRate, -1);
                            if (!adjustmentStreamId)
                                adjustmentStreamId = App->AddStreamInfo (FormattedString(TEXT("Congestion detected, dropping bitrate to %d kbps"), currentBitRate).Array(), StreamInfoPriority_Low);
                            else
                                App->SetStreamInfo(adjustmentStreamId, FormattedString(TEXT("Congestion detected, dropping bitrate to %d kbps"), currentBitRate).Array());

                            bUpdateBPS = true;
                        }

                        lastAdjustmentTime = renderStartTimeMS;
                    }
                }
                else if (currentBitRate < defaultBitRate && curStrain < 5 && lastStrain < 5)
                {
                    if (renderStartTimeMS - lastAdjustmentTime > 5000)
                    {
                        if (currentBitRate < defaultBitRate)
                        {
                            currentBitRate += (int)(defaultBitRate * 0.05);
                            if (currentBitRate > defaultBitRate)
                                currentBitRate = defaultBitRate;
                        }

                        App->GetVideoEncoder()->SetBitRate(currentBitRate, -1);
                        /*if (!adjustmentStreamId)
                            App->AddStreamInfo (FormattedString(TEXT("Congestion clearing, raising bitrate to %d kbps"), currentBitRate).Array(), StreamInfoPriority_Low);
                        else
                            App->SetStreamInfo(adjustmentStreamId, FormattedString(TEXT("Congestion clearing, raising bitrate to %d kbps"), currentBitRate).Array());*/

                        App->RemoveStreamInfo(adjustmentStreamId);
                        adjustmentStreamId = 0;

                        bUpdateBPS = true;

                        lastAdjustmentTime = renderStartTimeMS;
                    }
                }
            }
        }

        lastRenderTarget = curRenderTarget;

        if(curRenderTarget == (NUM_RENDER_BUFFERS-1))
            curRenderTarget = 0;
        else
            curRenderTarget++;

        if(bUpdateBPS || !CloseDouble(curStrain, lastStrain) || curFramesDropped != lastFramesDropped)
        {
            PostMessage(hwndMain, OBS_UPDATESTATUSBAR, 0, 0);
            lastStrain = curStrain;

            lastFramesDropped = curFramesDropped;
        }

        //------------------------------------
        // we're about to sleep so we should flush the d3d command queue
        profileIn("flush");
        GetD3D()->Flush();
        profileOut;
        profileOut;
        profileOut; //frame

        //------------------------------------
        // frame sync

        QWORD renderStopTime = GetQPCTimeNS();

        if(bWasLaggedFrame = (frameDelta > frameLengthNS))
        {
            numLongFrames++;
            if(bLogLongFramesProfile && (numLongFrames/float(max(1, numTotalFrames)) * 100.) > logLongFramesProfilePercentage)
                DumpLastProfileData();
        }

        //OSDebugOut(TEXT("Frame adjust time: %d, "), frameTimeAdjust-totalTime);

        numTotalFrames++;
    }

    DisableProjector();

    //encodeThreadProfiler.reset();

    if(!bUsing444)
    {
        if(bUseThreaded420)
        {
            for(int i=0; i<numThreads; i++)
            {
                if(h420Threads[i])
                {
                    convertInfo[i].bKillThread = true;
                    SetEvent(convertInfo[i].hSignalConvert);

                    OSTerminateThread(h420Threads[i], 10000);
                    h420Threads[i] = NULL;
                }

                if(convertInfo[i].hSignalConvert)
                {
                    CloseHandle(convertInfo[i].hSignalConvert);
                    convertInfo[i].hSignalConvert = NULL;
                }

                if(convertInfo[i].hSignalComplete)
                {
                    CloseHandle(convertInfo[i].hSignalComplete);
                    convertInfo[i].hSignalComplete = NULL;
                }
            }

            if(!bFirstEncode)
            {
                ID3D10Texture2D *copyTexture = copyTextures[curCopyTexture];
                copyTexture->Unmap(0);
            }
        }

        if(bUsingQSV)
            for(int i = 0; i < NUM_OUT_BUFFERS; i++)
                delete outPics[i].mfxOut;
        else
            for(int i=0; i<NUM_OUT_BUFFERS; i++)
            {
                x264_picture_clean(outPics[i].picOut);
                delete outPics[i].picOut;
            }
    }

    Free(h420Threads);
    Free(convertInfo);

    Log(TEXT("Total frames rendered: %d, number of late frames: %d (%0.2f%%) (it's okay for some frames to be late)"), numTotalFrames, numLongFrames, (double(numLongFrames)/double(numTotalFrames))*100.0);
}