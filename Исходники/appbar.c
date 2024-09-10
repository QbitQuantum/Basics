static void testwindow_setpos(HWND hwnd)
{
    struct testwindow_info* info = (struct testwindow_info*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    APPBARDATA abd;
    BOOL ret;

    ok(info != NULL, "got unexpected ABN_POSCHANGED notification\n");

    if (!info || !info->registered)
    {
        return;
    }

    if (info->to_be_deleted)
    {
        win_skip("Some Win95 and NT4 systems send messages to removed taskbars\n");
        return;
    }

    abd.cbSize = sizeof(abd);
    abd.hWnd = hwnd;
    abd.uEdge = info->edge;
    abd.rc = info->desired_rect;
    ret = SHAppBarMessage(ABM_QUERYPOS, &abd);
    ok(ret == TRUE, "SHAppBarMessage returned %i\n", ret);
    switch (info->edge)
    {
        case ABE_BOTTOM:
            ok(info->desired_rect.top == abd.rc.top, "ABM_QUERYPOS changed top of rect from %i to %i\n", info->desired_rect.top, abd.rc.top);
            abd.rc.top = abd.rc.bottom - (info->desired_rect.bottom - info->desired_rect.top);
            break;
        case ABE_LEFT:
            ok(info->desired_rect.right == abd.rc.right, "ABM_QUERYPOS changed right of rect from %i to %i\n", info->desired_rect.right, abd.rc.right);
            abd.rc.right = abd.rc.left + (info->desired_rect.right - info->desired_rect.left);
            break;
        case ABE_RIGHT:
            ok(info->desired_rect.left == abd.rc.left, "ABM_QUERYPOS changed left of rect from %i to %i\n", info->desired_rect.left, abd.rc.left);
            abd.rc.left = abd.rc.right - (info->desired_rect.right - info->desired_rect.left);
            break;
        case ABE_TOP:
            ok(info->desired_rect.bottom == abd.rc.bottom, "ABM_QUERYPOS changed bottom of rect from %i to %i\n", info->desired_rect.bottom, abd.rc.bottom);
            abd.rc.bottom = abd.rc.top + (info->desired_rect.bottom - info->desired_rect.top);
            break;
    }

    ret = SHAppBarMessage(ABM_SETPOS, &abd);
    ok(ret == TRUE, "SHAppBarMessage returned %i\n", ret);

    info->allocated_rect = abd.rc;
    MoveWindow(hwnd, abd.rc.left, abd.rc.top, abd.rc.right-abd.rc.left, abd.rc.bottom-abd.rc.top, TRUE);
}