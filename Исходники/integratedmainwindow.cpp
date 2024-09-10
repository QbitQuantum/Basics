/*!
    Forces Windows to refresh the cached pixmap it received from \a sendPreview.
 */
void IntegratedMainWindow::invalidateThumbnail()
{
#ifdef Q_WS_WIN
    DwmInvalidateIconicBitmaps(winId());
#endif
}