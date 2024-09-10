void X11Loop::handleX11Event()
{
    XEvent event;
    OSFactory *pOsFactory = OSFactory::instance( getIntf() );

    // Look for the next event in the queue
    XNextEvent( XDISPLAY, &event );

    if( event.xany.window == m_rDisplay.getMainWindow() )
    {
        if( event.type == ClientMessage )
        {
            Atom wm_protocols =
                XInternAtom( XDISPLAY, "WM_PROTOCOLS", False);
            Atom wm_delete =
                XInternAtom( XDISPLAY, "WM_DELETE_WINDOW", False);

            if( event.xclient.message_type == wm_protocols &&
                event.xclient.data.l[0] == wm_delete )
            {
                msg_Dbg( getIntf(), "Received WM_DELETE_WINDOW message" );
                libvlc_Quit( getIntf()->p_libvlc );
            }
        }
        return;
    }

    // Find the window to which the event is sent
    GenericWindow *pWin =
        ((X11Factory*)pOsFactory)->m_windowMap[event.xany.window];

    if( !pWin )
    {
        return;
    }

    // Send the right event object to the window
    switch( event.type )
    {
        case Expose:
        {
            EvtRefresh evt( getIntf(), event.xexpose.x,
                            event.xexpose.y, event.xexpose.width,
                            event.xexpose.height );
            pWin->processEvent( evt );
            break;
        }
        case FocusIn:
        {
            EvtFocus evt( getIntf(), true );
            pWin->processEvent( evt );
            break;
        }
        case FocusOut:
        {
            EvtFocus evt( getIntf(), false );
            pWin->processEvent( evt );
            break;
        }

        case MotionNotify:
        {
            // Don't trust the position in the event, it is
            // out of date. Get the actual current position instead
            int x, y;
            pOsFactory->getMousePos( x, y );
            EvtMotion evt( getIntf(), x, y );
            pWin->processEvent( evt );
            break;
        }
        case LeaveNotify:
        {
            EvtLeave evt( getIntf() );
            pWin->processEvent( evt );
            break;
        }
        case ButtonPress:
        case ButtonRelease:
        {
            EvtMouse::ActionType_t action = EvtMouse::kDown;
            switch( event.type )
            {
            case ButtonPress:
                action = EvtMouse::kDown;
                break;
            case ButtonRelease:
                action = EvtMouse::kUp;
                break;
            }

            int mod = X11ModToMod( event.xbutton.state );

            // Check for double clicks
            if( event.type == ButtonPress &&
                event.xbutton.button == 1 )
            {
                mtime_t time = mdate();
                int x, y;
                pOsFactory->getMousePos( x, y );
                if( time - m_lastClickTime < m_dblClickDelay &&
                    x == m_lastClickPosX && y == m_lastClickPosY )
                {
                    m_lastClickTime = 0;
                    action = EvtMouse::kDblClick;
                }
                else
                {
                    m_lastClickTime = time;
                    m_lastClickPosX = x;
                    m_lastClickPosY = y;
                }
            }

            switch( event.xbutton.button )
            {
                case 1:
                {
                    EvtMouse evt( getIntf(), event.xbutton.x,
                                  event.xbutton.y, EvtMouse::kLeft,
                                  action, mod );
                    pWin->processEvent( evt );
                    break;
                }
                case 2:
                {
                    EvtMouse evt( getIntf(), event.xbutton.x,
                                  event.xbutton.y, EvtMouse::kMiddle,
                                  action, mod );
                    pWin->processEvent( evt );
                    break;
                }
                case 3:
                {
                    EvtMouse evt( getIntf(), event.xbutton.x,
                                  event.xbutton.y, EvtMouse::kRight,
                                  action, mod );
                    pWin->processEvent( evt );
                    break;
                }
                case 4:
                {
                    // Scroll up
                    EvtScroll evt( getIntf(), event.xbutton.x,
                                   event.xbutton.y, EvtScroll::kUp,
                                   mod );
                    pWin->processEvent( evt );
                    break;
                }
                case 5:
                {
                    // Scroll down
                    EvtScroll evt( getIntf(), event.xbutton.x,
                                   event.xbutton.y, EvtScroll::kDown,
                                   mod );
                    pWin->processEvent( evt );
                    break;
                }
            }
            break;
        }
        case KeyPress:
        case KeyRelease:
        {
            // Take the first keysym = lower case character, and translate.
            int key = keysymToVlcKey( XLookupKeysym( &event.xkey, 0 ) );

            EvtKey evt( getIntf(), key,
                        event.type==KeyRelease ? EvtKey::kUp : EvtKey::kDown,
                        X11ModToMod( event.xkey.state ) );
            pWin->processEvent( evt );
            break;
        }

        case ClientMessage:
        {
            // Get the message type
            string type = XGetAtomName( XDISPLAY, event.xclient.message_type );

            // Find the DnD object for this window
            X11DragDrop *pDnd =
                ((X11Factory*)pOsFactory)->m_dndMap[event.xany.window];
            if( !pDnd )
            {
                msg_Err( getIntf(), "no associated D&D object" );
                return;
            }

            if( type == "XdndEnter" )
                pDnd->dndEnter( event.xclient.data.l );
            else if( type == "XdndPosition" )
                pDnd->dndPosition( event.xclient.data.l );
            else if( type == "XdndLeave" )
                pDnd->dndLeave( event.xclient.data.l );
            else if( type == "XdndDrop" )
                pDnd->dndDrop( event.xclient.data.l );
            break;
        }
    }
}