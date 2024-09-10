void ConnectionWindow::rfbLog(const char *format, ...)
{
    if ( !quiet() ) {
        va_list args;
        QString message;
        va_start(args, format);
        message.vsprintf(format, args);
        message.prepend(tr("RFB") + ": ");
        va_end(args);
        VncMainWindow::log(message);
    }
}