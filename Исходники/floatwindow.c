LRESULT CALLBACK
FloatToolbarWndProc(HWND hwnd,
                    UINT Message,
                    WPARAM wParam,
                    LPARAM lParam)
{
    PFLT_WND FltInfo;

    /* Get the window context */
    FltInfo = (PFLT_WND)GetWindowLongPtr(hwnd,
                                         GWLP_USERDATA);
    if (FltInfo == NULL && Message != WM_CREATE)
    {
        goto HandleDefaultMessage;
    }

    switch(Message)
    {
        case WM_CREATE:
        {
            FltInfo = (PFLT_WND)(((LPCREATESTRUCT)lParam)->lpCreateParams);

            /*FIXME: read this from registry */
//            FltInfo->bShow = TRUE;

            SetWindowLongPtr(hwnd,
                             GWLP_USERDATA,
                             (LONG_PTR)FltInfo);

            FltInfo->bOpaque = FALSE;

            SetWindowLongPtr(hwnd,
                             GWL_EXSTYLE,
                             GetWindowLongPtr(hwnd,
                                              GWL_EXSTYLE) | WS_EX_LAYERED);

            /* set the tranclucency to 60% */
            FltInfo->Transparancy = 60;
            SetLayeredWindowAttributes(hwnd,
                                       0,
                                       (255 * FltInfo->Transparancy) / 100,
                                       LWA_ALPHA);
        }
        break;

        case WM_TIMER:
        {
            DoTimer(FltInfo,
                    wParam);
        }
        break;

        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
        {
            if (FltInfo->bOpaque == FALSE)
            {

                RedrawWindow(hwnd,
                             NULL,
                             NULL,
                             RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);

                FltInfo->bOpaque = TRUE;
                //MessageBox(NULL, _T("in"), _T("Hit test"), MB_OK | MB_ICONEXCLAMATION);

                /* timer to check if cursor is in toolbar coords */
                SetTimer(hwnd,
                         ID_TIMER1,
                         200,
                         NULL);

                /* timer to fade in the toolbars */
                SetTimer(hwnd,
                         ID_TIMER2,
                         50,
                         NULL);
            }
        }
        break;

        case WM_CLOSE:
            ShowHideWindow(FltInfo->hSelf);
        break;

        case WM_COMMAND:
        {
            if (LOWORD(wParam) == IDCANCEL)
                ShowHideWindow(FltInfo->hSelf);

            switch(LOWORD(wParam))
            {
                case ID_NEW:
                    MessageBox(hwnd, _T("Kapow!"), _T("Hit test"), MB_OK | MB_ICONEXCLAMATION);
                break;

                case ID_CLONESTAMP:
                case ID_COLORPICKER:
                case ID_ECLIPSE:
                case ID_ECLIPSESEL:
                case ID_ERASER:
                case ID_FREEFORM:
                case ID_LASOO:
                case ID_LINE:
                case ID_MAGICWAND:
                case ID_MOVE:
                case ID_MOVESEL:
                case ID_PAINTBRUSH:
                case ID_PAINTBUCKET:
                case ID_PENCIL:
                case ID_RECOLORING:
                case ID_RECTANGLE:
                case ID_ROUNDRECT:
                case ID_TEXT:
                case ID_ZOOM:
                    /*SendMessage(Info->hSelf,
                                LOWORD(wParam),
                                wParam,
                                lParam);*/
                break;
            }
        }
        break;

        case WM_NCACTIVATE:
            /* FIXME: needs fully implementing */
            return DefWindowProc(hwnd,
                                 Message,
                                 TRUE,
                                 lParam);
        break;

        case WM_DESTROY:
            SetWindowLongPtr(hwnd,
                             GWLP_USERDATA,
                             0);
        break;

        default:
HandleDefaultMessage:
            return DefWindowProc(hwnd,
                                 Message,
                                 wParam,
                                 lParam);
    }

    return 0;
}