void touchmind::win::CanvasPanel::SetGestureConfigs(HWND hWnd) {
    if (!touchmind::util::OSVersionChecker::IsWin7()) {
        return;
    }
    GESTURECONFIG gc[5];
    UINT uiGcs = 5;
    gc[0].dwID = GID_ZOOM;
    gc[0].dwWant = GC_ZOOM;
    gc[0].dwBlock = 0;
    gc[1].dwID = GID_PAN;
    gc[1].dwWant = GC_PAN_WITH_INERTIA;
    gc[1].dwBlock = 0;
    gc[2].dwID = GID_ROTATE;
    gc[2].dwWant = 0;
    gc[2].dwBlock = GC_ROTATE;
    gc[3].dwID = GID_TWOFINGERTAP;
    gc[3].dwWant = GC_TWOFINGERTAP;
    gc[3].dwBlock = 0;
    gc[4].dwID = GID_PRESSANDTAP;
    gc[4].dwWant = GC_PRESSANDTAP;
    gc[4].dwBlock = 0;
    BOOL bResult = SetGestureConfig(hWnd, 0, uiGcs, gc, sizeof(GESTURECONFIG));
    if (!bResult) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << util::LastError(util::LastErrorArgs(L"SetGestureConfig", lastError));
    }
}