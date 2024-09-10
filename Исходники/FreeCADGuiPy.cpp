LRESULT CALLBACK
FilterProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (qApp)
        qApp->sendPostedEvents(0, -1); // special DeferredDelete
    return CallNextHookEx(hhook, nCode, wParam, lParam);
}