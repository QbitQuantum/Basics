void EventEditTest::shouldEmitEventWhenPressEnter()
{
    MessageViewer::EventEdit edit;
    edit.show();
    // make sure the window is active so we can test for focus
    qApp->setActiveWindow(&edit);
    QTest::qWaitForWindowExposed(&edit);
    QVERIFY(edit.isVisible());

    KMime::Message::Ptr msg(new KMime::Message);
    QString subject = QStringLiteral("Test Note");
    msg->subject(true)->fromUnicodeString(subject, "us-ascii");
    edit.setMessage(msg);
    QLineEdit *eventedit = edit.findChild<QLineEdit *>(QStringLiteral("eventedit"));
    eventedit->setFocus();
    QSignalSpy spy(&edit, SIGNAL(createEvent(KCalCore::Event::Ptr,Akonadi::Collection)));
    QTest::keyClick(eventedit, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
}