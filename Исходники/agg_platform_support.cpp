    //------------------------------------------------------------------------
    bool platform_support::init(unsigned width, unsigned height, unsigned flags)
    {
        if(m_specific->m_sys_format == pix_format_undefined)
        {
            return false;
        }

        m_window_flags = flags;

		// application
		EventTypeSpec		eventType;
		EventHandlerUPP		handlerUPP;

		eventType.eventClass = kEventClassApplication;
		eventType.eventKind = kEventAppQuit;

		handlerUPP = NewEventHandlerUPP(DoAppQuit);

		InstallApplicationEventHandler (handlerUPP, 1, &eventType, nil, nil);

		eventType.eventClass = kEventClassMouse;
		eventType.eventKind = kEventMouseDown;
		handlerUPP = NewEventHandlerUPP(DoMouseDown);
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);

		eventType.eventKind = kEventMouseUp;
		handlerUPP = NewEventHandlerUPP(DoMouseUp);
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);
		
		eventType.eventKind = kEventMouseDragged;
		handlerUPP = NewEventHandlerUPP(DoMouseDragged);
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);

		eventType.eventClass = kEventClassKeyboard;
		eventType.eventKind = kEventRawKeyDown;
		handlerUPP = NewEventHandlerUPP(DoKeyDown);
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);

		eventType.eventKind = kEventRawKeyUp;
		handlerUPP = NewEventHandlerUPP(DoKeyUp);
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);

		eventType.eventKind = kEventRawKeyRepeat;
		handlerUPP = NewEventHandlerUPP(DoKeyDown);		// 'key repeat' is translated to 'key down'
		InstallApplicationEventHandler (handlerUPP, 1, &eventType, this, nil);

		WindowAttributes	windowAttrs;
		Rect				bounds;

		// window
		windowAttrs = kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute | kWindowStandardHandlerAttribute;
		SetRect (&bounds, 0, 0, width, height);
		OffsetRect (&bounds, 100, 100);
		CreateNewWindow (kDocumentWindowClass, windowAttrs, &bounds, &m_specific->m_window);

        if(m_specific->m_window == nil)
        {
            return false;
        }

		// I assume the text is ASCII.
		// Change to kCFStringEncodingMacRoman, kCFStringEncodingISOLatin1, kCFStringEncodingUTF8 or what else you need.
        SetWindowTitleWithCFString (m_specific->m_window, CFStringCreateWithCStringNoCopy (nil, m_caption, kCFStringEncodingASCII, nil));
		
		eventType.eventClass = kEventClassWindow;
		eventType.eventKind = kEventWindowClose;

		handlerUPP = NewEventHandlerUPP(DoWindowClose);
		InstallWindowEventHandler (m_specific->m_window, handlerUPP, 1, &eventType, this, NULL);

		eventType.eventKind = kEventWindowDrawContent;
		handlerUPP = NewEventHandlerUPP(DoWindowDrawContent);
		InstallWindowEventHandler (m_specific->m_window, handlerUPP, 1, &eventType, this, NULL);
		
		// Periodic task
		// Instead of an idle function I use the Carbon event timer.
		// You may decide to change the wait value which is currently 50 milliseconds.
		EventLoopRef		mainLoop;
		EventLoopTimerUPP	timerUPP;
		EventLoopTimerRef	theTimer;

		mainLoop = GetMainEventLoop();
		timerUPP = NewEventLoopTimerUPP (DoPeriodicTask);
		InstallEventLoopTimer (mainLoop, 0, 50 * kEventDurationMillisecond, timerUPP, this, &theTimer);

        m_specific->create_pmap(width, height, &m_rbuf_window);
        m_initial_width = width;
        m_initial_height = height;
        on_init();
        on_resize(width, height);
        m_specific->m_redraw_flag = true;
		
  		ShowWindow (m_specific->m_window);
  		SetPortWindowPort (m_specific->m_window);
		
      return true;
    }