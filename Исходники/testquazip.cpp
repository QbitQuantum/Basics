void TestQuaZip::getFileList()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    qSort(fileNames);
    QDir curDir;
    if (curDir.exists(zipName)) {
        if (!curDir.remove(zipName))
            QFAIL("Can't remove zip file");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("Can't create test file");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("Can't create test archive");
    }
    QuaZip testZip(zipName);
    QVERIFY(testZip.open(QuaZip::mdUnzip));
    QVERIFY(testZip.goToFirstFile());
    QString firstFile = testZip.getCurrentFileName();
    QStringList fileList = testZip.getFileNameList();
    qSort(fileList);
    QCOMPARE(fileList, fileNames);
    QHash<QString, QFileInfo> srcInfo;
    foreach (QString fileName, fileNames) {
        srcInfo[fileName] = QFileInfo("tmp/" + fileName);
    }