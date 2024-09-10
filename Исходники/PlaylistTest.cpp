void PlaylistTest::testStatic1()
{
    DynamicPlaylist::PlaylistParams p;
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "tallest man on earth" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "bon iver" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Artist, QLatin1String( "mumford and sons" ) ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Type, Echonest::DynamicPlaylist::ArtistRadioType ) );
    p.append( DynamicPlaylist::PlaylistParamData( Echonest::DynamicPlaylist::Results, 10 ) );

    QNetworkReply* reply = DynamicPlaylist::staticPlaylist( p );

    qDebug() << reply->url().toString();
    QVERIFY( reply->url().toString() == QLatin1String( "http://developer.echonest.com/api/v4/playlist/static?api_key=JGJCRKWLXLBZIFAZB&format=xml&artist=tallest+man+on+earth&artist=bon+iver&artist=mumford+and+sons&type=artist-radio&results=10" ) );

    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    SongList songs = DynamicPlaylist::parseStaticPlaylist( reply );

    QVERIFY( songs.size() == 10 );
    Q_FOREACH( const Song& song, songs )
        QVERIFY( !song.id().isEmpty() );

}