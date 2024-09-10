bool
SqlPlaylist::saveToDb( bool tracks )
{
    int parentId = -1;
    if( m_parent )
        parentId = m_parent->id();

    SqlStorage *sql = CollectionManager::instance()->sqlStorage();

    //figure out if we have a urlId and if this id is already in the db, if so, update it instead of creating a new one.
    if( !m_urlId.isEmpty() )
    {
        debug() << "Checking " << m_urlId << " against db";

        //check if urlId exists
        QString query = "SELECT id from playlists WHERE urlid='%1'";
        query = query.arg( sql->escape( m_urlId ) );
        QStringList result = sql->query( query );

        if( !result.isEmpty() )
        {
            //set this id to the already existing one
            m_dbId =  result.at( 0 ).toInt();
            debug() << "Got existing playlist with id " << m_dbId;
        }
    }

    if( m_dbId != -1 )
    {
        //update existing
        QString query = "UPDATE playlists SET parent_id=%1, name='%2', description='%3' WHERE id=%4;";
        query = query.arg( QString::number( parentId ) )
                .arg( sql->escape( m_name ) )
                .arg( sql->escape( m_description ) )
                .arg( QString::number( m_dbId ) );
        CollectionManager::instance()->sqlStorage()->query( query );

        if( tracks )
        {
            //delete existing tracks and insert all
            query = "DELETE FROM playlist_tracks where playlist_id=%1;";
            query = query.arg( QString::number( m_dbId ) );
            CollectionManager::instance()->sqlStorage()->query( query );
            saveTracks();
        }
    }
    else
    {
        //insert new
        QString query = "INSERT INTO playlists ( parent_id, name, description, urlid ) "
                        "VALUES ( %1, '%2', '%3', '%4' );";
        query = query.arg( QString::number( parentId ) )
                .arg( sql->escape( m_name ) )
                .arg( sql->escape( m_description ) )
                .arg( sql->escape( m_urlId ) );
        m_dbId = CollectionManager::instance()->sqlStorage()->insert( query, "playlists" );
        if( tracks )
            saveTracks();
    }

    //HACK! if this has just been added from the collection scanner, the list is full of "dirty"
    //tracks that might not all have been properly trackForUrl'ed, so clear the track list so we
    //reload if we ever need them!
    if( !m_urlId.isEmpty() )
    {
        m_tracks.clear();
        m_tracksLoaded = false;
    }

    //clean the cache
    if( m_parent )
        m_parent->clear();

    return true;
}