int EPOC_HandleWsEvent(_THIS, const TWsEvent& aWsEvent)
{
    int posted = 0;
    SDL_keysym keysym;
    
//    SDL_TRACE1("hws %d", aWsEvent.Type());

    switch (aWsEvent.Type())
		{    
    case EEventPointer: /* Mouse pointer events */
		{

        const TPointerCursorMode mode =  Private->EPOC_WsSession.PointerCursorMode();

        if(mode == EPointerCursorNone) 
            {
            return 0; //TODO: Find out why events are get despite of cursor should be off
            }

        const TPointerEvent* pointerEvent = aWsEvent.Pointer();
        TPoint mousePos = pointerEvent->iPosition;

        /*!! TODO Pointer do not yet work properly
        //SDL_TRACE1("SDL: EPOC_HandleWsEvent, pointerEvent->iType=%d", pointerEvent->iType); //!!

        if (Private->EPOC_ShrinkedHeight) {
            mousePos.iY <<= 1; // Scale y coordinate to shrinked screen height
        }
        if (Private->EPOC_ShrinkedWidth) {
            mousePos.iX <<= 1; // Scale x coordinate to shrinked screen width
        }
        */

		posted += SDL_PrivateMouseMotion(0, 0, mousePos.iX, mousePos.iY); /* Absolute position on screen */

		switch (pointerEvent->iType)
			{
        case TPointerEvent::EButton1Down:
            posted += SDL_PrivateMouseButton(SDL_PRESSED, SDL_BUTTON_LEFT, 0, 0);
			break;
        case TPointerEvent::EButton1Up:
			posted += SDL_PrivateMouseButton(SDL_RELEASED, SDL_BUTTON_LEFT, 0, 0);
			break;
        case TPointerEvent::EButton2Down:
            posted += SDL_PrivateMouseButton(SDL_PRESSED, SDL_BUTTON_RIGHT, 0, 0);
			break;
		case TPointerEvent::EButton2Up:
			posted += SDL_PrivateMouseButton(SDL_RELEASED, SDL_BUTTON_RIGHT, 0, 0);
			break;
        case TPointerEvent::EButton3Down:
            posted += SDL_PrivateMouseButton(SDL_PRESSED, SDL_BUTTON_MIDDLE, 0, 0);
			break;
        case TPointerEvent::EButton3Up:
			posted += SDL_PrivateMouseButton(SDL_RELEASED, SDL_BUTTON_MIDDLE, 0, 0);
			break;
			} // switch
        break;
	    }
    
    case EEventKeyDown: /* Key events */
    {
#ifdef SYMBIAN_CRYSTAL
		// special case: 9300/9500 rocker down, simulate left mouse button
		if (aWsEvent.Key()->iScanCode == EStdKeyDeviceA)
			{
            const TPointerCursorMode mode =  Private->EPOC_WsSession.PointerCursorMode();
            if(mode != EPointerCursorNone) 
                posted += SDL_PrivateMouseButton(SDL_PRESSED, SDL_BUTTON_LEFT, 0, 0);
			}
#endif
       (void*)TranslateKey(_this, aWsEvent.Key()->iScanCode, &keysym);
            
#ifndef DISABLE_JOYSTICK
        /* Special handling */
        switch((int)keysym.sym) {
        case SDLK_CAPSLOCK:
            if (!isCursorVisible) {
                /* Enable virtual cursor */
	            HAL::Set(HAL::EMouseState, HAL::EMouseState_Visible);
            }
            else {
                /* Disable virtual cursor */
                HAL::Set(HAL::EMouseState, HAL::EMouseState_Invisible);
            }
            isCursorVisible = !isCursorVisible;
            break;
        }
#endif        
	    posted += SDL_PrivateKeyboard(SDL_PRESSED, &keysym);
        break;
	} 

    case EEventKeyUp: /* Key events */
		{
#ifdef SYMBIAN_CRYSTAL
		// special case: 9300/9500 rocker up, simulate left mouse button
		if (aWsEvent.Key()->iScanCode == EStdKeyDeviceA)
			{
            posted += SDL_PrivateMouseButton(SDL_RELEASED, SDL_BUTTON_LEFT, 0, 0);
			}
#endif
	    posted += SDL_PrivateKeyboard(SDL_RELEASED, TranslateKey(_this, aWsEvent.Key()->iScanCode, &keysym));
        break;
		}
    
    case EEventFocusGained: /* SDL window got focus */
	    {
        Private->EPOC_IsWindowFocused = ETrue;
		posted += SDL_PrivateAppActive(1, SDL_APPINPUTFOCUS|SDL_APPMOUSEFOCUS);
        /* Draw window background and screen buffer */
        DisableKeyBlocking(_this);  //Markus: guess why:-)
 
        RedrawWindowL(_this);  
        break;
	    }

    case EEventFocusLost: /* SDL window lost focus */
		{
/*        
        CFbsBitmap* bmp = new (ELeave) CFbsBitmap();
        bmp->Create(Private->EPOC_ScreenSize, Private->EPOC_DisplayMode);
        Private->EPOC_WsScreen->CopyScreenToBitmap(bmp);
        Private->EPOC_WindowGc->Activate(Private->EPOC_WsWindow);
        Private->EPOC_WsWindow.BeginRedraw(TRect(Private->EPOC_WsWindow.Size()));
	    Private->EPOC_WindowGc->BitBlt(TPoint(0, 0), bmp);
	    Private->EPOC_WsWindow.EndRedraw();
	    Private->EPOC_WindowGc->Deactivate();
        bmp->Save(_L("C:\\scr.mbm"));
        delete bmp;
*/       

		Private->EPOC_IsWindowFocused = EFalse;

		posted += SDL_PrivateAppActive(0, SDL_APPINPUTFOCUS|SDL_APPMOUSEFOCUS);

        RWsSession s;
        s.Connect();
        RWindowGroup g(s);
        g.Construct(TUint32(&g), EFalse);
        g.EnableReceiptOfFocus(EFalse);
        RWindow w(s);
        w.Construct(g, TUint32(&w));
        w.SetExtent(TPoint(0, 0), Private->EPOC_WsWindow.Size());
        w.SetOrdinalPosition(0);
        w.Activate();
        w.Close();
        g.Close();
        s.Close();

/*
        Private->EPOC_WsSession.SetWindowGroupOrdinalPosition(Private->EPOC_WsWindowGroupID, -1);

            
        SDL_Delay(500);
        TInt focus = -1;
        while(focus < 0)
            {
            const TInt curr = Private->EPOC_WsSession.GetFocusWindowGroup();
            if(curr != Private->EPOC_WsWindowGroupID)
                focus = curr;
            else
                SDL_Delay(500);
            }

        if(1 < Private->EPOC_WsSession.GetWindowGroupOrdinalPriority(Private->EPOC_WsWindowGroupID))
            {
            Private->EPOC_WsSession.SetWindowGroupOrdinalPosition(focus, -1);
            SDL_Delay(500);
            Private->EPOC_WsSession.SetWindowGroupOrdinalPosition(focus, 0);
            }
*/
        /*//and the request redraw
        TRawEvent redrawEvent;
        redrawEvent.Set(TRawEvent::ERedraw);
        Private->EPOC_WsSession.SimulateRawEvent(redrawEvent);
        Private->EPOC_WsSession.Flush();*/
#if 0
        //!! Not used
        // Wait and eat events until focus is gained again
	    while (ETrue) {
            Private->EPOC_WsSession.EventReady(&Private->EPOC_WsEventStatus);
            User::WaitForRequest(Private->EPOC_WsEventStatus);
		    Private->EPOC_WsSession.GetEvent(Private->EPOC_WsEvent);
            TInt eventType = Private->EPOC_WsEvent.Type();
		    Private->EPOC_WsEventStatus = KRequestPending;
		    //Private->EPOC_WsSession.EventReady(&Private->EPOC_WsEventStatus);
            if (eventType == EEventFocusGained) {
                RedrawWindowL(_this);
                break;
            }
	    }
#endif
        break;
	    }

    case EEventModifiersChanged: 
    {
	    TModifiersChangedEvent* modEvent = aWsEvent.ModifiersChanged();
        TUint modstate = KMOD_NONE;
        if (modEvent->iModifiers == EModifierLeftShift)
            modstate |= KMOD_LSHIFT;
        if (modEvent->iModifiers == EModifierRightShift)
            modstate |= KMOD_RSHIFT;
        if (modEvent->iModifiers == EModifierLeftCtrl)
            modstate |= KMOD_LCTRL;
        if (modEvent->iModifiers == EModifierRightCtrl)
            modstate |= KMOD_RCTRL;
        if (modEvent->iModifiers == EModifierLeftAlt)
            modstate |= KMOD_LALT;
        if (modEvent->iModifiers == EModifierRightAlt)
            modstate |= KMOD_RALT;
        if (modEvent->iModifiers == EModifierLeftFunc)
            modstate |= KMOD_LMETA;
        if (modEvent->iModifiers == EModifierRightFunc)
            modstate |= KMOD_RMETA;
        if (modEvent->iModifiers == EModifierCapsLock)
            modstate |= KMOD_CAPS;
        SDL_SetModState(STATIC_CAST(SDLMod,(modstate | KMOD_LSHIFT)));
        break;
    }
    default:            
        break;
	} 
	
    return posted;
}