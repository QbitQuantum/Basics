inline QString
albumCacheKey( const Tomahawk::artist_ptr& artist, const QString& albumName )
{
    return QString( "%1\t\t%2" ).arg( artist->name().toLower() ).arg( albumName.toLower() );
}