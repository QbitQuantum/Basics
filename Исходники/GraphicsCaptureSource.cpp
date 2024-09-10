void GraphicsCaptureSource::Tick(float fSeconds)
{
    if(hSignalExit && WaitForSingleObject(hSignalExit, 0) == WAIT_OBJECT_0) {
        Log(TEXT("Exit signal received, terminating capture"));
        EndCapture();
    }

    if(bCapturing && !hSignalReady && targetProcessID)
        hSignalReady = GetEvent(String() << CAPTURE_READY_EVENT << UINT(targetProcessID));

    if (injectHelperProcess && WaitForSingleObject(injectHelperProcess, 0) == WAIT_OBJECT_0)
    {
        DWORD exitCode;
        GetExitCodeProcess(injectHelperProcess, (DWORD*)&exitCode);
        CloseHandle(injectHelperProcess);
        injectHelperProcess = nullptr;

        if (exitCode != 0)
        {
            AppWarning(TEXT("safe inject Helper: Failed, error code = %d"), exitCode);
            bErrorAcquiring = true;
        }
    }

    if (hSignalReady) {

        DWORD val = WaitForSingleObject(hSignalReady, 0);
        if (val == WAIT_OBJECT_0)
            NewCapture();
        else if (val != WAIT_TIMEOUT)
            OSDebugOut(TEXT("what the heck?  val is 0x%08lX\n"), val);
    }

    static int floong = 0;

    if (hSignalReady) {
        if (floong++ == 60) {
            OSDebugOut(TEXT("valid, bCapturing = %s\n"), bCapturing ? TEXT("true") : TEXT("false"));
            floong = 0;
        }
    } else {
        if (floong++ == 60) {
            OSDebugOut(TEXT("not valid, bCapturing = %s\n"), bCapturing ? TEXT("true") : TEXT("false"));
            floong = 0;
        }
    }

    if(bCapturing && !capture)
    {
        if(++captureWaitCount >= API->GetMaxFPS())
        {
            bCapturing = false;
        }
    }

    captureCheckInterval += fSeconds;

    if(!bCapturing && !bErrorAcquiring)
    {
        if ((!bUseHotkey && captureCheckInterval >= 3.0f) ||
            (bUseHotkey && hwndNextTarget != NULL))
        {
            if (bUseHotkey && hwndNextTarget)
            {
                strWindowClass.SetLength(255);
                RealGetWindowClassW(hwndNextTarget, strWindowClass.Array(), 255);
                strWindowClass.SetLength(slen(strWindowClass));

                data->SetString(L"windowClass", strWindowClass);
            }

            AttemptCapture();
            captureCheckInterval = 0.0f;
        }
    }
    else
    {
        if(!IsWindow(hwndCapture) && !bUseDWMCapture) {
            Log(TEXT("Capture window 0x%08lX invalid or changing, terminating capture"), DWORD(hwndCapture));
            EndCapture();
        } else if (hTargetProcess && WaitForSingleObject(hTargetProcess, 0) == WAIT_OBJECT_0) {
            Log(TEXT("Capture process %s exited, terminating capture"), strExecutable.Array());
            EndCapture();
        } else if (bUseHotkey && hwndNextTarget && hwndNextTarget != hwndTarget) {
            Log(TEXT("Capture hotkey triggered for new window, terminating capture"));
            EndCapture();
        } else if (captureCheckInterval >= 5.0f) {
            //expensive check, only run it every 5 seconds
            DWORD processID;
            if (GetWindowThreadProcessId(hwndCapture, &processID) && processID != targetProcessID) {
                Log(TEXT("Capture window 0x%08lX changed owner to process %d (trying to capture %d), terminating capture"), DWORD(hwndCapture), processID, targetProcessID);
                EndCapture();
            }
            captureCheckInterval = 0.0f;
        } else {
            hwndNextTarget = NULL;
        }
    }
}