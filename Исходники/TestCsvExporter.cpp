void TestCsvExporter::testExport()
{
    Group* groupRoot = m_db->rootGroup();
    Group* group = new Group();
    group->setName("Test Group Name");
    group->setParent(groupRoot);
    Entry* entry = new Entry();
    entry->setGroup(group);
    entry->setTitle("Test Entry Title");
    entry->setUsername("Test Username");
    entry->setPassword("Test Password");
    entry->setUrl("http://test.url");
    entry->setNotes("Test Notes");

    QBuffer buffer;
    QVERIFY(buffer.open(QIODevice::ReadWrite));
    m_csvExporter->exportDatabase(&buffer, m_db);

    QString expectedResult = QString().append(ExpectedHeaderLine).append("\"Test Group Name\",\"Test Entry Title\",\"Test Username\",\"Test Password\",\"http://test.url\",\"Test Notes\"\n");

    QCOMPARE(QString::fromUtf8(buffer.buffer().constData()), expectedResult);
}