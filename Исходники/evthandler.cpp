void EvtHandlerTestCase::BindMethodUsingBaseEvent()
{
    // test connecting a method taking just wxEvent and not MyEvent: this
    // should work too if we don't need any MyEvent-specific information in the
    // handler
    handler.Bind( MyEventType, &MyHandler::OnEvent, &handler );
    g_called.Reset();
    handler.ProcessEvent(e);
    CPPUNIT_ASSERT( g_called.method );
    handler.Unbind( MyEventType, &MyHandler::OnEvent, &handler );
    g_called.Reset();
    handler.ProcessEvent(e);
    CPPUNIT_ASSERT( !g_called.method );

    handler.Bind( MyEventType, &MyHandler::OnEvent, &handler, 0 );
    handler.Unbind( MyEventType, &MyHandler::OnEvent, &handler, 0 );

    handler.Bind( MyEventType, &MyHandler::OnEvent, &handler, 0, 0 );
    handler.Unbind( MyEventType, &MyHandler::OnEvent, &handler, 0, 0 );
}