// This hook exists whilst the slideshow is running but only listens on the
// slideshows thread. It listens out for slide changes, message WM_USER+22.
LRESULT CALLBACK CwpProc(int nCode, WPARAM wParam, LPARAM lParam){
    CWPSTRUCT *cwp;
    cwp = (CWPSTRUCT *)lParam;
    HHOOK hook = NULL;
    char filename[MAX_PATH];

    DWORD windowThread = GetWindowThreadProcessId(cwp->hwnd, NULL);
    int id = -1;
    for (int i = 0; i < MAX_PPTS; i++)
    {
        if (pptView[i].dwThreadId == windowThread)
        {
            id = i;
            hook = pptView[id].hook;
            break;
        }
    }
    if ((id >= 0) && (nCode == HC_ACTION))
    {
        if (cwp->message == WM_USER + 22)
        {
            if (pptView[id].state != PPT_LOADED)
            {
                if ((pptView[id].currentSlide > 0)
                    && (pptView[id].previewPath != NULL
                    && strlen(pptView[id].previewPath) > 0))
                {
                    sprintf_s(filename, MAX_PATH, "%s%i.bmp",
                        pptView[id].previewPath,
                        pptView[id].currentSlide);
                    CaptureAndSaveWindow(cwp->hwnd, filename);
                }
                if (((cwp->wParam == 0)
                    || (pptView[id].slideNos[1] == cwp->wParam))
                    && (pptView[id].currentSlide > 0))
                {
                    pptView[id].state = PPT_LOADED;
                    pptView[id].currentSlide = pptView[id].slideCount + 1;
                }
                else
                {
                    if (cwp->wParam > 0)
                    {
                        pptView[id].currentSlide = pptView[id].currentSlide + 1;
                        pptView[id].slideNos[pptView[id].currentSlide]
                            = cwp->wParam;
                        pptView[id].slideCount = pptView[id].currentSlide;
                        pptView[id].lastSlideSteps = 0;
                    }
                }
            }
            else
            {
                if (cwp->wParam > 0)
                {
                    if(pptView[id].guess > 0
                        && pptView[id].slideNos[pptView[id].guess] == 0)
                    {
                        pptView[id].currentSlide = 0;
                    }
                    for(int i = 1; i <= pptView[id].slideCount; i++)
                    {
                        if(pptView[id].slideNos[i] == cwp->wParam)
                        {
                            pptView[id].currentSlide = i;
                            break;
                        }
                    }
                    if(pptView[id].currentSlide == 0)
                    {
                        pptView[id].slideNos[pptView[id].guess] = cwp->wParam;
                        pptView[id].currentSlide = pptView[id].guess;
                    }
                    pptView[id].guess = 0;
                }
            }
        }
        if ((pptView[id].state != PPT_CLOSED)

            &&(cwp->message == WM_CLOSE || cwp->message == WM_QUIT))
        {
            pptView[id].state = PPT_CLOSING;
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}