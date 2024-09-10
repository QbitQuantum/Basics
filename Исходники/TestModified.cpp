void TestModified::testGroupSets()
{
    int spyCount = 0;
    Database* db = new Database();
    Group* root = db->rootGroup();

    Group* g = new Group();
    g->setParent(root);

    QSignalSpy spyModified(db, SIGNAL(modifiedImmediate()));

    root->setUuid(Uuid::random());
    QCOMPARE(spyModified.count(), ++spyCount);
    root->setUuid(root->uuid());
    QCOMPARE(spyModified.count(), spyCount);

    root->setName("test");
    QCOMPARE(spyModified.count(), ++spyCount);
    root->setName(root->name());
    QCOMPARE(spyModified.count(), spyCount);

    root->setNotes("test");
    QCOMPARE(spyModified.count(), ++spyCount);
    root->setNotes(root->notes());
    QCOMPARE(spyModified.count(), spyCount);

    root->setIcon(1);
    QCOMPARE(spyModified.count(), ++spyCount);
    root->setIcon(root->iconNumber());
    QCOMPARE(spyModified.count(), spyCount);

    root->setIcon(Uuid::random());
    QCOMPARE(spyModified.count(), ++spyCount);
    root->setIcon(root->iconUuid());
    QCOMPARE(spyModified.count(), spyCount);


    g->setUuid(Uuid::random());
    QCOMPARE(spyModified.count(), ++spyCount);
    g->setUuid(g->uuid());
    QCOMPARE(spyModified.count(), spyCount);

    g->setName("test");
    QCOMPARE(spyModified.count(), ++spyCount);
    g->setName(g->name());
    QCOMPARE(spyModified.count(), spyCount);

    g->setNotes("test");
    QCOMPARE(spyModified.count(), ++spyCount);
    g->setNotes(g->notes());
    QCOMPARE(spyModified.count(), spyCount);

    g->setIcon(1);
    QCOMPARE(spyModified.count(), ++spyCount);
    g->setIcon(g->iconNumber());
    QCOMPARE(spyModified.count(), spyCount);

    g->setIcon(Uuid::random());
    QCOMPARE(spyModified.count(), ++spyCount);
    g->setIcon(g->iconUuid());
    QCOMPARE(spyModified.count(), spyCount);

    delete db;
}