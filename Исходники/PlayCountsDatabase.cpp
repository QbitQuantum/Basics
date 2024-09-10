void
PlayCountsDatabase::beginTransaction()
{
    // we try until blue in the face to begin the transaction, as we really,
    // really want db lock
    
    QSqlQuery q( m_db );
    q.exec( "BEGIN TRANSACTION" );
            
    for (int i = 5; q.lastError().type() == QSqlError::ConnectionError && i; i--)
    {
        // we only try 5 times since SQLITE_BUSY is just one of the
        // possible things that ConnectionError might mean
        LOGL( 3, "SQLite might be busy trying again in 25ms..." );
        UnicornUtils::msleep( 25 );

        q.exec();
    }
}