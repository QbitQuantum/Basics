static void UtcDaliKeyInputFocusManagerSignalUnhandledKeyEvent()
{
  ToolkitTestApplication application;

  tet_infoline("UtcDaliKeyInputFocusManagerSignalUnhandledKeyEvent");

  SignalData data;
  SignalUnhandledKeyEventCallback callback( data );

  KeyInputFocusManager manager = KeyInputFocusManager::Get();
  manager.UnhandledKeyEventSignal().Connect( &callback, &SignalUnhandledKeyEventCallback::Callback );


  Integration::KeyEvent event("a", "a", 0, 0, 0, Integration::KeyEvent::Up);
  application.ProcessEvent(event);

  DALI_TEST_CHECK(data.functorCalled);
  DALI_TEST_CHECK(event.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK(event.keyCode == data.receivedKeyEvent.keyCode);
  DALI_TEST_CHECK(event.keyString == data.receivedKeyEvent.keyPressed );
  DALI_TEST_CHECK(event.state == data.receivedKeyEvent.state );

  data.Reset();

  Integration::KeyEvent event2("v", "v", 0, 0, 0, Integration::KeyEvent::Up);
  application.ProcessEvent(event2);

  DALI_TEST_CHECK(data.functorCalled);
  DALI_TEST_CHECK(event2.keyName == data.receivedKeyEvent.keyPressedName );
  DALI_TEST_CHECK(event2.keyCode == data.receivedKeyEvent.keyCode);
  DALI_TEST_CHECK(event2.keyString == data.receivedKeyEvent.keyPressed );
}