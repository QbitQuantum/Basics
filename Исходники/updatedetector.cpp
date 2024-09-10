void UpdateDetector::versionCheck( Theme *theme )
{
    connect(_accessManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(slotVersionInfoArrived(QNetworkReply*)) );
    QUrl url(QLatin1String("https://download.owncloud.com/clientupdater.php"));
    QString ver = QString::fromLatin1("%1.%2.%3").arg(MIRALL_VERSION_MAJOR).arg(MIRALL_VERSION_MINOR).arg(MIRALL_VERSION_MICRO);

    QString platform = QLatin1String("stranger");
#ifdef Q_OS_LINUX
    platform = QLatin1String("linux");
#endif
#ifdef Q_OS_WIN32
    platform = QLatin1String( "win32" );
#endif
#ifdef Q_OS_MAC
    platform = QLatin1String( "macos" );
#endif
    qDebug() << "00 client update check to " << url.toString();

    QString sysInfo = getSystemInfo();
    if( !sysInfo.isEmpty() ) {
        url.addQueryItem(QLatin1String("client"), sysInfo );
    }
    url.addQueryItem( QLatin1String("version"), ver );
    url.addQueryItem( QLatin1String("platform"), platform );
    url.addQueryItem( QLatin1String("oem"), theme->appName() );

    QNetworkRequest req( url );
    req.setRawHeader( QByteArray("User-Agent"), Utility::userAgentString() );

    _accessManager->get( req );
}