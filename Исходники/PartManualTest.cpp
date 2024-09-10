void PartManualTest::testShortcutOverride()
{
    // FIXME: This test asks the user to press shortcut key sequences manually because
    // the result is different than when sending the key press via QTest::keyClick()
    //
    // When the key presses are sent manually, Konsole::TerminalDisplay::event() is called
    // and the overrideShortcut() signal is emitted by the part.
    // When the key presses are sent automatically, the shortcut is triggered but
    // Konsole::TerminalDisplay::event() is not called and the overrideShortcut() signal is
    // not emitted by the part.

    // Create a main window with a menu and a test
    // action with a shortcut set to Ctrl+S, which is also used by the terminal
    KMainWindow* mainWindow = new KMainWindow();
    QMenu* fileMenu = mainWindow->menuBar()->addMenu("File");
    QAction* testAction = fileMenu->addAction("Test");
    testAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(testAction, SIGNAL(triggered()), this, SLOT(shortcutTriggered()));

    // Create terminal part and embed in into the main window
    KParts::Part* terminalPart = createPart();
    QVERIFY(terminalPart);
    mainWindow->setCentralWidget(terminalPart->widget());
    TerminalInterface* terminal = qobject_cast<TerminalInterface*>(terminalPart);
    QVERIFY(terminal);
    terminal->sendInput("Press Ctrl+S twice.\n");
    mainWindow->show();

    // Test shortcut with override disabled, so the shortcut will be triggered
    _shortcutTriggered = false;
    _override = false;
    _overrideCalled = false;
    QVERIFY(connect(terminalPart, SIGNAL(overrideShortcut(QKeyEvent*,bool&)),
                    this, SLOT(overrideShortcut(QKeyEvent*,bool&))));

    //QTest::keyClick(terminalPart->widget(),Qt::Key_S,Qt::ControlModifier);
    _shortcutEventLoop = new QEventLoop();
    _shortcutEventLoop->exec();

    QVERIFY(_overrideCalled);
    QVERIFY(_shortcutTriggered);
    QVERIFY(!_override);

    // Test shortcut with override enabled, so the shortcut will not be triggered
    _override = true;
    _overrideCalled = false;
    _shortcutTriggered = false;

    //QTest::keyClick(terminalPart->widget(),Qt::Key_S,Qt::ControlModifier);
    _shortcutEventLoop->exec();

    QVERIFY(_overrideCalled);
    QVERIFY(!_shortcutTriggered);
    QVERIFY(_override);

    delete _shortcutEventLoop;
    delete terminalPart;
    delete mainWindow;
}