int UtcDaliStageSignalKeyEventP(void)
{
  TestApplication application;
  Stage stage = Stage::GetCurrent();

  KeyEventSignalData data;
  KeyEventReceivedFunctor functor( data );
  stage.KeyEventSignal().Connect( &application, functor );

  Integration::KeyEvent event( "i", "i", 0, 0, 0, Integration::KeyEvent::Down );
  application.ProcessEvent( event );

  DALI_TEST_EQUALS( true, data.functorCalled, TEST_LOCATION );
  DALI_TEST_CHECK( event.keyModifier == data.receivedKeyEvent.keyModifier );
  DALI_TEST_CHECK( event.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK( event.keyString == data.receivedKeyEvent.keyPressed );
  DALI_TEST_CHECK( event.state == static_cast<Integration::KeyEvent::State>( data.receivedKeyEvent.state ) );

  data.Reset();

  Integration::KeyEvent event2( "i", "i", 0, 0, 0, Integration::KeyEvent::Up );
  application.ProcessEvent( event2 );

  DALI_TEST_EQUALS( true, data.functorCalled, TEST_LOCATION );
  DALI_TEST_CHECK( event2.keyModifier == data.receivedKeyEvent.keyModifier );
  DALI_TEST_CHECK( event2.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK( event2.keyString == data.receivedKeyEvent.keyPressed );
  DALI_TEST_CHECK( event2.state == static_cast<Integration::KeyEvent::State>( data.receivedKeyEvent.state ) );

  data.Reset();

  Integration::KeyEvent event3( "a", "a", 0, 0, 0, Integration::KeyEvent::Down );
  application.ProcessEvent( event3 );

  DALI_TEST_EQUALS( true, data.functorCalled, TEST_LOCATION );
  DALI_TEST_CHECK( event3.keyModifier == data.receivedKeyEvent.keyModifier );
  DALI_TEST_CHECK( event3.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK( event3.keyString == data.receivedKeyEvent.keyPressed );
  DALI_TEST_CHECK( event3.state == static_cast<Integration::KeyEvent::State>( data.receivedKeyEvent.state ) );

  data.Reset();

  Integration::KeyEvent event4( "a", "a", 0, 0, 0, Integration::KeyEvent::Up );
  application.ProcessEvent( event4 );

  DALI_TEST_EQUALS( true, data.functorCalled, TEST_LOCATION );
  DALI_TEST_CHECK( event4.keyModifier == data.receivedKeyEvent.keyModifier );
  DALI_TEST_CHECK( event4.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK( event4.keyString == data.receivedKeyEvent.keyPressed );
  DALI_TEST_CHECK( event4.state == static_cast<Integration::KeyEvent::State>( data.receivedKeyEvent.state ) );
  END_TEST;
}