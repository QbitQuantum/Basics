int UtcDaliBaseHandleConnectSignal(void)
{
  TestApplication application;
  tet_infoline("Testing Dali::BaseHandle::ConnectSignal");

  gTouchCallBackCalled = false;

  // get the root layer
  Actor actor = Actor::New();
  actor.SetAnchorPoint( AnchorPoint::TOP_LEFT );
  actor.SetParentOrigin( ParentOrigin::TOP_LEFT );
  actor.SetPosition( 240, 400 );
  actor.SetSize( 100, 100 );

  Stage::GetCurrent().Add( actor );

  DALI_TEST_CHECK( gTouchCallBackCalled == false );

  // connect to its touch signal
  actor.ConnectSignal( &application, "touched", TestCallback() );

  application.SendNotification();
  application.Render(1000);
  application.SendNotification();
  application.Render(1000);

  // simulate a touch event
  Dali::TouchPoint point( 0, TouchPoint::Down, 240, 400  );
  Dali::Integration::TouchEvent event;
  event.AddPoint( point );
  application.ProcessEvent( event );

  application.SendNotification();
  application.Render(1000);
  application.SendNotification();
  application.Render(1000);

  DALI_TEST_CHECK( application.GetConnectionCount() > 0 );
  DALI_TEST_CHECK( gTouchCallBackCalled == true );

  gTouchCallBackCalled = false;
  application.DisconnectAll();

  // simulate another touch event
  application.ProcessEvent( event );

  DALI_TEST_CHECK( gTouchCallBackCalled == false );
  END_TEST;
}