void TestQgsOgrProvider::setupProxy()
{

  QgsSettings settings;
  {
    settings.setValue( QStringLiteral( "proxy/proxyEnabled" ), true );
    settings.setValue( QStringLiteral( "proxy/proxyPort" ), QStringLiteral( "1234" ) );
    settings.setValue( QStringLiteral( "proxy/proxyHost" ), QStringLiteral( "myproxyhostname.com" ) );
    settings.setValue( QStringLiteral( "proxy/proxyUser" ), QStringLiteral( "username" ) );
    settings.setValue( QStringLiteral( "proxy/proxyPassword" ), QStringLiteral( "password" ) );
    settings.setValue( QStringLiteral( "proxy/proxyExcludedUrls" ), QStringLiteral( "http://www.myhost.com|http://www.myotherhost.com" ) );
    QgsNetworkAccessManager::instance()->setupDefaultProxyAndCache();
    QgsVectorLayer vl( mTestDataDir + '/' + QStringLiteral( "lines.shp" ), QStringLiteral( "proxy_test" ), QLatin1Literal( "ogr" ) );
    QVERIFY( vl.isValid() );
    const char *proxyConfig = CPLGetConfigOption( "GDAL_HTTP_PROXY", nullptr );
    QCOMPARE( proxyConfig, "myproxyhostname.com:1234" );
    const char *proxyCredentials = CPLGetConfigOption( "GDAL_HTTP_PROXYUSERPWD", nullptr );
    QCOMPARE( proxyCredentials, "username:password" );
  }

  {
    // Test partial config
    settings.setValue( QStringLiteral( "proxy/proxyEnabled" ), true );
    settings.remove( QStringLiteral( "proxy/proxyPort" ) );
    settings.setValue( QStringLiteral( "proxy/proxyHost" ), QStringLiteral( "myproxyhostname.com" ) );
    settings.setValue( QStringLiteral( "proxy/proxyUser" ), QStringLiteral( "username" ) );
    settings.remove( QStringLiteral( "proxy/proxyPassword" ) );
    QgsNetworkAccessManager::instance()->setupDefaultProxyAndCache();
    QgsVectorLayer vl( mTestDataDir + '/' + QStringLiteral( "lines.shp" ), QStringLiteral( "proxy_test" ), QLatin1Literal( "ogr" ) );
    QVERIFY( vl.isValid() );
    const char *proxyConfig = CPLGetConfigOption( "GDAL_HTTP_PROXY", nullptr );
    QCOMPARE( proxyConfig, "myproxyhostname.com" );
    const char *proxyCredentials = CPLGetConfigOption( "GDAL_HTTP_PROXYUSERPWD", nullptr );
    QCOMPARE( proxyCredentials, "username" );
  }

}