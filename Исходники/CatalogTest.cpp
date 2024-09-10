void CatalogTest::testProfile()
{
    Echonest::Catalog c( "CAWRKLJ12BF92BC7C3" );
    QNetworkReply* reply = c.profile();

    qDebug() << reply->url().toString();
    QCOMPARE( reply->url().toString(), QLatin1String( "http://developer.echonest.com/api/v4/catalog/profile?api_key=JGJCRKWLXLBZIFAZB&format=xml&id=CAWRKLJ12BF92BC7C3" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    c.parseProfile( reply );
    qDebug() << c;
    QCOMPARE( c.total(), 3 );
}