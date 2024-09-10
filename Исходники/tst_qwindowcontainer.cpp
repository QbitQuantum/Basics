void tst_QWindowContainer::testAncestorChange()
{
    QWidget root;
    QWidget *left = new QWidget(&root);
    QWidget *right = new QWidget(&root);

    root.setGeometry(0, 0, 200, 100);
    left->setGeometry(0, 0, 100, 100);
    right->setGeometry(100, 0, 100, 100);

    QWindow *window = new QWindow();
    QWidget *container = QWidget::createWindowContainer(window, left);
    container->setGeometry(0, 0, 100, 100);

    //      Root
    //      + left
    //      | + container
    //      |   + window
    //      + right
    root.show();
    QVERIFY(QTest::qWaitForWindowExposed(&root));
    QCOMPARE(window->geometry(), QRect(0, 0, 100, 100));

    container->setParent(right);
    //      Root
    //      + left
    //      + right
    //        + container
    //          + window
    QCOMPARE(window->geometry(), QRect(100, 0, 100, 100));

    QWidget *newRoot = new QWidget(&root);
    newRoot->setGeometry(50, 50, 200, 200);
    right->setParent(newRoot);
    //      Root
    //      + left
    //      + newRoot
    //        + right
    //          + container
    //            + window
    QCOMPARE(window->geometry(), QRect(150, 50, 100, 100));
    newRoot->move(0, 0);
    QCOMPARE(window->geometry(), QRect(100, 0, 100, 100));

    newRoot->setParent(0);
    newRoot->setGeometry(100, 100, 200, 200);
    newRoot->show();
    QVERIFY(QTest::qWaitForWindowExposed(newRoot));
    QCOMPARE(newRoot->windowHandle(), window->parent());
    //      newRoot
    //      + right
    //        + container
    //          + window
    QCOMPARE(window->geometry(), QRect(100, 0, 100, 100));
}