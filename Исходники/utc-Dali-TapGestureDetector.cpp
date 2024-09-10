int UtcDaliTapGestureSignalReceptionDifferentPossible(void)
{
  TestApplication application;

  Actor actor = Actor::New();
  actor.SetSize(100.0f, 100.0f);
  actor.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  Stage::GetCurrent().Add(actor);

  // Render and notify
  application.SendNotification();
  application.Render();

  // Attach actor to detector
  SignalData data;
  GestureReceivedFunctor functor( data );
  TapGestureDetector detector = TapGestureDetector::New();
  detector.Attach(actor);
  detector.DetectedSignal().Connect( &application, functor );

  // Gesture possible in actor's area.
  application.ProcessEvent(GenerateTap(Gesture::Possible, 1u, 1u, Vector2(50.0f, 10.0f)));
  DALI_TEST_EQUALS(false, data.functorCalled, TEST_LOCATION);

  // Move actor somewhere else
  actor.SetPosition( 100.0f, 100.0f );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Emit Started event, we should not receive the tap.
  application.ProcessEvent(GenerateTap(Gesture::Started, 1u, 1u, Vector2(50.0f, 10.0f)));
  DALI_TEST_EQUALS(false, data.functorCalled, TEST_LOCATION);

  // Tap possible in empty area.
  application.ProcessEvent(GenerateTap(Gesture::Possible, 1u, 1u, Vector2(50.0f, 10.0f)));
  DALI_TEST_EQUALS(false, data.functorCalled, TEST_LOCATION);

  // Move actor in to the tap position.
  actor.SetPosition( 0.0f, 0.0f );

  // Render and notify
  application.SendNotification();
  application.Render();

  // Emit Started event, we should not receive the tap.
  application.ProcessEvent(GenerateTap(Gesture::Started, 1u, 1u, Vector2(50.0f, 10.0f)));
  DALI_TEST_EQUALS(false, data.functorCalled, TEST_LOCATION);

  // Normal tap in actor's area for completeness.
  application.ProcessEvent(GenerateTap(Gesture::Possible, 1u, 1u, Vector2(50.0f, 10.0f)));
  application.ProcessEvent(GenerateTap(Gesture::Started, 1u, 1u, Vector2(50.0f, 10.0f)));
  DALI_TEST_EQUALS(true, data.functorCalled, TEST_LOCATION);
  END_TEST;
}