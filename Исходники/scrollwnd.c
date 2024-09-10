/* 
 * shoulded be called before scrollwnd is used
 * hWnd: the scrolled window
 */
int scrollwnd_init (HWND hWnd, PSWDATA pswdata)
{
    if (!pswdata)
        return -1;

    SetWindowAdditionalData2 (hWnd, 0);
    ShowScrollBar (hWnd, SB_HORZ, FALSE);
    ShowScrollBar (hWnd, SB_VERT, FALSE);

    svInitData (hWnd, pswdata);
    SetWindowAdditionalData2 (hWnd, (DWORD) pswdata);

    /* set scrollbar status */
    scrolled_set_hscrollinfo (hWnd, &pswdata->scrdata);
    scrolled_set_vscrollinfo (hWnd, &pswdata->scrdata);
                                    
    return 0;
}