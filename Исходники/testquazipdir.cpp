void TestQuaZipDir::entryList()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QFETCH(QString, dirName);
    QFETCH(int, filter);
    QFETCH(int, sort);
    QDir::Filters filters = static_cast<QDir::Filters>(filter);
    QDir::SortFlags sorting = static_cast<QDir::SortFlags>(sort);
    QFETCH(QStringList, entries);
    QDir curDir;
    if (!createTestFiles(fileNames)) {
        QFAIL("Couldn't create test files");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Couldn't create test archive");
    }
    removeTestFiles(fileNames);
    QuaZip zip(zipName);
    QVERIFY(zip.open(QuaZip::mdUnzip));
    QuaZipDir dir(&zip, dirName);
    QCOMPARE(dir.entryList(filters, sorting), entries);
    zip.close();
    curDir.remove(zipName);
}