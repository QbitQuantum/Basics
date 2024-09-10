bool MainWindowEx::winEvent(MSG *msg, long *result)
{
    bool fCallDWP = true;
    BOOL fDwmEnabled = FALSE;
    LRESULT lRet = 0;
    HRESULT hr = S_OK;
    HWND hWnd       = msg->hwnd;
    UINT message    = msg->message;
    WPARAM wParam   = msg->wParam;
    LPARAM lParam   = msg->lParam;

    // Winproc worker for custom frame issues.
    hr = DwmIsCompositionEnabled(&fDwmEnabled);
    if (!SUCCEEDED(hr) || !fDwmEnabled)
    {
        qDebug() << "DWM not enabled";
        return false;
    }
    fCallDWP = !DwmDefWindowProc(hWnd, message, wParam, lParam, &lRet);

    switch(message)
    {
        // 鼠标在窗口边缘时，缩放可用
        case WM_NCHITTEST:
        {
            return hitTestNCA(msg, result);
        }

        // Handle window activation.
        case WM_ACTIVATE:
        {
            // Extend the frame into the client area.
            MARGINS margins = { -1, -1, -1, -1 };
            hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

            if (!SUCCEEDED(hr))
            {
                // Handle error.
                qDebug() << "Extend frame to Client Area error";
            }

            fCallDWP = true;
            lRet = 0;
        };
        break;

        // 缩放
        case WM_NCCALCSIZE:
        {
            if(wParam == TRUE)
            {
                // Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
                NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

                pncsp->rgrc[0].left   = pncsp->rgrc[0].left   - 1;
                pncsp->rgrc[0].top    = pncsp->rgrc[0].top    - 1;
                pncsp->rgrc[0].right  = pncsp->rgrc[0].right  + 1;
                pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom + 1;

                QRect rect;
                rect.setLeft(pncsp->rgrc[0].left);
                rect.setTop(pncsp->rgrc[0].top);
                rect.setRight(pncsp->rgrc[0].right);
                rect.setBottom(pncsp->rgrc[0].bottom);
                emit sizeChanged();

                lRet = 0;
                // No need to pass the message on to the DefWindowProc.
                fCallDWP = false;
            }
        };
        break;

        case WM_NCMOUSELEAVE:
        {
//    if( uRow ==0 || uRow == 2 || uCol == 0 || uCol == 2)
//        emit hoverLeave();
//    else
//        emit hoverEnter();
            if(!this->geometry().contains(QCursor::pos()))
            {
//                QTimer::singleShot(400, this, SIGNAL(hoverLeave()));
                emit hoverLeave();
            }
        };
        break;

        case WM_NCMOUSEMOVE:
        {
            emit hoverEnter();
        };
        break;
        //最大化/最小化
        case WM_GETMINMAXINFO:
        {
            MINMAXINFO *mmi = (MINMAXINFO*)lParam;
            QRect rect = QApplication::desktop()->availableGeometry();
//            mmi->ptMaxSize.x = rect.width();
//            mmi->ptMaxSize.y = rect.height();
            mmi->ptMaxPosition.x = 0;
            mmi->ptMaxPosition.y = 0;
            mmi->ptMinTrackSize.x = 400;
            mmi->ptMinTrackSize.y = 260;
            mmi->ptMaxTrackSize.x = rect.width();
            mmi->ptMaxTrackSize.y = rect.height();

            lRet = 0;
            fCallDWP = false;
        };
        break;
    }

    if (!fCallDWP)
        *result = lRet;

    return !fCallDWP;
}