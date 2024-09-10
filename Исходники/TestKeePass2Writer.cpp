void TestKeePass2Writer::initTestCase()
{
    Crypto::init();

    CompositeKey key;
    key.addKey(PasswordKey("test"));

    m_dbOrg = new Database();
    m_dbOrg->setKey(key);
    m_dbOrg->metadata()->setName("TESTDB");
    Group* group = m_dbOrg->rootGroup();
    group->setUuid(Uuid::random());
    group->setNotes("I'm a note!");
    Entry* entry = new Entry();
    entry->setPassword(QString::fromUtf8("\xc3\xa4\xa3\xb6\xc3\xbc\xe9\x9b\xbb\xe7\xb4\x85"));
    entry->setUuid(Uuid::random());
    entry->attributes()->set("test", "protectedTest", true);
    QVERIFY(entry->attributes()->isProtected("test"));
    entry->attachments()->set("myattach.txt", QByteArray("this is an attachment"));
    entry->attachments()->set("aaa.txt", QByteArray("also an attachment"));
    entry->setGroup(group);
    Group* groupNew = new Group();
    groupNew->setUuid(Uuid::random());
    groupNew->setName("TESTGROUP");
    groupNew->setNotes("I'm a sub group note!");
    groupNew->setParent(group);

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);

    KeePass2Writer writer;
    writer.writeDatabase(&buffer, m_dbOrg);
    QVERIFY(!writer.error());
    buffer.seek(0);
    KeePass2Reader reader;
    m_dbTest = reader.readDatabase(&buffer, key);
    QVERIFY(!reader.hasError());
    QVERIFY(m_dbTest);
}