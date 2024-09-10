void tst_QSimToolkit::testDeliverEventDownload()
{
    QFETCH( QByteArray, data );
    QFETCH( QByteArray, payload );
    QFETCH( int, event );
    QFETCH( int, sourceDevice );

    // Output a dummy line to give some indication of which test we are currently running.
    qDebug() << "";

    // Clear the client/server state.
    server->clear();
    deliveredCommand = QSimCommand();

    // Compose and send the envelope.
    QSimEnvelope env;
    env.setType( QSimEnvelope::EventDownload );
    env.setSourceDevice( (QSimCommand::Device)sourceDevice );
    env.setEvent( (QSimEnvelope::Event)event );
    env.setExtensionData( payload );
    client->sendEnvelope( env );

    // Wait for the envelope to be received.
    QVERIFY( QFutureSignal::wait( server, SIGNAL(envelopeSeen()), 100 ) );

    // Check that the envelope is what we expected to get and that we didn't
    // get any terminal responses yet.
    QCOMPARE( server->responseCount(), 0 );
    QCOMPARE( server->envelopeCount(), 1 );
    QByteArray lastenv = server->lastEnvelope();
    lastenv[2] = data[2];      // Handle 0x19 vs 0x99 discrepancy.
    QCOMPARE( lastenv, data );
}