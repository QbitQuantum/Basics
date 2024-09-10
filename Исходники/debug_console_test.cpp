void DebugConsoleTest::testX11Client()
{
    DebugConsoleModel model;
    QModelIndex x11TopLevelIndex = model.index(0, 0, QModelIndex());
    QVERIFY(x11TopLevelIndex.isValid());
    // we don't have any windows yet
    QCOMPARE(model.rowCount(x11TopLevelIndex), 0);
    QVERIFY(!model.hasChildren(x11TopLevelIndex));
    // child index must be invalid
    QVERIFY(!model.index(0, 0, x11TopLevelIndex).isValid());
    QVERIFY(!model.index(0, 1, x11TopLevelIndex).isValid());
    QVERIFY(!model.index(0, 2, x11TopLevelIndex).isValid());
    QVERIFY(!model.index(1, 0, x11TopLevelIndex).isValid());

    // start glxgears, to get a window, which should be added to the model
    QSignalSpy rowsInsertedSpy(&model, &QAbstractItemModel::rowsInserted);
    QVERIFY(rowsInsertedSpy.isValid());

    QProcess glxgears;
    glxgears.start(QStringLiteral("glxgears"));
    QVERIFY(glxgears.waitForStarted());

    QVERIFY(rowsInsertedSpy.wait());
    QCOMPARE(rowsInsertedSpy.count(), 1);
    QVERIFY(model.hasChildren(x11TopLevelIndex));
    QCOMPARE(model.rowCount(x11TopLevelIndex), 1);
    QCOMPARE(rowsInsertedSpy.first().at(0).value<QModelIndex>(), x11TopLevelIndex);
    QCOMPARE(rowsInsertedSpy.first().at(1).value<int>(), 0);
    QCOMPARE(rowsInsertedSpy.first().at(2).value<int>(), 0);

    QModelIndex clientIndex = model.index(0, 0, x11TopLevelIndex);
    QVERIFY(clientIndex.isValid());
    QCOMPARE(model.parent(clientIndex), x11TopLevelIndex);
    QVERIFY(model.hasChildren(clientIndex));
    QVERIFY(model.rowCount(clientIndex) != 0);
    QCOMPARE(model.columnCount(clientIndex), 2);
    // other indexes are still invalid
    QVERIFY(!model.index(0, 1, x11TopLevelIndex).isValid());
    QVERIFY(!model.index(0, 2, x11TopLevelIndex).isValid());
    QVERIFY(!model.index(1, 0, x11TopLevelIndex).isValid());

    // the clientIndex has children and those are properties
    for (int i = 0; i < model.rowCount(clientIndex); i++) {
        const QModelIndex propNameIndex = model.index(i, 0, clientIndex);
        QVERIFY(propNameIndex.isValid());
        QCOMPARE(model.parent(propNameIndex), clientIndex);
        QVERIFY(!model.hasChildren(propNameIndex));
        QVERIFY(!model.index(0, 0, propNameIndex).isValid());
        QVERIFY(model.data(propNameIndex, Qt::DisplayRole).isValid());
        QCOMPARE(model.data(propNameIndex, Qt::DisplayRole).userType(), int(QMetaType::QString));

        // and the value
        const QModelIndex propValueIndex = model.index(i, 1, clientIndex);
        QVERIFY(propValueIndex.isValid());
        QCOMPARE(model.parent(propValueIndex), clientIndex);
        QVERIFY(!model.index(0, 0, propValueIndex).isValid());
        QVERIFY(!model.hasChildren(propValueIndex));
        // TODO: how to test whether the values actually work?

        // and on third column we should not get an index any more
        QVERIFY(!model.index(i, 2, clientIndex).isValid());
    }
    // row after count should be invalid
    QVERIFY(!model.index(model.rowCount(clientIndex), 0, clientIndex).isValid());

    // creating a second model should be initialized directly with the X11 child
    DebugConsoleModel model2;
    QVERIFY(model2.hasChildren(model2.index(0, 0, QModelIndex())));

    // now close the window again, it should be removed from the model
    QSignalSpy rowsRemovedSpy(&model, &QAbstractItemModel::rowsRemoved);
    QVERIFY(rowsRemovedSpy.isValid());

    glxgears.terminate();
    QVERIFY(glxgears.waitForFinished());

    QVERIFY(rowsRemovedSpy.wait());
    QCOMPARE(rowsRemovedSpy.count(), 1);
    QCOMPARE(rowsRemovedSpy.first().first().value<QModelIndex>(), x11TopLevelIndex);
    QCOMPARE(rowsRemovedSpy.first().at(1).value<int>(), 0);
    QCOMPARE(rowsRemovedSpy.first().at(2).value<int>(), 0);

    // the child should be gone again
    QVERIFY(!model.hasChildren(x11TopLevelIndex));
    QVERIFY(!model2.hasChildren(model2.index(0, 0, QModelIndex())));
}