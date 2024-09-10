void ProfileFactoryTest::testCreateFromXml()
{
    const QString NAME = "name";
    ProfileFactory pf;
    QDomDocument doc;

    {
        QString type = Profile::TYPE_CLIENT;
        Profile clientProfile(NAME, type);
        QDomElement root = clientProfile.toXml(doc);
        QScopedPointer<Profile> p(pf.createProfile(root));
        QVERIFY(p != 0);
        QCOMPARE(p->name(), NAME);
        QCOMPARE(p->type(), type);
    }

    {
        QString type = Profile::TYPE_SYNC;
        SyncProfile syncProfile(NAME);
        QDomElement root = syncProfile.toXml(doc);
        QScopedPointer<Profile> p(pf.createProfile(root));
        QVERIFY(p != 0);
        QCOMPARE(p->name(), NAME);
        QCOMPARE(p->type(), type);
        QVERIFY(dynamic_cast<SyncProfile*>(p.data()) != 0);
    }

    {
        QString type = Profile::TYPE_STORAGE;
        StorageProfile storageProfile(NAME);
        QDomElement root = storageProfile.toXml(doc);
        QScopedPointer<Profile> p(pf.createProfile(root));
        QVERIFY(p != 0);
        QCOMPARE(p->name(), NAME);
        QCOMPARE(p->type(), type);
        QVERIFY(dynamic_cast<StorageProfile*>(p.data()) != 0);
    }

}