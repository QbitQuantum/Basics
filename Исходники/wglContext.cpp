WglContext::WglContext(WglContext* shared, const ContextSettings& settings, unsigned int width, unsigned int height) :
m_window       (NULL),
m_deviceContext(NULL),
m_context      (NULL),
m_ownsWindow   (true)
{
    // The target of the context is a hidden window.
    // We can't create a memory DC (the resulting context wouldn't be compatible
    // with other contexts), and we don't add the extra complexity of P-Buffers;
    // we can still support them in the future if this solution is not good enough.

    // Create the hidden window
    m_window = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(m_window, SW_HIDE);
    m_deviceContext = GetDC(m_window);

    // Create the context
    if (m_deviceContext)
        createContext(shared, VideoMode::getDesktopMode().bitsPerPixel, settings);
}