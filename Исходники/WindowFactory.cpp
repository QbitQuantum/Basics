Window* WindowFactory::create(const int width, const int height) const
{
    HWND windowHandle = createWindow(width, height);
    ShowWindow(windowHandle, SW_SHOWNORMAL);

    Window* window = new Window(windowHandle);
    window->createContext();

    return window;
}