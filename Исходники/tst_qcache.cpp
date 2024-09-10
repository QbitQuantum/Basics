void tst_QCache::contains()
{
    QCache<int, int> cache;
    QVERIFY(!cache.contains(0));
    QVERIFY(!cache.contains(1));

    cache.insert(1, new int(1), 1);
    QVERIFY(!cache.contains(0));
    QVERIFY(cache.contains(1));

    cache.remove(0);
    cache.remove(1);
    QVERIFY(!cache.contains(0));
    QVERIFY(!cache.contains(1));

    cache.insert(1, new int(1), 1);
    QVERIFY(!cache.contains(0));
    QVERIFY(cache.contains(1));

    cache.clear();
    QVERIFY(!cache.contains(0));
    QVERIFY(!cache.contains(1));
}