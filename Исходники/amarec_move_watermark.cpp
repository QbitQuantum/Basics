BOOL func_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp)
{
    if (!fp) {
        return FALSE;
    }
    if (!editp) {
        return FALSE;
    }

    if (fp->exfunc->is_saving(editp)) {
        return FALSE;
    }

    if (s_filtered_width <= 0 || s_filtered_height <= 0) {
        return FALSE;
    }

    int leftMargin, bottomMargin;
    Mask const* mask = Mask::selectMask(s_filtered_width, s_filtered_height, leftMargin, bottomMargin);
    if (!mask) {
        return FALSE;
    }

    int const minXShift = -leftMargin;
    int const maxXShift = s_filtered_width - mask->width_ - leftMargin;

    int const minYShift = -(s_filtered_height - bottomMargin - mask->height_);
    int const maxYShift = bottomMargin;

    bool changed = false;
    changed |= fp->track_s[0] != minXShift;
    changed |= fp->track_e[0] != maxXShift;
    changed |= fp->track_s[1] != minYShift;
    changed |= fp->track_e[1] != maxYShift;

    if (changed) {
        fp->track_s[0] = minXShift;
        fp->track_e[0] = maxXShift;

        fp->track_s[1] = minYShift;
        fp->track_e[1] = maxYShift;

        char const* kClassName = "msctls_trackbar32";
        HWND deltaX = FindWindowExA(hwnd, nullptr, kClassName, nullptr);
        if (deltaX) {
            SendMessageA(deltaX, TBM_SETRANGE, (WPARAM)FALSE, (LPARAM)MAKELONG(minXShift, maxXShift));
            HWND deltaY = FindWindowExA(hwnd, deltaX, kClassName, nullptr);
            if (deltaY) {
                SendMessageA(deltaY, TBM_SETRANGE, (WPARAM)FALSE, (LPARAM)MAKELONG(minYShift, maxYShift));
            }
        }
    }

    return FALSE;
}