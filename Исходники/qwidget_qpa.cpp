void QWidgetPrivate::create_sys(WId window, bool initializeWindow, bool destroyOldWindow)
{
    Q_Q(QWidget);

    Q_UNUSED(window);
    Q_UNUSED(initializeWindow);
    Q_UNUSED(destroyOldWindow);

    Qt::WindowFlags flags = data.window_flags;

    if (!q->testAttribute(Qt::WA_NativeWindow) && !q->isWindow())
        return; // we only care about real toplevels

    QWindow *win = topData()->window;
    // topData() ensures the extra is created but does not ensure 'window' is non-null
    // in case the extra was already valid.
    if (!win) {
        createTLSysExtra();
        win = topData()->window;
    }

    win->setFlags(data.window_flags);
    fixPosIncludesFrame();
    if (q->testAttribute(Qt::WA_Moved))
        win->setGeometry(q->geometry());
    else
        win->resize(q->size());
    win->setScreen(QGuiApplication::screens().value(topData()->screenIndex, 0));

    if (q->testAttribute(Qt::WA_TranslucentBackground)) {
        QSurfaceFormat format;
        format.setAlphaBufferSize(8);
        win->setFormat(format);
    }

    if (QWidget *nativeParent = q->nativeParentWidget()) {
        if (nativeParent->windowHandle()) {
            if (flags & Qt::Window) {
                win->setTransientParent(nativeParent->windowHandle());
                win->setParent(0);
            } else {
                win->setTransientParent(0);
                win->setParent(nativeParent->windowHandle());
            }
        }
    }

    qt_window_private(win)->positionPolicy = topData()->posIncludesFrame ?
        QWindowPrivate::WindowFrameInclusive : QWindowPrivate::WindowFrameExclusive;
    win->create();
    // Enable nonclient-area events for QDockWidget and other NonClientArea-mouse event processing.
    if ((flags & Qt::Desktop) == Qt::Window)
        win->handle()->setFrameStrutEventsEnabled(true);

    data.window_flags = win->flags();

    QBackingStore *store = q->backingStore();

    if (!store) {
        if (win && q->windowType() != Qt::Desktop)
            q->setBackingStore(new QBackingStore(win));
        else
            q->setAttribute(Qt::WA_PaintOnScreen, true);
    }

    setWindowModified_helper();
    setWinId(win->winId());

    // Check children and create windows for them if necessary
    q_createNativeChildrenAndSetParent(q);

    if (extra && !extra->mask.isEmpty())
        setMask_sys(extra->mask);

    // If widget is already shown, set window visible, too
    if (q->isVisible())
        win->setVisible(true);
}