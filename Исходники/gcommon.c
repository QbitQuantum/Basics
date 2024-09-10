LRESULT CALLBACK ScrollWndProc (
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam
) {
    Gwidget_t *widget, *child;
    WINDOWPOS *wpos;
    PIXpoint_t po;
    RECT r;
    int dummy, dx, dy, wi;

    if (Gnocallbacks || !(widget = findwidget (hwnd, G_SCROLLWIDGET)))
        return (DefWindowProc(hwnd, message, wparam, lparam));
    switch (message) {
    case WM_WINDOWPOSCHANGED:
        wpos = (WINDOWPOS *) lparam;
        if (!(wpos->flags & SWP_NOSIZE))
            handleresize (widget);
        break;
    case WM_HSCROLL:
    case WM_VSCROLL:
        for (wi = 0; wi < Gwidgetn; wi++) {
            child = &Gwidgets[wi];
            if (child->inuse && child->pwi == widget - &Gwidgets[0])
                break;
        }
        if (wi == Gwidgetn)
            return (DefWindowProc(hwnd, message, wparam, lparam));
        GetClientRect (widget->w, &r);
        GetScrollRange (widget->w, SB_HORZ, &dummy, &dx);
        GetScrollRange (widget->w, SB_VERT, &dummy, &dy);
        po.x = GetScrollPos (widget->w, SB_HORZ);
        po.y = GetScrollPos (widget->w, SB_VERT);
        switch (message) {
        case WM_HSCROLL:
            switch (LOWORD (wparam)) {
            case SB_BOTTOM:        po.x = dx;                  break;
            case SB_LINEDOWN:      po.x += 10;                 break;
            case SB_LINEUP:        po.x -= 10;                 break;
            case SB_PAGEDOWN:      po.x += (r.right - r.left); break;
            case SB_PAGEUP:        po.x -= (r.right - r.left); break;
            case SB_THUMBPOSITION: po.x = HIWORD (wparam);     break;
            case SB_THUMBTRACK:    po.x = HIWORD (wparam);     break;
            case SB_TOP:           po.x = 0;                   break;
            }
            po.x = min (po.x, dx);
            po.x = max (po.x, 0);
            SetScrollPos (widget->w, SB_HORZ, po.x, TRUE);
            SetWindowPos (
                child->w, (HWND) NULL, -po.x, -po.y, 0, 0,
                SWP_NOSIZE | SWP_NOZORDER
            );
            break;
        case WM_VSCROLL:
            switch (LOWORD (wparam)) {
            case SB_BOTTOM:        po.y = dy;                  break;
            case SB_LINEDOWN:      po.y += 10;                 break;
            case SB_LINEUP:        po.y -= 10;                 break;
            case SB_PAGEDOWN:      po.y += (r.bottom - r.top); break;
            case SB_PAGEUP:        po.y -= (r.bottom - r.top); break;
            case SB_THUMBPOSITION: po.y = HIWORD (wparam);     break;
            case SB_THUMBTRACK:    po.y = HIWORD (wparam);     break;
            case SB_TOP:           po.y = 0;                   break;
            }
            po.y = min (po.y, dy);
            po.y = max (po.y, 0);
            SetScrollPos (widget->w, SB_VERT, po.y, TRUE);
            SetWindowPos (
                child->w, (HWND) NULL, -po.x, -po.y, 0, 0,
                SWP_NOSIZE | SWP_NOZORDER
            );
            break;
        }
        break;
    default:
        return (DefWindowProc (hwnd, message, wparam, lparam));
    }
    return 0;
}