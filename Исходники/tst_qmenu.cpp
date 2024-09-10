void tst_QMenu::overrideMenuAction()
{
	//test the override menu action by first creating an action to which we set its menu
	QMainWindow w;

	QAction *aFileMenu = new QAction("&File", &w);
	w.menuBar()->addAction(aFileMenu);

	QMenu *m = new QMenu(&w);
	QAction *menuaction = m->menuAction();
	connect(m, SIGNAL(triggered(QAction*)), SLOT(onActivated(QAction*)));
	aFileMenu->setMenu(m); //this sets the override menu action for the QMenu
    QCOMPARE(m->menuAction(), aFileMenu);

#ifdef Q_WS_MAC
    QSKIP("On Mac, we need to create native key events to test menu action activation", SkipAll);
#elif defined(Q_OS_WINCE)
    QSKIP("On Windows CE, we need to create native key events to test menu action activation", SkipAll);
#elif defined(Q_OS_SYMBIAN)
    QSKIP("On Symbian OS, we need to create native key events to test menu action activation", SkipAll);
#endif

    QAction *aQuit = new QAction("Quit", &w);
	aQuit->setShortcut(QKeySequence("Ctrl+X"));
	m->addAction(aQuit);

	w.show();
    QApplication::setActiveWindow(&w);
    w.setFocus();
    QTest::qWaitForWindowShown(&w);
    QTRY_VERIFY(w.hasFocus());

	//test of the action inside the menu
	QTest::keyClick(&w, Qt::Key_X, Qt::ControlModifier);
    QTRY_COMPARE(activated, aQuit);

	//test if the menu still pops out
	QTest::keyClick(&w, Qt::Key_F, Qt::AltModifier);
    QTRY_VERIFY(m->isVisible());

	delete aFileMenu;

	//after the deletion of the override menu action,
	//the menu should have its default menu action back
	QCOMPARE(m->menuAction(), menuaction);

}