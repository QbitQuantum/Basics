void QWindowsBackingStore::flush(QWindow *window, const QRegion &region,
                                        const QPoint &offset)
{
    Q_ASSERT(window);

    const QRect br = region.boundingRect();
    if (QWindowsContext::verbose > 1)
        qCDebug(lcQpaBackingStore) << __FUNCTION__ << this << window << offset << br;
    QWindowsWindow *rw = QWindowsWindow::baseWindowOf(window);

#ifndef Q_OS_WINCE
    const bool hasAlpha = rw->format().hasAlpha();
    const Qt::WindowFlags flags = window->flags();
    if ((flags & Qt::FramelessWindowHint) && QWindowsWindow::setWindowLayered(rw->handle(), flags, hasAlpha, rw->opacity()) && hasAlpha) {
        // Windows with alpha: Use blend function to update.
        QRect r = window->frameGeometry();
        QPoint frameOffset(window->frameMargins().left(), window->frameMargins().top());
        QRect dirtyRect = br.translated(offset + frameOffset);

        SIZE size = {r.width(), r.height()};
        POINT ptDst = {r.x(), r.y()};
        POINT ptSrc = {0, 0};
        BLENDFUNCTION blend = {AC_SRC_OVER, 0, (BYTE)(255.0 * rw->opacity()), AC_SRC_ALPHA};
        if (QWindowsContext::user32dll.updateLayeredWindowIndirect) {
            RECT dirty = {dirtyRect.x(), dirtyRect.y(),
                dirtyRect.x() + dirtyRect.width(), dirtyRect.y() + dirtyRect.height()};
            UPDATELAYEREDWINDOWINFO info = {sizeof(info), NULL, &ptDst, &size, m_image->hdc(), &ptSrc, 0, &blend, ULW_ALPHA, &dirty};
            QWindowsContext::user32dll.updateLayeredWindowIndirect(rw->handle(), &info);
        } else {
            QWindowsContext::user32dll.updateLayeredWindow(rw->handle(), NULL, &ptDst, &size, m_image->hdc(), &ptSrc, 0, &blend, ULW_ALPHA);
        }
    } else {
#endif
        const HDC dc = rw->getDC();
        if (!dc) {
            qErrnoWarning("%s: GetDC failed", __FUNCTION__);
            return;
        }

        if (!BitBlt(dc, br.x(), br.y(), br.width(), br.height(),
                    m_image->hdc(), br.x() + offset.x(), br.y() + offset.y(), SRCCOPY)) {
            const DWORD lastError = GetLastError(); // QTBUG-35926, QTBUG-29716: may fail after lock screen.
            if (lastError != ERROR_SUCCESS && lastError != ERROR_INVALID_HANDLE)
                qErrnoWarning(lastError, "%s: BitBlt failed", __FUNCTION__);
        }
        rw->releaseDC();
#ifndef Q_OS_WINCE
    }
#endif

    // Write image for debug purposes.
    if (QWindowsContext::verbose > 2 && lcQpaBackingStore().isDebugEnabled()) {
        static int n = 0;
        const QString fileName = QString::fromLatin1("win%1_%2.png").
                arg(rw->winId()).arg(n++);
        m_image->image().save(fileName);
        qCDebug(lcQpaBackingStore) << "Wrote " << m_image->image().size() << fileName;
    }
}