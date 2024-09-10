void TestGlobalSearch::testGlobalSearch()
{
    QString filename(QFile::decodeName(FILES_DATA_DIR "/TestGlobalSearch.kexi"));
    kDebug() << filename;
    NewArgs args(m_argv);
    args.vals[args.count - 1] = qstrdup(QFile::encodeName(filename).constData());

    KexiAboutData aboutData;
    aboutData.setProgramName(ki18n(metaObject()->className()));
    int result = KexiMainWindow::create(args.count, args.vals, aboutData);
    QVERIFY(kapp);
    QCOMPARE(result, 0);

    KLineEdit *lineEdit = kexiTester().widget<KLineEdit*>("globalSearch.lineEdit");
    QVERIFY(lineEdit);
    QTreeView *treeView = kexiTester().widget<QTreeView*>("globalSearch.treeView");
    QVERIFY(treeView);

    lineEdit->setFocus();
    // enter "cars", expect 4 completion items
    QTest::keyClicks(lineEdit, "cars");
    QVERIFY(treeView->isVisible());
    int globalSearchCompletionListRows = treeView->model()->rowCount();
    QCOMPARE(globalSearchCompletionListRows, 4);

    // add "x", expect no completion items and hidden list
    QTest::keyClicks(lineEdit, "x");
    QVERIFY(!treeView->isVisible());
    globalSearchCompletionListRows = treeView->model()->rowCount();
    QCOMPARE(globalSearchCompletionListRows, 0);

    // Escape should clear
    QTest::keyClick(lineEdit, Qt::Key_Escape,  Qt::NoModifier, GUI_DELAY);
    QVERIFY(lineEdit->text().isEmpty());

    QTest::keyClicks(lineEdit, "cars");
    QVERIFY(treeView->isVisible());
    treeView->setFocus();
    QTest::keyPress(treeView, Qt::Key_Down, Qt::NoModifier, GUI_DELAY);
    QTest::keyPress(treeView, Qt::Key_Down, Qt::NoModifier, GUI_DELAY);
    QTest::keyPress(treeView, Qt::Key_Down, Qt::NoModifier, GUI_DELAY);

    // 3rd row should be "cars" form
    QModelIndexList selectedIndices = treeView->selectionModel()->selectedRows();
    QCOMPARE(selectedIndices.count(), 1);
    QCOMPARE(treeView->model()->data(selectedIndices.first(), Qt::DisplayRole).toString(), QLatin1String("cars"));

    // check if proper entry of Project Navigator is selected
    QTest::keyPress(treeView, Qt::Key_Enter, Qt::NoModifier, GUI_DELAY);

    KexiProjectNavigator *projectNavigator = kexiTester().widget<KexiProjectNavigator*>("KexiProjectNavigator");
    QVERIFY(projectNavigator);
    KexiPart::Item* selectedPartItem = projectNavigator->selectedPartItem();
    QVERIFY(selectedPartItem);
    QCOMPARE(selectedPartItem->name(), QLatin1String("cars"));
    QCOMPARE(selectedPartItem->partClass(), QLatin1String("org.kexi-project.form"));

    if (m_goToEventLoop) {
        result = kapp->exec();
        QCOMPARE(result, 0);
    }
}