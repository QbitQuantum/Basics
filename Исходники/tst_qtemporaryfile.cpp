void tst_QTemporaryFile::removeAndReOpen()
{
    QString fileName;
    {
        QTemporaryFile file;
        file.open();
        fileName = file.fileName();
        QVERIFY(QFile::exists(fileName));

        file.remove();
        QVERIFY(!QFile::exists(fileName));

        QVERIFY(file.open());
        QCOMPARE(QFileInfo(file.fileName()).path(), QFileInfo(fileName).path());
        fileName = file.fileName();
        QVERIFY(QFile::exists(fileName));
    }
    QVERIFY(!QFile::exists(fileName));
}