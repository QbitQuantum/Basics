void classISQL::ExecSQL()
{
    SQLHSTMT    hStmt;
    QString     qsHorizSep;
    SQLLEN      nRowsAffected;
    SWORD       nColumns;
    int         iRC                 = 0;
/* TIM - return error messages if provided */
    char    szState[10];
    char    szBuf[700];
    char    szErrString[800];
    SQLRETURN retcode;

    // CREATE A STATEMENT
    iRC = SQLAllocStmt( hDbc, &hStmt );
    if ( SQL_SUCCESS != iRC )
        QMessageBox::critical( (QWidget *)this, "Data Manager", "Failed: SQLAllocStmt " );

    if ( SQL_SUCCESS != (iRC=SQLPrepare(hStmt, (SQLCHAR*)(txtSQL->text().data()), SQL_NTS)) )
    {
        retcode = SQLError(SQL_NULL_HENV, hDbc, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)szBuf, 700, NULL);
        if ( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
            QMessageBox::critical( (QWidget *)this, "Data Manager", szBuf);
        else
            QMessageBox::critical( (QWidget *)this, "Data Manager", "Failed: SQLPrepare " );
    }

    // EXECUTE
    iRC = SQLExecute( hStmt );
    if ( iRC != SQL_SUCCESS )
    {
        retcode = SQLError( 0, 0, hStmt, (SQLCHAR*)szState, NULL, (SQLCHAR*)szBuf, 700, NULL);
        if ( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
            QMessageBox::critical( (QWidget *)this, "Data Manager", szBuf);
        else
            QMessageBox::critical( (QWidget *)this, "Data Manager", "Failed: SQLExecute " );
    }

    if ( iRC != SQL_SUCCESS && iRC != SQL_SUCCESS_WITH_INFO )
        return;

    // UPDATE HISTORY
    appendHistoryItem();

    // GET NUMBER OF ROWS AFFECTED
// Wait until we know the exact number. SQLRowCount is not supported by all drivers and should not
// be used.
//    nRowsAffected = -1;
//    if ( (iRC = SQLRowCount( hStmt, &nRowsAffected )) != SQL_SUCCESS )
//        nRowsAffected = -1;

    // GET NUMBER OF COLUMNS RETURNED
    if ( (iRC = SQLNumResultCols( hStmt, &nColumns )) != SQL_SUCCESS )
        nColumns = -1;

    txtResults->setAutoUpdate( FALSE );
    txtResults->clear();

    // GET A RESULTS HEADER (column headers)
    getResultsHeader( hStmt, nColumns, &qsHorizSep );
    // GET A RESULTS BODY (data)
    nRowsAffected = getResultsBody( hStmt, nColumns );

    // FREE STATEMENT
    iRC = SQLFreeStmt( hStmt, SQL_DROP );
    if ( SQL_SUCCESS != iRC )
        QMessageBox::critical( (QWidget *)this, "Data Manager", "Failed: SQLFreeStmt " );

    pTabBar->setCurrentTab( 1 );
    txtResults->show();
    txtSQL->hide();

    txtResults->append( qsHorizSep );
    qsHorizSep.sprintf( "\n\n%d rows affected", nRowsAffected );
    txtResults->append( qsHorizSep );

    txtResults->setAutoUpdate( TRUE );
    txtResults->repaint();

}