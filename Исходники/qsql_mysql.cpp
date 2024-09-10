bool QMYSQLDriver::rollbackTransaction()
{
#ifndef CLIENT_TRANSACTIONS
    return FALSE;
#endif
    if ( !isOpen() ) {
#ifdef QT_CHECK_RANGE
	qWarning( "QMYSQLDriver::rollbackTransaction: Database not open" );
#endif
	return FALSE;
    }
    if ( mysql_query( d->mysql, "ROLLBACK" ) ) {
	setLastError( qMakeError("Unable to rollback transaction", QSqlError::Statement, d ) );
	return FALSE;
    }
    return TRUE;
}