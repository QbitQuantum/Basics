void tst_QGuiApplication::focusObject()
{
    int argc = 0;
    QGuiApplication app(argc, 0);

    if (qApp->platformName().toLower() == QLatin1String("wayland"))
        QSKIP("Wayland: This fails. Figure out why.");

    QObject obj1, obj2, obj3;
    const QRect screenGeometry = QGuiApplication::primaryScreen()->availableVirtualGeometry();

    DummyWindow window1;
#if defined(Q_OS_QNX)
    window1.setSurfaceType(QSurface::OpenGLSurface);
#endif
    window1.resize(windowSize, windowSize);
    window1.setTitle(QStringLiteral("focusObject:window1"));
    window1.setFramePosition(QPoint(screenGeometry.left() + spacing, screenGeometry.top() + spacing));
    DummyWindow window2;
    window2.resize(windowSize, windowSize);
    window2.setFramePosition(QPoint(screenGeometry.left() + 2 * spacing + windowSize, screenGeometry.top() + spacing));
    window2.setTitle(QStringLiteral("focusObject:window2"));

    window1.show();

#if defined(Q_OS_QNX) // We either need to create a eglSurface or a create a backing store
                      // and then post the window in order for screen to show the window
    QOpenGLContext context;
    context.create();
    context.makeCurrent(&window1);
    QTest::qWaitForWindowExposed(&window1); // Buffer swap only succeeds with exposed window
    context.swapBuffers(&window1);
#endif

    QSignalSpy spy(&app, SIGNAL(focusObjectChanged(QObject*)));


    // verify active window focus propagates to qguiapplication
    window1.requestActivate();
    QVERIFY(QTest::qWaitForWindowActive(&window1));
    QCOMPARE(app.focusWindow(), &window1);

    window1.setFocusObject(&obj1);
    QCOMPARE(app.focusObject(), &obj1);
    QCOMPARE(spy.count(), 1);

    spy.clear();
    window1.setFocusObject(&obj2);
    QCOMPARE(app.focusObject(), &obj2);
    QCOMPARE(spy.count(), 1);

    spy.clear();
    window2.setFocusObject(&obj3);
    QCOMPARE(app.focusObject(), &obj2); // not yet changed
    window2.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window2));
    QTRY_COMPARE(app.focusWindow(), &window2);
    QCOMPARE(app.focusObject(), &obj3);
    QCOMPARE(spy.count(), 1);

    // focus change on unfocused window does not show
    spy.clear();
    window1.setFocusObject(&obj1);
    QCOMPARE(spy.count(), 0);
    QCOMPARE(app.focusObject(), &obj3);
}