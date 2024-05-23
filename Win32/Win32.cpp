#include <windows.h>

class Win32App {
public:
    Win32App(HINSTANCE hInstance) : hInstance_(hInstance) {}

    int Run() {
        if (!CreateMainWindow()) {
            return -1;
        }

        ShowWindow(hWnd_, SW_SHOW);
        UpdateWindow(hWnd_);

        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return static_cast<int>(msg.wParam);
    }

private:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // Добавьте здесь вашу отрисовку
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hWnd, &ps);
        }
                     break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    bool CreateMainWindow() {
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance_;
        wc.lpszClassName = L"Win32AppWindowClass";

        if (!RegisterClass(&wc)) {
            return false;
        }

        hWnd_ = CreateWindowEx(
            0,
            L"Win32AppWindowClass",
            L"Win32 Application",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            hInstance_,
            nullptr
        );

        if (!hWnd_) {
            return false;
        }

        return true;
    }

    HINSTANCE hInstance_;
    HWND hWnd_;
};

int main() {
    Win32App app(GetModuleHandle(NULL));
    return app.Run();
}