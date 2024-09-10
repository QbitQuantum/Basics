static LRESULT CALLBACK TreeProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    UNUSED(uIdSubclass);
    TreeCtrl* w = (TreeCtrl*)dwRefData;
    CrashIf(w->hwnd != (HWND)hwnd);

    if (w->preFilter) {
        bool discard = false;
        auto res = w->preFilter(hwnd, msg, wp, lp, discard);
        if (discard) {
            return res;
        }
    }

    if (WM_ERASEBKGND == msg) {
        return FALSE;
    }

    if (WM_KEYDOWN == msg) {
        if (HandleKey(hwnd, wp)) {
            return 0;
        }
    }

    if (WM_NCDESTROY == msg) {
        Unsubclass(w);
        return DefSubclassProc(hwnd, msg, wp, lp);
    }

    return DefSubclassProc(hwnd, msg, wp, lp);
}