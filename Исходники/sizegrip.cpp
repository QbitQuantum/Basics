/*!
    \fn void CSizeGrip::mousePressEvent(QMouseEvent * event)

    Receives the mouse press events for the widget, and primes the
    resize operation. The mouse press event is passed in the \a event
    parameter.
*/
void CSizeGrip::mousePressEvent(QMouseEvent * e)
{
    ungrabGesture(Qt::TapAndHoldGesture);

    if (e->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(e);
        return;
    }


    QWidget *tlw = qt_sizegrip_topLevelWidget();
    p = e->globalPos();
    gotMousePress = true;
    r = tlw->geometry();

#ifdef Q_WS_X11
    #if QT_VERSION >= 0x050000
    // Use a native X11 sizegrip for "real" top-level windows if supported.
    if (tlw->isWindow() && X11->isSupportedByWM(ATOM(_NET_WM_MOVERESIZE))
        && !(tlw->windowFlags() & Qt::X11BypassWindowManagerHint)
        && !tlw->testAttribute(Qt::WA_DontShowOnScreen) && !qt_widget_private(tlw)->hasHeightForWidth()) {
        XEvent xev;
        xev.xclient.type = ClientMessage;
        xev.xclient.message_type = ATOM(_NET_WM_MOVERESIZE);
        xev.xclient.display = X11->display;
        xev.xclient.window = tlw->winId();
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = e->globalPos().x();
        xev.xclient.data.l[1] = e->globalPos().y();
        if (atBottom())
            xev.xclient.data.l[2] = atLeft() ? 6 : 4; // bottomleft/bottomright
        else
            xev.xclient.data.l[2] = atLeft() ? 0 : 2; // topleft/topright
        xev.xclient.data.l[3] = Button1;
        xev.xclient.data.l[4] = 0;
        XUngrabPointer(X11->display, X11->time);
        XSendEvent(X11->display, QX11Info::appRootWindow(x11Info().screen()), False,
                   SubstructureRedirectMask | SubstructureNotifyMask, &xev);
        return;
    }
#endif
#endif // Q_WS_X11
#ifdef Q_WS_WIN
    #if QT_VERSION >= 0x050000
    if (tlw->isWindow() && !tlw->testAttribute(Qt::WA_DontShowOnScreen) && !qt_widget_private(tlw)->hasHeightForWidth()) {
        uint orientation = 0;
        if (atBottom())
            orientation = atLeft() ? SZ_SIZEBOTTOMLEFT : SZ_SIZEBOTTOMRIGHT;
        else
            orientation = atLeft() ? SZ_SIZETOPLEFT : SZ_SIZETOPRIGHT;

        ReleaseCapture();
        PostMessage(tlw->winId(), WM_SYSCOMMAND, orientation, 0);
        return;
    }
#endif
#endif // Q_WS_WIN

    // Find available desktop/workspace geometry.
    QRect availableGeometry;
    bool hasVerticalSizeConstraint = true;
    bool hasHorizontalSizeConstraint = true;
    if (tlw->isWindow())
        availableGeometry = QApplication::desktop()->availableGeometry(tlw);
    else {
        const QWidget *tlwParent = tlw->parentWidget();
        // Check if tlw is inside QAbstractScrollArea/QScrollArea.
        // If that's the case tlw->parentWidget() will return the viewport
        // and tlw->parentWidget()->parentWidget() will return the scroll area.
#ifndef QT_NO_SCROLLAREA
        QAbstractScrollArea *scrollArea = qobject_cast<QAbstractScrollArea *>(tlwParent->parentWidget());
        if (scrollArea) {
            hasHorizontalSizeConstraint = scrollArea->horizontalScrollBarPolicy() == Qt::ScrollBarAlwaysOff;
            hasVerticalSizeConstraint = scrollArea->verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOff;
        }
#endif // QT_NO_SCROLLAREA
        availableGeometry = tlwParent->contentsRect();
    }

    // Find frame geometries, title bar height, and decoration sizes.
    const QRect frameGeometry = tlw->frameGeometry();
    const int titleBarHeight = qMax(tlw->geometry().y() - frameGeometry.y(), 0);
    const int bottomDecoration = qMax(frameGeometry.height() - tlw->height() - titleBarHeight, 0);
    const int leftRightDecoration = qMax((frameGeometry.width() - tlw->width()) / 2, 0);

    // Determine dyMax depending on whether the sizegrip is at the bottom
    // of the widget or not.
    if (atBottom()) {
        if (hasVerticalSizeConstraint)
            dyMax = availableGeometry.bottom() - r.bottom() - bottomDecoration;
        else
            dyMax = INT_MAX;
    } else {
        if (hasVerticalSizeConstraint)
            dyMax = availableGeometry.y() - r.y() + titleBarHeight;
        else
            dyMax = -INT_MAX;
    }

    // In RTL mode, the size grip is to the left; find dxMax from the desktop/workspace
    // geometry, the size grip geometry and the width of the decoration.
    if (atLeft()) {
        if (hasHorizontalSizeConstraint)
            dxMax = availableGeometry.x() - r.x() + leftRightDecoration;
        else
            dxMax = -INT_MAX;
    } else {
        if (hasHorizontalSizeConstraint)
            dxMax = availableGeometry.right() - r.right() - leftRightDecoration;
        else
            dxMax = INT_MAX;
    }
}