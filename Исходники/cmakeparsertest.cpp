void CMakeParserTest::testLexerWithFile()
{
    QTemporaryFile tempFile;
    tempFile.setAutoRemove( false );
    tempFile.open();
    if ( !QFile::exists( tempFile.fileName() ) )
         QFAIL( "Unable to open temporary file" );

    QString tempName = tempFile.fileName();
    tempFile.close(); //hacks to the get name of the file

    cmListFileLexer* lexer = cmListFileLexer_New();
    if ( !lexer )
        QFAIL( "unable to create lexer" );
    QVERIFY( cmListFileLexer_SetFileName( lexer, qPrintable( tempName ) ) );
    cmListFileLexer_Delete( lexer );
    tempFile.remove();
}