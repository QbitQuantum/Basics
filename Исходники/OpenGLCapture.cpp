void HandleGLSceneUpdate(HDC hDC)
{
    if(!bTargetAcquired && hdcAcquiredDC == NULL)
    {
        logOutput << CurrentTimeString() << "setting up gl data" << endl;
        PIXELFORMATDESCRIPTOR pfd;

        hwndTarget = WindowFromDC(hDC);

        int pixFormat = GetPixelFormat(hDC);
        DescribePixelFormat(hDC, pixFormat, sizeof(pfd), &pfd);

        if(pfd.cColorBits == 32 && hwndTarget)
        {
            bTargetAcquired = true;
            hdcAcquiredDC = hDC;
            glcaptureInfo.format = GS_BGR;
        }

        OSInitializeTimer();
    }

    if(hDC == hdcAcquiredDC)
    {
        if(bCapturing && WaitForSingleObject(hSignalEnd, 0) == WAIT_OBJECT_0)
            bStopRequested = true;

        if(bCapturing && !IsWindow(hwndOBS))
        {
            hwndOBS = NULL;
            bStopRequested = true;
        }

        if(bCapturing && bStopRequested)
        {
            RUNEVERYRESET logOutput << CurrentTimeString() << "stop requested, terminating gl capture" << endl;

            ClearGLData();
            bCapturing = false;
            bStopRequested = false;
            bReacquiring = false;
        }

        if(!bCapturing && WaitForSingleObject(hSignalRestart, 0) == WAIT_OBJECT_0)
        {
            hwndOBS = FindWindow(OBS_WINDOW_CLASS, NULL);
            if(hwndOBS)
                bCapturing = true;
        }

        RECT rc;
        GetClientRect(hwndTarget, &rc);

        if(bCapturing && bReacquiring)
        {
            if(lastCX != rc.right || lastCY != rc.bottom) //reset if continuing to size within the 3 seconds
            {
                reacquireStart = OSGetTimeMicroseconds();
                lastCX = rc.right;
                lastCY = rc.bottom;
            }

            if(OSGetTimeMicroseconds()-reacquireTime >= 3000000) { //3 second to reacquire
                RUNEVERYRESET logOutput << CurrentTimeString() << "reacquiring gl due to resize..." << endl;
                bReacquiring = false;
            } else {
                return;
            }
        }

        if(bCapturing && (!bHasTextures || rc.right != glcaptureInfo.cx || rc.bottom != glcaptureInfo.cy))
        {
            if (!rc.right || !rc.bottom)
                return;

            if(bHasTextures) //resizing
            {
                ClearGLData();
                bReacquiring = true;
                reacquireStart = OSGetTimeMicroseconds();
                lastCX = rc.right;
                lastCY = rc.bottom;
                return;
            }
            else
            {
                if(hwndOBS)
                    DoGLCPUHook(rc);
                else
                    ClearGLData();
            }
        }

        LONGLONG timeVal = OSGetTimeMicroseconds();

        //check keep alive state, dumb but effective
        if(bCapturing)
        {
            if (!keepAliveTime)
                keepAliveTime = timeVal;

            if((timeVal-keepAliveTime) > 5000000)
            {
                HANDLE hKeepAlive = OpenEvent(EVENT_ALL_ACCESS, FALSE, strKeepAlive.c_str());
                if (hKeepAlive) {
                    CloseHandle(hKeepAlive);
                } else {
                    ClearGLData();
                    logOutput << CurrentTimeString() << "Keepalive no longer found on gl, freeing capture data" << endl;
                    bCapturing = false;
                }

                keepAliveTime = timeVal;
            }
        }

        if(bHasTextures)
        {
            LONGLONG frameTime;
            if(bCapturing)
            {
                if(copyData)
                {
                    if(frameTime = copyData->frameTime)
                    {
                        LONGLONG timeElapsed = timeVal-lastTime;

                        if(timeElapsed >= frameTime)
                        {
                            lastTime += frameTime;
                            if(timeElapsed > frameTime*2)
                                lastTime = timeVal;

                            GLuint texture = gltextures[curCapture];
                            DWORD nextCapture = (curCapture == NUM_BUFFERS-1) ? 0 : (curCapture+1);

                            glReadBuffer(GL_BACK);
                            glBindBuffer(GL_PIXEL_PACK_BUFFER, texture);

                            if(glLockedTextures[curCapture])
                            {
                                OSEnterMutex(glDataMutexes[curCapture]);

                                glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
                                glLockedTextures[curCapture] = false;

                                OSLeaveMutex(glDataMutexes[curCapture]);
                            }

                            glReadPixels(0, 0, glcaptureInfo.cx, glcaptureInfo.cy, GL_BGRA, GL_UNSIGNED_BYTE, 0);

                            //----------------------------------

                            glBindBuffer(GL_PIXEL_PACK_BUFFER, gltextures[nextCapture]);
                            pCopyData = (void*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
                            if(pCopyData)
                            {
                                curCPUTexture = nextCapture;
                                glLockedTextures[nextCapture] = true;

                                RUNEVERYRESET logOutput << CurrentTimeString() << "successfully capturing gl frames via RAM" << endl;

                                SetEvent(hCopyEvent);
                            } else {
                                RUNEVERYRESET logOutput << CurrentTimeString() << "one or more gl frames failed to capture for some reason" << endl;
                            }

                            //----------------------------------

                            glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

                            curCapture = nextCapture;
                        }
                    }
                }
            }
            else {
                RUNEVERYRESET logOutput << CurrentTimeString() << "no longer capturing, terminating gl capture" << endl;
                ClearGLData();
            }
        }
    }
}