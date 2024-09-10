/*
   Execute \a query.
*/
bool QSQLite2Result::reset (const QString& query)
{
    // this is where we build a query.
    if (!driver())
        return false;
    if (!driver()-> isOpen() || driver()->isOpenError())
        return false;

    d->cleanup();

    // Um, ok.  callback based so.... pass private static function for this.
    setSelect(false);
    char *err = 0;
    int res = sqlite_compile(d->access,
                                d->utf8 ? query.toUtf8().constData()
                                        : query.toAscii().constData(),
                                &(d->currentTail),
                                &(d->currentMachine),
                                &err);
    if (res != SQLITE_OK || err) {
        setLastError(QSqlError(QCoreApplication::translate("QSQLite2Result",
                     "Unable to execute statement"), QString::fromAscii(err),
                     QSqlError::StatementError, res));
        sqlite_freemem(err);
    }
    //if (*d->currentTail != '\000' then there is more sql to eval
    if (!d->currentMachine) {
        setActive(false);
        return false;
    }
    // we have to fetch one row to find out about
    // the structure of the result set
    d->skippedStatus = d->fetchNext(d->firstRow, 0, true);
    if (lastError().isValid()) {
        setSelect(false);
        setActive(false);
        return false;
    }
    setSelect(!d->rInf.isEmpty());
    setActive(true);
    return true;
}