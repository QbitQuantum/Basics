static LRESULT CALLBACK
EditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    EditCtrl *w = (EditCtrl *)dwRefData;
    CrashIf(w->hwnd != (HWND)lp);

    if (w->preFilter) {
        bool discard = false;
        auto res = w->preFilter(hwnd, msg, wp, lp, discard);
        if (discard) {
            return res;
        }
    }

    if (WM_NCDESTROY == msg) {
        RemoveWindowSubclass(GetParent(w->hwnd), EditParentProc, 0);
        RemoveWindowSubclass(w->hwnd, EditProc, 0);
        return DefSubclassProc(hwnd, msg, wp, lp);
    }

    // Node: this is sent during creation, which is too early for us (we didn't
    // subclass the window yet)
    // currently, we force it with SetWindowPos(... SMP_FRAMECHANGED)
    if (WM_NCCALCSIZE == msg) {
        NCCALCSIZE_PARAMS *p = (NCCALCSIZE_PARAMS *)lp;
        RECT orig = p->rgrc[0];
        LRESULT res = DefSubclassProc(hwnd, msg, wp, lp);
        RECT curr = p->rgrc[0];
        w->ncDx = RectDx(orig) - RectDx(curr);
        w->ncDy = RectDy(orig) - RectDy(curr);
        return res;
    }

    return DefSubclassProc(hwnd, msg, wp, lp);
}