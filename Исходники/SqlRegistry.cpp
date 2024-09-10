// ------ directory
int
SqlRegistry::getDirectory( const QString &path, uint mtime )
{
    int dirId;
    int deviceId = m_collection->mountPointManager()->getIdForUrl( path );
    QString rdir = m_collection->mountPointManager()->getRelativePath( deviceId, path );

    SqlStorage *storage = m_collection->sqlStorage();

    // - find existing entry
    QString query = QString( "SELECT id, changedate FROM directories "
                             "WHERE  deviceid = %1 AND dir = '%2';" )
                        .arg( QString::number( deviceId ), storage->escape( rdir ) );
    QStringList res = storage->query( query );

    // - create new entry
    if( res.isEmpty() )
    {
        debug() << "SqlRegistry::getDirectory(): new directory" << path;
        QString insert = QString( "INSERT INTO directories(deviceid,changedate,dir) "
                                  "VALUES (%1,%2,'%3');" )
                        .arg( QString::number( deviceId ), QString::number( mtime ),
                                storage->escape( rdir ) );
        dirId = storage->insert( insert, "directories" );
        m_collectionChanged = true;
    }
    else
    {
        // update old one
        dirId = res[0].toUInt();
        uint oldMtime = res[1].toUInt();
        if( oldMtime != mtime )
        {
            QString update = QString( "UPDATE directories SET changedate = %1 "
                                      "WHERE id = %2;" )
                .arg( QString::number( mtime ), res[0] );
            debug() << "SqlRegistry::getDirectory(): update directory" << path << "(id" <<
                    res[0] << ") from" << oldMtime << "to" << mtime << "UNIX time";
            storage->query( update );
        }
    }
    return dirId;
}