void KillWindow() {
    window_ready=false;
    wglMakeCurrent(NULL,NULL);  // release GL rendering context
    if (hRC) {
        wglDeleteContext(hRC);
        hRC=NULL;
    }

    if (hWnd && hDC) {
        ReleaseDC(hWnd,hDC);
    }
    hDC = NULL;

    if (hWnd) {
        DestroyWindow(hWnd);
    }
    hWnd = NULL;

    if (hOriginalWindowStation) {
        SetProcessWindowStation(hOriginalWindowStation);
        CloseWindowStation(hInteractiveWindowStation);
        hInteractiveWindowStation = NULL;
    }

    if (hOriginalDesktop) {
        SetThreadDesktop(hOriginalDesktop);
        CloseDesktop(hInteractiveDesktop);
        hInteractiveDesktop = NULL;
    }
}