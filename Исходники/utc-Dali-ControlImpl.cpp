int UtcDaliControlImplOnGestureMethods(void)
{
  ToolkitTestApplication application;

  // Check gesture actually happens
  {
    DummyControl dummy = DummyControl::New(true);
    dummy.SetSize( Vector3(100.0f, 100.0f, 100.0f) );

    dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
    Stage::GetCurrent().Add(dummy);

    // Render and notify a couple of times
    application.SendNotification();
    application.Render();
    application.SendNotification();
    application.Render();

    DummyControlImplOverride& dummyImpl = static_cast<DummyControlImplOverride&>(dummy.GetImplementation());
    dummyImpl.EnableGestureDetection( Gesture::Type(Gesture::Pinch | Gesture::Pan | Gesture::Tap | Gesture::LongPress) );

    DALI_TEST_CHECK( dummyImpl.pinchCalled == false );
    Integration::PinchGestureEvent pinch(Gesture::Started);
    pinch.scale = 10.0f;
    pinch.speed = 50.0f;
    pinch.centerPoint = Vector2(20.0f, 20.0f);
    application.ProcessEvent(pinch);
    DALI_TEST_CHECK( dummyImpl.pinchCalled == true );

    DALI_TEST_CHECK( dummyImpl.panCalled == false );
    Integration::PanGestureEvent pan(Gesture::Possible);
    pan.previousPosition = Vector2(10.0f, 20.0f);
    pan.currentPosition = Vector2(20.0f, 20.0f);
    pan.timeDelta = 10;
    pan.numberOfTouches = 1u;
    application.ProcessEvent(pan);
    pan.state = Gesture::Started;
    application.ProcessEvent(pan);
    DALI_TEST_CHECK( dummyImpl.panCalled == true );

    DALI_TEST_CHECK( dummyImpl.tapCalled == false );
    Integration::TapGestureEvent tap(Gesture::Possible);
    tap.numberOfTaps = 1u;
    tap.numberOfTouches = 1u;
    tap.point = Vector2(50.0f, 50.0f);
    application.ProcessEvent(tap);
    tap.state = Gesture::Started;
    application.ProcessEvent(tap);
    DALI_TEST_CHECK( dummyImpl.tapCalled == true );

    DALI_TEST_CHECK( dummyImpl.longPressCalled == false );
    Integration::LongPressGestureEvent longPress(Gesture::Possible);
    longPress.numberOfTouches = 1u;
    longPress.point = Vector2(50.0f, 50.0f);
    application.ProcessEvent(longPress);
    longPress.state = Gesture::Started;
    application.ProcessEvent(longPress);
    DALI_TEST_CHECK( dummyImpl.longPressCalled == true );
    longPress.state = Gesture::Finished;
    application.ProcessEvent(longPress);

    Stage::GetCurrent().Remove(dummy);
  }

  // Ensure full code coverage
  {
    DummyControl dummy = DummyControl::New();
    dummy.SetSize( Vector3(100.0f, 100.0f, 100.0f) );

    dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
    Stage::GetCurrent().Add(dummy);

    // Render and notify a couple of times
    application.SendNotification();
    application.Render();
    application.SendNotification();
    application.Render();

    DummyControlImpl& dummyImpl = static_cast<DummyControlImpl&>(dummy.GetImplementation());
    dummyImpl.EnableGestureDetection( Gesture::Type(Gesture::Pinch | Gesture::Pan | Gesture::Tap | Gesture::LongPress) );

    DALI_TEST_CHECK( dummy.GetCurrentScale().x != 10.0f );
    Integration::PinchGestureEvent pinch(Gesture::Started);
    pinch.scale = 10.0f;
    pinch.speed = 50.0f;
    pinch.centerPoint = Vector2(20.0f, 20.0f);
    application.ProcessEvent(pinch);

    // Render and notify a couple of times
    application.SendNotification();
    application.Render();
    application.SendNotification();
    application.Render();
    DALI_TEST_CHECK( dummy.GetCurrentScale().x == 10.0f );

    Integration::PanGestureEvent pan(Gesture::Possible);
    pan.previousPosition = Vector2(10.0f, 20.0f);
    pan.currentPosition = Vector2(20.0f, 20.0f);
    pan.timeDelta = 10;
    pan.numberOfTouches = 1u;
    application.ProcessEvent(pan);
    pan.state = Gesture::Started;
    application.ProcessEvent(pan);

    Integration::TapGestureEvent tap(Gesture::Possible);
    tap.numberOfTaps = 1u;
    tap.numberOfTouches = 1u;
    tap.point = Vector2(50.0f, 50.0f);
    application.ProcessEvent(tap);
    tap.state = Gesture::Started;
    application.ProcessEvent(tap);

    Integration::LongPressGestureEvent longPress(Gesture::Possible);
    longPress.numberOfTouches = 1u;
    longPress.point = Vector2(50.0f, 50.0f);
    application.ProcessEvent(longPress);
    longPress.state = Gesture::Started;
    application.ProcessEvent(longPress);
    longPress.state = Gesture::Finished;
    application.ProcessEvent(longPress);

    Stage::GetCurrent().Remove(dummy);
  }
  END_TEST;
}