Meta::TrackPtr
ServiceSqlCollection::trackForUrl(const KUrl & url)
{
    if ( !possiblyContainsTrack( url ) ) //do we even bother trying?
        return Meta::TrackPtr();

    //split out the parts we can be sure about ( strip username and such info )
    QString trackRows = m_metaFactory->getTrackSqlRows() + ',' + m_metaFactory->getAlbumSqlRows() + ',' +  m_metaFactory->getArtistSqlRows() + ',' +  m_metaFactory->getGenreSqlRows();

    QString prefix = m_metaFactory->tablePrefix();

    QString pristineUrl = url.url();

    SqlStorage *sqlDb = CollectionManager::instance()->sqlStorage();

    QString from =  prefix + "_tracks";
    from += " LEFT JOIN " + prefix + "_albums ON " + prefix + "_tracks.album_id = " + prefix + "_albums.id";
    from += " LEFT JOIN " + prefix + "_artists ON " + prefix + "_albums.artist_id = " + prefix + "_artists.id";
    from += " LEFT JOIN " + prefix + "_genre ON " + prefix + "_genre.album_id = " + prefix + "_albums.id";

    QString queryString = QString( "select DISTINCT %1 FROM %2 WHERE %3_tracks.preview_url = '%4' GROUP BY %5_tracks.id;" )
            .arg( trackRows)
            .arg( from )
            .arg( prefix )
            .arg( sqlDb->escape( pristineUrl ) )
            .arg( prefix );

    //debug() << "Querying for track: " << queryString;
    QStringList result = sqlDb->query( queryString );
    //debug() << "result: " << result;

    return m_registry->getTrack( result );
}