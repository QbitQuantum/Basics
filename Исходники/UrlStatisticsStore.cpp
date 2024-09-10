UrlStatisticsStore::UrlStatisticsStore( Meta::Track *track, const QString &permanentUrl )
    : PersistentStatisticsStore( track )
    , m_permanentUrl( permanentUrl )
{
    if( m_permanentUrl.isEmpty() )
        m_permanentUrl = track->uidUrl();
    SqlStorage *sql = CollectionManager::instance()->sqlStorage();
    if( !sql )
    {
        warning() << __PRETTY_FUNCTION__ << "could not get SqlStorage, aborting";
        return;
    }


    const QString query = "SELECT firstplayed, lastplayed, score, rating, playcount FROM "
                          "statistics_permanent WHERE url = '%1'";
    QStringList result = sql->query( query.arg( sql->escape( m_permanentUrl ) ) );
    if( !result.isEmpty() )
    {
        m_firstPlayed = QDateTime::fromString( result.value( 0 ), s_sqlDateFormat );
        m_lastPlayed = QDateTime::fromString( result.value( 1 ), s_sqlDateFormat );
        m_score = result.value( 2 ).toDouble();
        m_rating = result.value( 3 ).toInt();
        m_playCount = result.value( 4 ).toInt();
    }
}