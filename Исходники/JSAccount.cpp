QString
JSAccount::serializeQVariantMap( const QVariantMap& map )
{
    QVariantMap localMap = map;

    foreach( const QString& key, localMap.keys() )
    {
        QVariant currentVariant = localMap[ key ];

        // strip unserializable types - at least QJson needs this, check with QtJson
        if( currentVariant.canConvert<QImage>() )
        {
            localMap.remove( key );
        }
    }

    QByteArray serialized = TomahawkUtils::toJson( localMap );

    return QString( "JSON.parse('%1')" ).arg( JSAccount::escape( QString::fromUtf8( serialized ) ) );
}