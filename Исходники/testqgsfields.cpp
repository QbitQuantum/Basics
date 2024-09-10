void TestQgsFields::remove()
{
    QgsFields fields;

    //test for no crash
    fields.remove( 1 );

    QgsField field( "testfield" );
    fields.append( field );
    QgsField field2( "testfield2" );
    fields.append( field2 );

    //test for no crash
    fields.remove( -1 );
    fields.remove( 5 );

    //remove valid field
    fields.remove( 0 );
    QCOMPARE( fields.count(), 1 );
    QCOMPARE( fields.at( 0 ).name(), QString( "testfield2" ) );
    QCOMPARE( fields.indexFromName( "testfield2" ), 0 );
}