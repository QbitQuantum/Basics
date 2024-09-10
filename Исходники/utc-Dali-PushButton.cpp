static void UtcDaliPushButtonToggled()
{
    ToolkitTestApplication application;
    tet_infoline(" UtcDaliPushButtonToggled");

    PushButton pushButton = PushButton::New();
    pushButton.SetAnchorPoint( AnchorPoint::TOP_LEFT );
    pushButton.SetParentOrigin( ParentOrigin::TOP_LEFT );
    pushButton.SetPosition( 240, 400 );
    pushButton.SetSize( 100, 100 );

    Stage::GetCurrent().Add( pushButton );

    application.SendNotification();
    application.Render();

    // connect to its touch signal
    pushButton.ToggledSignal().Connect( &PushButtonToggled );

    Dali::Integration::TouchEvent event;

    // Test1. No toggle button.

    gPushButtonToggleState = false;
    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownInside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpInside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( !gPushButtonToggleState );

    // Set toggle property.
    pushButton.SetToggleButton( true );

    // Test2. Touch point down and up inside the button twice.
    gPushButtonToggleState = false;
    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownInside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpInside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( gPushButtonToggleState );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownInside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpInside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( !gPushButtonToggleState );

    // Test3. Touch point down and up outside the button.

    gPushButtonToggleState = false;
    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownOutside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpOutside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( !gPushButtonToggleState );

    // Test4. Touch point down inside and up outside the button.

    gPushButtonToggleState = false;
    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownInside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointLeave );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpOutside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( !gPushButtonToggleState );

    // Test5. Touch point down outside and up inside the button.

    gPushButtonToggleState = false;
    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointDownOutside );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointEnter );
    application.ProcessEvent( event );

    event = Dali::Integration::TouchEvent();
    event.AddPoint( pointUpInside );
    application.ProcessEvent( event );

    DALI_TEST_CHECK( !gPushButtonToggleState );
}