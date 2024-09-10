//*******************************************************************************************
BOOL CBCGPFrameWnd::PreTranslateMessage(MSG* pMsg)
{
    BOOL bProcessAccel = TRUE;

    switch (pMsg->message)
    {
    case WM_SYSKEYDOWN:
#ifndef BCGP_EXCLUDE_RIBBON
        if (m_Impl.m_pRibbonBar != NULL && m_Impl.m_pRibbonBar->OnSysKeyDown (this, pMsg->wParam, pMsg->lParam))
        {
            return TRUE;
        }

        if (pMsg->wParam == VK_F4 && m_Impl.m_pRibbonBar != NULL && m_Impl.m_pRibbonBar->IsBackstageViewActive())
        {
            break;
        }
#endif
        if (CBCGPPopupMenu::GetSafeActivePopupMenu() == NULL)
        {
            m_Impl.CancelToolbarMode();
        }

    case WM_CONTEXTMENU:
        if (!globalData.m_bSysUnderlineKeyboardShortcuts && !globalData.m_bUnderlineKeyboardShortcuts)
        {
            globalData.m_bUnderlineKeyboardShortcuts = TRUE;
            CBCGPToolBar::RedrawUnderlines ();
        }

        if (CBCGPPopupMenu::GetSafeActivePopupMenu() != NULL && (pMsg->wParam == VK_MENU || pMsg->wParam == VK_F10))
        {
            CBCGPPopupMenu::m_pActivePopupMenu->SendMessage (WM_CLOSE);
            return TRUE;
        }
        else if (m_Impl.ProcessKeyboard ((int) pMsg->wParam))
        {
            return TRUE;
        }
        break;

    case WM_SYSKEYUP:
        if (m_Impl.ProcessSysKeyUp(pMsg->wParam, pMsg->lParam))
        {
            return TRUE;
        }
        break;

    case WM_KEYDOWN:
        //-----------------------------------------
        // Pass keyboard action to the active menu:
        //-----------------------------------------
        if (!CBCGPFrameImpl::IsHelpKey (pMsg) &&
                m_Impl.ProcessKeyboard ((int) pMsg->wParam, &bProcessAccel))
        {
            return TRUE;
        }

        if (pMsg->wParam == VK_ESCAPE)
        {
            if (IsFullScreen())
            {
                if (!IsPrintPreview())
                {
                    m_Impl.InvokeFullScreenCommand();
                    return TRUE;
                }
            }

            CBCGPSmartDockingManager* pSDManager = NULL;
            if ((pSDManager = m_dockManager.GetSDManagerPermanent()) != NULL &&
                    pSDManager->IsStarted())
            {
                pSDManager->CauseCancelMode ();
            }

            CBCGPSlider* pSlider = DYNAMIC_DOWNCAST (CBCGPSlider, GetCapture ());
            if (pSlider != NULL)
            {
                pSlider->SendMessage (WM_CANCELMODE);
                return TRUE;
            }
        }

        if (!bProcessAccel)
        {
            return FALSE;
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        CPoint pt (BCG_GET_X_LPARAM(pMsg->lParam), BCG_GET_Y_LPARAM(pMsg->lParam));
        CWnd* pWnd = CWnd::FromHandle (pMsg->hwnd);

        if (pWnd != NULL && ::IsWindow (pMsg->hwnd))
        {
            pWnd->ClientToScreen (&pt);
        }

        if (m_Impl.ProcessMouseClick (pMsg->message, pt, pMsg->hwnd))
        {
            return TRUE;
        }

        if (!::IsWindow (pMsg->hwnd))
        {
            return TRUE;
        }
    }
    break;

    case WM_NCLBUTTONDOWN:
    case WM_NCLBUTTONUP:
    case WM_NCRBUTTONDOWN:
    case WM_NCRBUTTONUP:
    case WM_NCMBUTTONDOWN:
    case WM_NCMBUTTONUP:
        if (m_Impl.ProcessMouseClick (pMsg->message,
                                      CPoint (BCG_GET_X_LPARAM(pMsg->lParam), BCG_GET_Y_LPARAM(pMsg->lParam)),
                                      pMsg->hwnd))
        {
            return TRUE;
        }
        break;

    case WM_MOUSEWHEEL:
        if (m_Impl.ProcessMouseWheel (pMsg->wParam, pMsg->lParam))
        {
            return TRUE;
        }
        break;

    case WM_MOUSEMOVE:
    {
        CPoint pt (BCG_GET_X_LPARAM(pMsg->lParam), BCG_GET_Y_LPARAM(pMsg->lParam));
        CWnd* pWnd = CWnd::FromHandle (pMsg->hwnd);

        if (pWnd != NULL)
        {
            pWnd->ClientToScreen (&pt);
        }

        if (m_Impl.ProcessMouseMove (pt))
        {
            return TRUE;
        }
    }
    }

    return CFrameWnd::PreTranslateMessage(pMsg);
}