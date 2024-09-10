void CChatWnd::Open()
{
    if ( IsIconic() ) ShowWindow( SW_SHOWNORMAL );
    BringWindowToTop();
    SetForegroundWindow();
}