void Trace(LPSTR format, ...)
    {
    char message[256];
    va_list args = NULL;
    va_start(args, format);
    StringCchVPrintfA(message, 256, format, args);

    char buffer[256];
    StringCchCopyA(buffer, 256, "ode: ");
    StringCchCatA(buffer, 256, message);
    OutputDebugStringA(buffer);
    }