void TestTracklistController::tstVersion()
{
    QSharedPointer<TracklistController> controller = client.tracklistController();
    QSignalSpy spy(controller.data(), &TracklistController::versionReceived);

    controller->getVersion();
    QVERIFY(spy.wait(500));
}