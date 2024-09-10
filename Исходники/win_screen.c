//static
void drv_win_screen_update(void)
{
    GdiFlush();

    eline = 1;
    RedrawWindow( hWnd, 0, 0, RDW_INVALIDATE/*|RDW_NOERASE*/ );

}