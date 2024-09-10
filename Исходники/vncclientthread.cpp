void VncClientThread::outputHandler(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    QString message;
    message.vsprintf(format, args);

    va_end(args);

    message = message.trimmed();

    kDebug(5011) << message;

    if ((message.contains("Couldn't convert ")) ||
            (message.contains("Unable to connect to VNC server")))
        outputErrorMessageString = i18n("Server not found.");

    if ((message.contains("VNC connection failed: Authentication failed, too many tries")) ||
            (message.contains("VNC connection failed: Too many authentication failures")))
        outputErrorMessageString = i18n("VNC authentication failed because of too many authentication tries.");

    if (message.contains("VNC connection failed: Authentication failed"))
        outputErrorMessageString = i18n("VNC authentication failed.");

    if (message.contains("VNC server closed connection"))
        outputErrorMessageString = i18n("VNC server closed connection.");

    // internal messages, not displayed to user
    if (message.contains("VNC server supports protocol version 3.889")) // see http://bugs.kde.org/162640
        outputErrorMessageString = "INTERNAL:APPLE_VNC_COMPATIBILTY";
}