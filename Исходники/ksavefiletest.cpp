void KSaveFileTest::test_ksavefile()
{
    QString targetFile;

    {
        //This will be the file we eventually write to. Yes, I know you
        //should never remove the temporaryfile and then expect the filename
        //to continue to be unique, but this is a test for crying out loud. :)
        KTemporaryFile file;
        file.setPrefix("ksavefiletest");
        QVERIFY( file.open() );
        targetFile = file.fileName();
    }

    {
        //Test basic functionality
        KSaveFile saveFile;
        saveFile.setFileName(targetFile);
        QVERIFY( saveFile.open() );
        QVERIFY( !QFile::exists(targetFile) );

        QTextStream ts ( &saveFile );
        ts << "This is test data one.\n";
        ts.flush();
        QCOMPARE( saveFile.error(), QFile::NoError );
        QVERIFY( !QFile::exists(targetFile) );

        QVERIFY( saveFile.finalize() );
        QVERIFY( QFile::exists(targetFile) );

        QFile::remove(targetFile);
        QVERIFY( !QFile::exists(targetFile) );
    }

    {
        //Make sure destructor does what it is supposed to do.
        {
            KSaveFile saveFile;
            saveFile.setFileName(targetFile);
            QVERIFY( saveFile.open() );
            QVERIFY( !QFile::exists(targetFile) );
        }

        QVERIFY( QFile::exists(targetFile) );
        QFile::remove(targetFile);
        QVERIFY( !QFile::exists(targetFile) );
    }

    {
        //Test some error conditions
        KSaveFile saveFile;
        QVERIFY( !saveFile.open() ); //no filename
        saveFile.setFileName(targetFile);
        QVERIFY( saveFile.open() );
        QVERIFY( !QFile::exists(targetFile) );
        QVERIFY( !saveFile.open() ); //already open

        QVERIFY( saveFile.finalize() );
        QVERIFY( QFile::exists(targetFile) );
        QVERIFY( !saveFile.finalize() ); //already finalized

        QFile::remove(targetFile);
        QVERIFY( !QFile::exists(targetFile) );
    }

    {
        //Do it again, aborting this time
        KSaveFile saveFile ( targetFile );
        QVERIFY( saveFile.open() );
        QVERIFY( !QFile::exists(targetFile) );

        QTextStream ts ( &saveFile );
        ts << "This is test data two.\n";
        ts.flush();
        QCOMPARE( saveFile.error(), QFile::NoError );
        QVERIFY( !QFile::exists(targetFile) );

        saveFile.abort();
        QVERIFY( !QFile::exists(targetFile) );
    }

    QFile file ( targetFile );
    QVERIFY( file.open(QIODevice::WriteOnly | QIODevice::Text) );
    QVERIFY( file.setPermissions( file.permissions() | QFile::ExeUser ) );
    file.close();

    {
        //Test how it works when the file already exists
        //Also check for special permissions
        KSaveFile saveFile ( targetFile );
        QVERIFY( saveFile.open() );

        QVERIFY( QFile::exists(targetFile) );
        QFileInfo fi ( targetFile );

#ifndef Q_WS_WIN
        // Windows: qt_ntfs_permission_lookup is not set by default in
        // qfsfileengine_win.cpp, could change in future Qt versions.
        QVERIFY( fi.permission( QFile::ExeUser ) );
#endif
        QVERIFY( fi.size() == 0 );

        QTextStream ts ( &saveFile );
        ts << "This is test data three.\n";
        ts.flush();

        fi.refresh();
        QVERIFY( fi.size() == 0 );
        QVERIFY( saveFile.finalize() );

        fi.refresh();
        QVERIFY( fi.size() != 0 );
#ifndef Q_WS_WIN
        QVERIFY( fi.permission( QFile::ExeUser ) );
#endif

        QFile::remove(targetFile);
    }

    {
        QFileInfo fi ( targetFile );
        targetFile = fi.fileName();
        QDir::setCurrent(fi.path());

        //one more time, this time with relative filenames
        KSaveFile saveFile ( targetFile );
        QVERIFY( saveFile.open() );
        QVERIFY( !QFile::exists(targetFile) );

        QTextStream ts ( &saveFile );
        ts << "This is test data four.\n";
        ts.flush();
        QCOMPARE( saveFile.error(), QFile::NoError );
        QVERIFY( !QFile::exists(targetFile) );

        QVERIFY( saveFile.finalize() );
        QVERIFY( QFile::exists(targetFile) );
        QFile::remove(targetFile);
    }

}