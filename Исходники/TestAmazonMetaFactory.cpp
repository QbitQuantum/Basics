void
TestAmazonMetaFactory::testCreateTrack()
{
    QStringList list, list2;
    list << "id" << "name" << "trackNumber" << "length" << "playableUrl" << "albumId" << "artistId" << "price" << "ASIN";
    list2 << "23" << "name" << "5" << "300" << "http://www.amazon.de/gp/dmusic/get_sample_url.html?ASIN=B007NV28OK" << "42" << "12" << "99" << "B007NV28OK";

    AmazonMetaFactory factory( "Amazontest" );
    Meta::TrackPtr trackPtr = factory.createTrack( list );
    Meta::TrackPtr trackPtr2 = factory.createTrack( list2 );

    QVERIFY( trackPtr );
    QVERIFY( trackPtr2 );

    Meta::AmazonTrack* amazonTrack = dynamic_cast<Meta::AmazonTrack*>( trackPtr.data() );
    Meta::AmazonTrack* amazonTrack2 = dynamic_cast<Meta::AmazonTrack*>( trackPtr2.data() );

    QVERIFY( amazonTrack );
    QVERIFY( amazonTrack2 );

    QCOMPARE( amazonTrack->id(), 0 );
    QCOMPARE( amazonTrack->name(), QString( "name" ) );
    QCOMPARE( amazonTrack->trackNumber(), 0 );
    QCOMPARE( amazonTrack->length(), (qint64)0 );
    QCOMPARE( amazonTrack->playableUrl(), KUrl( "playableUrl" ) );
    QCOMPARE( amazonTrack->albumId(), 0 );
    QCOMPARE( amazonTrack->artistId(), 0 );
    QCOMPARE( amazonTrack->price(), QString( "price" ) );
    QCOMPARE( amazonTrack->asin(), QString( "ASIN" ) );

    QCOMPARE( amazonTrack2->id(), 23 );
    QCOMPARE( amazonTrack2->trackNumber(), 5 );
    QCOMPARE( amazonTrack2->length(), (qint64)300 );
    QCOMPARE( amazonTrack2->playableUrl(), KUrl( "http://www.amazon.de/gp/dmusic/get_sample_url.html?ASIN=B007NV28OK" ) );
    QCOMPARE( amazonTrack2->albumId(), 42 );
    QCOMPARE( amazonTrack2->artistId(), 12 );
    QCOMPARE( amazonTrack2->price(), QString( "99" ) );
    QCOMPARE( amazonTrack2->asin(), QString( "B007NV28OK" ) );
}