    static INT_PTR CALLBACK windowProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
    {
        DiWin32EGLWindow* window = (DiWin32EGLWindow*)LongToPtr(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        DiRenderWindow* renderWnd = DiBase::Driver->FindRenderWindow(DiWndHandle(hwnd));

        if (window && window->DestroyingWindow())
            return 0;

        switch (msg)
        {
        case WM_CREATE:
            ::UpdateWindow(hwnd);
            break;

        case WM_CLOSE:
            DiBase::CommandMgr->ExecuteCommand("quit");
            break;
        case WM_ACTIVATE:
        {
            bool active = (LOWORD(wParam) != WA_INACTIVE);
            if (active)
            {
                if (renderWnd)
                    renderWnd->GetRenderBuffer()->SetActive(true);
            }
            else
            {
                if (renderWnd)
                    renderWnd->GetRenderBuffer()->SetActive(false);
            }
            break;
        }
    
        case WM_COPYDATA:
        {
            const char* str = (const char*)(((COPYDATASTRUCT*)lParam)->lpData);
            DiString s(str, ((COPYDATASTRUCT*)lParam)->cbData);
            DiBase::CommandMgr->ExecuteCommand(s.c_str());
            break;
        }

        default:
            return ::DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }