static pascal OSStatus WinEventHandler( EventHandlerCallRef handler,
                                        EventRef event, void *data )
{
    GenericWindow *pWin = (GenericWindow*)data;
    intf_thread_t *pIntf = pWin->getIntf();

    //fprintf(stderr, "event\n" );
    UInt32 evclass = GetEventClass( event );
    UInt32 evkind = GetEventKind( event );

    switch( evclass )
    {
    case kEventClassWindow:
        EvtRefresh evt( pIntf, 0, 0, -1, -1);
        pWin->processEvent( evt );
        break;
    }
}