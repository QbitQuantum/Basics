void WaitForEventTest::testWaitEnded() {
    QObject parentObject;

    WaitForEvent waitForEvent(&parentObject, QEvent::ChildAdded);
    waitForEvent.setActive(true);

    //WaitFor* must be registered in order to be used with QSignalSpy
    int waitForStarType = qRegisterMetaType<WaitFor*>("WaitFor*");
    QSignalSpy waitEndedSpy(&waitForEvent, SIGNAL(waitEnded(WaitFor*)));

    QObject* childObject = new QObject();
    childObject->setParent(&parentObject);

    QVERIFY(waitForEvent.conditionMet());
    QCOMPARE(waitEndedSpy.count(), 1);
    QVariant argument = waitEndedSpy.at(0).at(0);
    QCOMPARE(argument.userType(), waitForStarType);
    QCOMPARE(qvariant_cast<WaitFor*>(argument), &waitForEvent);
}