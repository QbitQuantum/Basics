void qt_message_box(void * frontend, const char *title, const char *fmt, ...)
{
    QString msg;
    va_list args;
    assert(frontend);
    GuiTerminalWindow *f = static_cast<GuiTerminalWindow*>(frontend);
    va_start (args, fmt);
    QMessageBox::critical(f, QString(title), msg.vsprintf(fmt, args), QMessageBox::Ok);
    va_end (args);
}