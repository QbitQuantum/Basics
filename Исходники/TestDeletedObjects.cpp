void TestDeletedObjects::createAndDelete(Database* db, int delObjectsSize)
{
    QCOMPARE(db->deletedObjects().size(), delObjectsSize);
    Group* root = db->rootGroup();
    int rootChildrenCount = root->children().size();

    Group* g = new Group();
    g->setParent(root);
    Uuid gUuid = Uuid::random();
    g->setUuid(gUuid);
    delete g;
    QCOMPARE(db->deletedObjects().size(), ++delObjectsSize);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-1).uuid, gUuid);
    QCOMPARE(rootChildrenCount, root->children().size());

    Group* g1 = new Group();
    g1->setParent(root);
    Uuid g1Uuid = Uuid::random();
    g1->setUuid(g1Uuid);
    Entry* e1 = new Entry();
    e1->setGroup(g1);
    Uuid e1Uuid = Uuid::random();
    e1->setUuid(e1Uuid);
    Group* g2 = new Group();
    g2->setParent(g1);
    Uuid g2Uuid = Uuid::random();
    g2->setUuid(g2Uuid);
    Entry* e2 = new Entry();
    e2->setGroup(g2);
    Uuid e2Uuid = Uuid::random();
    e2->setUuid(e2Uuid);

    delete g1;
    delObjectsSize += 4;

    QCOMPARE(db->deletedObjects().size(), delObjectsSize);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-4).uuid, e1Uuid);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-3).uuid, e2Uuid);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-2).uuid, g2Uuid);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-1).uuid, g1Uuid);
    QCOMPARE(rootChildrenCount, root->children().size());

    Entry* e3 = new Entry();
    e3->setGroup(root);
    Uuid e3Uuid = Uuid::random();
    e3->setUuid(e3Uuid);

    delete e3;

    QCOMPARE(db->deletedObjects().size(), ++delObjectsSize);
    QCOMPARE(db->deletedObjects().at(delObjectsSize-1).uuid, e3Uuid);
    QCOMPARE(rootChildrenCount, root->children().size());
}