bool QgsAuthOAuth2Method::updateNetworkRequest( QNetworkRequest &request, const QString &authcfg,
    const QString &dataprovider )
{
  Q_UNUSED( dataprovider )

  QMutexLocker locker( &mNetworkRequestMutex );

  QString msg;

  QgsO2 *o2 = getOAuth2Bundle( authcfg );
  if ( !o2 )
  {
    msg = QStringLiteral( "Update request FAILED for authcfg %1: null object for requestor" ).arg( authcfg );
    QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Warning );
    return false;
  }

  if ( o2->linked() )
  {
    // Check if the cache file has been deleted outside core method routines
    QString tokencache = QgsAuthOAuth2Config::tokenCachePath( authcfg, !o2->oauth2config()->persistToken() );
    if ( !QFile::exists( tokencache ) )
    {
      msg = QStringLiteral( "Token cache removed for authcfg %1: unlinking authenticator" ).arg( authcfg );
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Info );
      o2->unlink();
    }
  }

  if ( o2->linked() )
  {
    // First, check if it is expired
    bool expired = false;
    if ( o2->expires() > 0 )  // QStringLiteral("").toInt() result for tokens with no expiration
    {
      int cursecs = static_cast<int>( QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000 );
      expired = ( ( o2->expires() - cursecs ) < 120 ); // try refresh with expired or two minutes to go
    }

    if ( expired )
    {
      msg = QStringLiteral( "Token expired, attempting refresh for authcfg %1" ).arg( authcfg );
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Info );

      // Try to get a refresh token first
      // go into local event loop and wait for a fired refresh-related slot
      QEventLoop rloop( nullptr );
      connect( o2, &QgsO2::refreshFinished, &rloop, &QEventLoop::quit );

      // Asynchronously attempt the refresh
      // TODO: This already has a timed reply setup in O2 base class (and in QgsNetworkAccessManager!)
      //       May need to address this or app crashes will occur!
      o2->refresh();

      // block request update until asynchronous linking loop is quit
      rloop.exec( QEventLoop::ExcludeUserInputEvents );

      // refresh result should set o2 to (un)linked
    }
  }

  if ( !o2->linked() )
  {
    // link app
    // clear any previous token session properties
    o2->unlink();

    connect( o2, &QgsO2::linkedChanged, this, &QgsAuthOAuth2Method::onLinkedChanged, Qt::UniqueConnection );
    connect( o2, &QgsO2::linkingFailed, this, &QgsAuthOAuth2Method::onLinkingFailed, Qt::UniqueConnection );
    connect( o2, &QgsO2::linkingSucceeded, this, &QgsAuthOAuth2Method::onLinkingSucceeded, Qt::UniqueConnection );
    connect( o2, &QgsO2::openBrowser, this, &QgsAuthOAuth2Method::onOpenBrowser, Qt::UniqueConnection );
    connect( o2, &QgsO2::closeBrowser, this, &QgsAuthOAuth2Method::onCloseBrowser, Qt::UniqueConnection );
    connect( o2, &QgsO2::getAuthCode, this, &QgsAuthOAuth2Method::onAuthCode, Qt::UniqueConnection );
    connect( this, &QgsAuthOAuth2Method::setAuthCode, o2,  &QgsO2::onSetAuthCode, Qt::UniqueConnection );
    //qRegisterMetaType<QNetworkReply::NetworkError>( QStringLiteral( "QNetworkReply::NetworkError" )) // for Qt::QueuedConnection, if needed;
    connect( o2, &QgsO2::refreshFinished, this, &QgsAuthOAuth2Method::onRefreshFinished, Qt::UniqueConnection );


    QgsSettings settings;
    QString timeoutkey = QStringLiteral( "qgis/networkAndProxy/networkTimeout" );
    int prevtimeout = settings.value( timeoutkey, QStringLiteral( "-1" ) ).toInt();
    int reqtimeout = o2->oauth2config()->requestTimeout() * 1000;
    settings.setValue( timeoutkey, reqtimeout );

    // go into local event loop and wait for a fired linking-related slot
    QEventLoop loop( nullptr );
    connect( o2, &QgsO2::linkingFailed, &loop, &QEventLoop::quit );
    connect( o2, &QgsO2::linkingSucceeded, &loop, &QEventLoop::quit );

    // add singlshot timer to quit linking after an alloted timeout
    // this should keep the local event loop from blocking forever
    QTimer timer( nullptr );
    timer.setInterval( reqtimeout * 5 );
    timer.setSingleShot( true );
    connect( &timer, &QTimer::timeout, o2, &QgsO2::linkingFailed );
    timer.start();

    // asynchronously attempt the linking
    o2->link();

    // block request update until asynchronous linking loop is quit
    loop.exec();
    if ( timer.isActive() )
    {
      timer.stop();
    }

    // don't re-apply a setting that wasn't already set
    if ( prevtimeout == -1 )
    {
      settings.remove( timeoutkey );
    }
    else
    {
      settings.setValue( timeoutkey, prevtimeout );
    }

    if ( !o2->linked() )
    {
      msg = QStringLiteral( "Update request FAILED for authcfg %1: requestor could not link app" ).arg( authcfg );
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Warning );
      return false;
    }
  }

  if ( o2->token().isEmpty() )
  {
    msg = QStringLiteral( "Update request FAILED for authcfg %1: access token is empty" ).arg( authcfg );
    QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Warning );
    return false;
  }

  // update the request
  QgsAuthOAuth2Config::AccessMethod accessmethod = o2->oauth2config()->accessMethod();

  QUrl url = request.url();
  QUrlQuery query( url );

  switch ( accessmethod )
  {
    case QgsAuthOAuth2Config::Header:
      request.setRawHeader( O2_HTTP_AUTHORIZATION_HEADER, QStringLiteral( "Bearer %1" ).arg( o2->token() ).toAscii() );
      msg = QStringLiteral( "Updated request HEADER with access token for authcfg: %1" ).arg( authcfg );
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Info );
      break;
    case QgsAuthOAuth2Config::Form:
      // FIXME: what to do here if the parent request is not POST?
      //        probably have to skip this until auth system support is moved into QgsNetworkAccessManager
      msg = QStringLiteral( "Update request FAILED for authcfg %1: form POST token update is unsupported" ).arg( authcfg );
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Warning );
      break;
    case QgsAuthOAuth2Config::Query:
      if ( !query.hasQueryItem( O2_OAUTH2_ACCESS_TOKEN ) )
      {
        query.addQueryItem( O2_OAUTH2_ACCESS_TOKEN, o2->token() );
        url.setQuery( query );
        request.setUrl( url );
        msg = QStringLiteral( "Updated request QUERY with access token for authcfg: %1" ).arg( authcfg );
      }
      else
      {
        msg = QStringLiteral( "Updated request QUERY with access token SKIPPED (existing token) for authcfg: %1" ).arg( authcfg );
      }
      QgsMessageLog::logMessage( msg, AUTH_METHOD_KEY, Qgis::MessageLevel::Info );
      break;
  }

  return true;
}