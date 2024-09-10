/*************************************************************************
    Win32 'Window Procedure' function
*************************************************************************/
LRESULT CALLBACK Win32AppHelper::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CHAR:
        s_samplesFramework->injectChar((CEGUI::utf32)wParam);
        break;

    case WM_MOUSELEAVE:
        mouseLeaves();
        break;

    case WM_NCMOUSEMOVE:
        mouseLeaves();
        break;

    case WM_MOUSEMOVE:
        mouseEnters();

        s_samplesFramework->injectMousePosition((float)(LOWORD(lParam)), (float)(HIWORD(lParam)));
        break;

    case WM_LBUTTONDOWN:
        s_samplesFramework->injectMouseButtonDown(CEGUI::LeftButton);
        break;

    case WM_LBUTTONUP:
        s_samplesFramework->injectMouseButtonUp(CEGUI::LeftButton);
        break;

    case WM_RBUTTONDOWN:
        s_samplesFramework->injectMouseButtonDown(CEGUI::RightButton);
        break;

    case WM_RBUTTONUP:
        s_samplesFramework->injectMouseButtonUp(CEGUI::RightButton);
        break;

    case WM_MBUTTONDOWN:
        s_samplesFramework->injectMouseButtonDown(CEGUI::MiddleButton);
        break;

    case WM_MBUTTONUP:
        s_samplesFramework->injectMouseButtonUp(CEGUI::MiddleButton);
        break;

    case 0x020A: // WM_MOUSEWHEEL:
        s_samplesFramework->injectMouseWheelChange(static_cast<float>((short)HIWORD(wParam)) / static_cast<float>(120));
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        {
            // get CEGUI::System as a pointer so we can detect if it's not
            // instantiated yet.
            CEGUI::System* cegui_system = CEGUI::System::getSingletonPtr();

            // only continue if CEGUI is up an running and window was not
            // minimised (else it's just a waste of time)
            if ((cegui_system != 0) && (wParam != SIZE_MINIMIZED))
            {
                // get renderer identification string
                CEGUI::Renderer* renderer = cegui_system->getRenderer();
                CEGUI::String id(renderer->getIdentifierString());

                // invoke correct function based on the renderer we have ID'd
#ifdef CEGUI_BUILD_RENDERER_DIRECT3D9
                if (id.find("Official Direct3D 9") != id.npos)
                    DeviceReset_Direct3D9(hWnd, renderer);
#endif
#ifdef CEGUI_BUILD_RENDERER_DIRECT3D10
                if (id.find("Official Direct3D 10") != id.npos)
                    DeviceReset_Direct3D10(hWnd, renderer);
#endif
#ifdef CEGUI_BUILD_RENDERER_DIRECT3D11
                if (id.find("Official Direct3D 11") != id.npos)
                    DeviceReset_Direct3D11(hWnd, renderer);
#endif
            }
        }
        break;

    case WM_PAINT:
        {
            HDC         hDC;
            PAINTSTRUCT ps;

            hDC = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;
        }

    default:
        return(DefWindowProc(hWnd, message, wParam, lParam));
        break;
    }

    return 0;
}