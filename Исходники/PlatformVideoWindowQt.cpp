PlatformVideoWindow::PlatformVideoWindow()
{
    QWindow* win = new FullScreenVideoWindow();
    m_window = win;
    win->setFlags(win->flags() | Qt::FramelessWindowHint);
    m_videoWindowId = win->winId();
}