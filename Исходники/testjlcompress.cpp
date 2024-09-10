void TestJlCompress::compressFile()
{
    QFETCH(QString, zipName);
    QFETCH(QString, fileName);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(QStringList() << fileName)) {
        QFAIL("Can't create test file");
    }
    QVERIFY(JlCompress::compressFile(zipName, "tmp/" + fileName));
    // get the file list and check it
    QStringList fileList = JlCompress::getFileList(zipName);
    QCOMPARE(fileList.count(), 1);
    QVERIFY(fileList[0] == fileName);
    // now test the QIODevice* overload of getFileList()
    QFile zipFile(zipName);
    QVERIFY(zipFile.open(QIODevice::ReadOnly));
    fileList = JlCompress::getFileList(zipName);
    QCOMPARE(fileList.count(), 1);
    QVERIFY(fileList[0] == fileName);
    zipFile.close();
    removeTestFiles(QStringList() << fileName);
    curDir.remove(zipName);
}