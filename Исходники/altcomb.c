void SubClassHistoryCombo(HWND combo)
{
    POINT pt;
    HWND editWnd;
    pt.x = 5;
    pt.y = 5;
    editWnd = ChildWindowFromPoint(combo, pt);
    SetWindowLong(combo, GWL_WNDPROC, (int)historyComboProc);
    SetWindowLong(editWnd, GWL_WNDPROC, (int)historyEditComboProc);
}