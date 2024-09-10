//
// HandleMessage
//
LRESULT WINAPI TaskbarListHandler::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    DbgTraceWindowMessage("ITaskbarList", uMsg, wParam, lParam);
    switch (uMsg)
    {
        // Sent by ITaskbarList::ActivateTab and ITaskbarList::SetActiveAlt
        // ActivateTab will send WM_ShellHook(4, hwnd) immediately after this message.
    case WM_USER + 50:
        {
            // wParam = 0, lParam = hWnd
            SendMessage(m_hLiteStep, LM_TASK_MARKASACTIVE, lParam, 0);
        }
        return 0;

        // Sent by ITaskbarList2::MarkFullscreenWindow
    case WM_USER + 60:
        {
            // wParam = 1 to mark as fullscreen, 0 to remove marking
            // lParam = hWnd

            // TODO::This should be sent to the fullscreen monitor
        }
        return 0;

        // Sent by ITaskbarList3::SetProgressValue
    case WM_USER + 64:
        {
            // wParam = hwnd
            // lParam = progress, 0 = 0%, 0xFFFE = 100%
            SendMessage(m_hLiteStep, LM_TASK_SETPROGRESSVALUE, wParam, lParam);
        }
        return 0;

        // Sent by ITaskbarList3::SetProgressState
    case WM_USER + 65:
        {
            // wParam = hwnd
            // lParam = tbpFlags
            SendMessage(m_hLiteStep, LM_TASK_SETPROGRESSSTATE, wParam, lParam);
        }
        return 0;

        // Sent by ITaskbarList3::RegisterTab
    case WM_USER + 67:
        {
            // wParam = hwndTab
            // lParam = hwndMDI
            SendMessage(m_hLiteStep, LM_TASK_REGISTERTAB, wParam, lParam);
        }
        return 0;
        
        // Sent by ITaskbarList3::UnregisterTab
    case WM_USER + 68:
        {
            // wParam = hwndTab
            // lParam = 0
            SendMessage(m_hLiteStep, LM_TASK_UNREGISTERTAB, wParam, 0);
        }
        return 0;

        // Sent by ITaskbarList3::SetTabOrder
    case WM_USER + 71:
        {
            // wParam = hwndTab
            // lParam = hwndInsertBefore
            SendMessage(m_hLiteStep, LM_TASK_SETTABORDER, wParam, lParam);
        }
        return 0;

        // Sent by ITaskbarList3::SetTabActive
    case WM_USER + 72:
        {
            // wParam = hwndTab
            // lParam = 0 ???
            SendMessage(m_hLiteStep, LM_TASK_SETACTIVETAB, wParam, lParam);
        }
        return 0;

        // Mysterious message, sent by control panel windows
    case WM_USER + 75:
        {
            // wParam = hwnd of the control panel
            // lParam = 0 ?

        }
        return 0;

        // Sent by ITaskbarList3::ThumbBarAddButtons
    case WM_USER + 76:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(cButtons, pButton) (first 4 bytes is cButtons)
            LPUINT pData = (LPUINT)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            THUMBBUTTONLIST thumbList;
            thumbList.cButtons = pData[0];
            thumbList.pButton = (THUMBBUTTON*)&pData[1];
            SendMessage(m_hLiteStep, LM_TASK_THUMBBARADDBUTTONS, wParam, (LPARAM)&thumbList);
            SHUnlockShared(pData);
        }
        return 0;
        
        // Sent by ITaskbarList3::ThumbBarUpdateButtons
    case WM_USER + 77:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(cButtons, pButton) (first 4 bytes is cButtons)
            LPUINT pData = (LPUINT)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            THUMBBUTTONLIST thumbList;
            thumbList.cButtons = pData[0];
            thumbList.pButton = (THUMBBUTTON*)&pData[1];
            SendMessage(m_hLiteStep, LM_TASK_THUMBBARUPDATEBUTTONS, wParam, (LPARAM)&thumbList);
            SHUnlockShared(pData);
        }
        return 0;

        // Sent by ITaskbarList3::ThumbBarSetImageList
    case WM_USER + 78:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(himl)
            HIMAGELIST hImageList = (HIMAGELIST)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            SendMessage(m_hLiteStep, LM_TASK_THUMBBARSETIMAGELIST, wParam, (LPARAM)hImageList);
            if (hImageList) {
                SHUnlockShared(hImageList);
            }
        }
        return 0;

        // Sent by ITaskbarList3::SetOverlayIcon
    case WM_USER + 79:
        {
            // wParam = hwnd
            // lParam = hicon
            SendMessage(m_hLiteStep, LM_TASK_SETOVERLAYICON, wParam, lParam);
        }
        return 0;

        // Sent by ITaskbarList3::SetThumbnailTooltip
    case WM_USER + 80:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(pszTip)
            LPWSTR pwzTip = (LPWSTR)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            SendMessage(m_hLiteStep, LM_TASK_SETTHUMBNAILTOOLTIP, wParam, (LPARAM)pwzTip);
            if (pwzTip) {
                SHUnlockShared(pwzTip);
            }
        }
        return 0;

        // Sent by ITaskbarList3::SetThumbnailClip
    case WM_USER + 81:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(prcClip)
            LPRECT prcClip = (LPRECT)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            SendMessage(m_hLiteStep, LM_TASK_SETTHUMBNAILCLIP, wParam, (LPARAM)prcClip);
            if (prcClip) {
                SHUnlockShared(prcClip);
            }
        }
        return 0;

        // Sent by ITaskbarList3::SetOverlayIcon
    case WM_USER + 85:
        {
            // wParam = hwnd
            // lParam = SHSharedAlloc(pszDescription)
            LPWSTR pwzDescription = (LPWSTR)SHLockShared((HANDLE)lParam, m_dwLiteStepProc);
            SendMessage(m_hLiteStep, LM_TASK_SETOVERLAYICONDESC, wParam, (LPARAM)pwzDescription);
            if (pwzDescription) {
                SHUnlockShared(pwzDescription);
            }
        }
        return 0;

        // Sent by ITaskbarList4::SetTabProperties
    case WM_USER + 87:
        {
            // wParam = hwndTab
            // lParam = stpFlags
            SendMessage(m_hLiteStep, LM_TASK_SETTABPROPERTIES, wParam, lParam);
        }
        return 0;

    default:
        {
            // AddTab, DeleteTab, and ActivateTab will send WM_ShellHook
            // TODO::We should consider distinguishing between these and actual WM_SHELLHOOK messages
            // we may wish to remember that a certain window has been "marked" as deleted, so that we
            // don't accidentally recreate it (when activated, or on recycles).
            if (uMsg == WM_ShellHook)
            {
                return SendMessage(m_hLiteStep, uMsg, wParam, lParam);
            }
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}