/**
 *  This function 'subclasses' an existing control with the toolbar.  This is
 *  not proper subclassing, as we hide the subclassed control, but borrow its
 *  position.
 *
 *  @param id       The id of the control to subclass.
 */
void DialogToolbar::Subclass(UINT id)
{
    CWnd  *parent        = GetParent();
    CWnd  *toolbarHolder = parent->GetDlgItem(id);
    CSize sizeBar        = CalcFixedLayout(FALSE, TRUE);
    WINDOWPLACEMENT wpl;
    toolbarHolder->GetWindowPlacement(&wpl);
    wpl.rcNormalPosition.bottom = wpl.rcNormalPosition.top  + sizeBar.cy + 4;
    wpl.rcNormalPosition.right  = wpl.rcNormalPosition.left + sizeBar.cx + 4;
    toolbarHolder->SetWindowPlacement(&wpl);
    SetWindowPlacement(&wpl);
    RepositionBars
    (
        AFX_IDW_CONTROLBAR_FIRST, 
        AFX_IDW_CONTROLBAR_LAST, 
        0
    );
    toolbarHolder->ShowWindow(SW_HIDE);
    SetWindowPos
    (
        &CWnd::wndTop,
        0, 0, 0, 0,
        SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOMOVE
    );
    INIT_AUTO_TOOLTIP();
}