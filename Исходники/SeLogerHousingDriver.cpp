bool SeLogerHousingDriver::parseSearchRequestData( const QByteArray& data, Announcement::List& announcements, RequestResultProperties* properties ) const
{
    // before parsing the announce, we convert the xml to a standard simple one using xquery
    const QString xpath = xPathQuery();
    QXmlQuery query;
    QString xml;
    
    if ( !query.setFocus( QString::fromUtf8( data ) ) ) {
        if ( properties ) {
            properties->error = tr( "%s: Can't set focus" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 1", Q_FUNC_INFO );
        return false;
    }

    query.setQuery( xpath, QUrl( d->webServiceUrl() ) );
    
    if ( !query.isValid() ) {
        if ( properties ) {
            properties->error = tr( "%s: Invalid query" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 2", Q_FUNC_INFO );
        return false;
    }
    
    if ( !query.evaluateTo( &xml ) ) {
        if ( properties ) {
            properties->error = tr( "%s: Can't evaluateTo" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 3", Q_FUNC_INFO );
        return false;
    }
    
    return parseStandardDomDocument( xml, announcements, properties );
}