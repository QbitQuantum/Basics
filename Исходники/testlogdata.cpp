void TestLogData::changingFile()
{
    char newLine[90];
    LogData logData;

    QSignalSpy finishedSpy( &logData, SIGNAL( loadingFinished( bool ) ) );
    QSignalSpy progressSpy( &logData, SIGNAL( loadingProgressed( int ) ) );
    QSignalSpy changedSpy( &logData,
                           SIGNAL( fileChanged( LogData::MonitoredFileStatus ) ) );

    // Register for notification file is loaded
    connect( &logData, SIGNAL( loadingFinished( bool ) ),
             this, SLOT( loadingFinished() ) );

    // Generate a small file
    QFile file( TMPDIR "/changingfile.txt" );
    if ( file.open( QIODevice::WriteOnly ) ) {
        for (int i = 0; i < 200; i++) {
            snprintf(newLine, 89, sl_format, i);
            file.write( newLine, qstrlen(newLine) );
        }
    }
    file.close();

    // Start loading it
    logData.attachFile( TMPDIR "/changingfile.txt" );

    // and wait for the signal
    QApplication::exec();

    // Check we have the small file
    QCOMPARE( finishedSpy.count(), 1 );
    QCOMPARE( logData.getNbLine(), 200LL );
    QCOMPARE( logData.getMaxLength(), SL_LINE_LENGTH );
    QCOMPARE( logData.getFileSize(), 200 * (SL_LINE_LENGTH+1LL) );

    // Add some data to it
    if ( file.open( QIODevice::Append ) ) {
        for (int i = 0; i < 200; i++) {
            snprintf(newLine, 89, sl_format, i);
            file.write( newLine, qstrlen(newLine) );
        }
        // To test the edge case when the final line is not complete
        file.write( partial_line_begin, qstrlen( partial_line_begin ) );
    }
    file.close();

    // and wait for the signals
    QApplication::exec();

    // Check we have a bigger file
    QCOMPARE( changedSpy.count(), 1 );
    QCOMPARE( finishedSpy.count(), 2 );
    QCOMPARE( logData.getNbLine(), 401LL );
    QCOMPARE( logData.getMaxLength(), SL_LINE_LENGTH );
    QCOMPARE( logData.getFileSize(), (qint64) (400 * (SL_LINE_LENGTH+1LL)
              + strlen( partial_line_begin ) ) );

    // Add a couple more lines, including the end of the unfinished one.
    if ( file.open( QIODevice::Append ) ) {
        file.write( partial_line_end, qstrlen( partial_line_end ) );
        for (int i = 0; i < 20; i++) {
            snprintf(newLine, 89, sl_format, i);
            file.write( newLine, qstrlen(newLine) );
        }
    }
    file.close();

    // and wait for the signals
    QApplication::exec();

    // Check we have a bigger file
    QCOMPARE( changedSpy.count(), 2 );
    QCOMPARE( finishedSpy.count(), 3 );
    QCOMPARE( logData.getNbLine(), 421LL );
    QCOMPARE( logData.getMaxLength(), SL_LINE_LENGTH );
    QCOMPARE( logData.getFileSize(), (qint64) ( 420 * (SL_LINE_LENGTH+1LL)
              + strlen( partial_line_begin ) + strlen( partial_line_end ) ) );

    // Truncate the file
    QVERIFY( file.open( QIODevice::WriteOnly ) );
    file.close();

    // and wait for the signals
    QApplication::exec();

    // Check we have an empty file
    QCOMPARE( changedSpy.count(), 3 );
    QCOMPARE( finishedSpy.count(), 4 );
    QCOMPARE( logData.getNbLine(), 0LL );
    QCOMPARE( logData.getMaxLength(), 0 );
    QCOMPARE( logData.getFileSize(), 0LL );
}