// --------------------------------------------------------------------------------------
static pascal OSStatus windowEventHandler(EventHandlerCallRef nextHandler, EventRef event,
        void *junk)
{
#pragma unused (nextHandler, junk)

    OSStatus result = eventNotHandledErr;
    UInt32 eventClass, eventKind;
    WindowRef prefsWindow;
    Point mouseLocation, minWindowBounds;
    UInt32 modifiers;
    ControlRef listScrollBar;
    ListHandle iconList;
    Rect iconListRect;

    eventClass = GetEventClass(event);
    eventKind = GetEventKind(event);

    switch (eventClass)
    {
    case kEventClassWindow:
        GetEventParameter(event, kEventParamDirectObject, typeWindowRef, NULL,
                          sizeof(WindowRef), NULL, &prefsWindow);

        switch (eventKind)
        {
        case kEventWindowActivated:
            HandleActivate(prefsWindow, true);
            result = noErr;
            break;

        case kEventWindowDeactivated:
            HandleActivate(prefsWindow, false);
            result = noErr;
            break;

        case kEventWindowHandleContentClick:
            GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, NULL,
                              sizeof(Point), NULL, &mouseLocation);
            GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, NULL,
                              sizeof(UInt32), NULL, &modifiers);

            HandleContentClick(prefsWindow, mouseLocation, (EventModifiers)modifiers);
            result = noErr;
            break;

        case kEventWindowGetMinimumSize:
            SetPt(&minWindowBounds, gPrefsWindowWidth, gPrefsWindowHeight);
            SetEventParameter(event, kEventParamDimensions, typeQDPoint, sizeof(Point),
                              &minWindowBounds);
            result = noErr;
            break;

        case kEventWindowResizeCompleted:
            AdjustControls(prefsWindow);
            result = noErr;
            break;

        case kEventWindowClose:
            ClosePrefsWindow(prefsWindow);
            result = noErr;
            break;

        case kEventWindowDrawContent:
            HandleDrawContent(prefsWindow);
            result = noErr;
            break;

        case kEventWindowContextualMenuSelect:
            result = noErr;		// eat contextual menu clicks
            break;
        }
        break;

    case kEventClassControl:	// we need to respond to clicks in the list's scroll bar
        switch (eventKind)				// kEventControlClick instead of kEventControlHit
        {   // because the control click must be tracked
        case kEventControlClick:	// with LClick instead of the default handler
            GetEventParameter(event, kEventParamDirectObject, typeControlRef,
                              NULL, sizeof(ControlRef), NULL, &listScrollBar);

            prefsWindow = GetControlOwner(listScrollBar);
            GetWindowProperty(prefsWindow, kAppSignature, kIconListTag,
                              sizeof(ListHandle), NULL, &iconList);
            if (listScrollBar == GetListVerticalScrollBar(iconList))
            {
                GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, NULL,
                                  sizeof(Point), NULL, &mouseLocation);
                GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, NULL,
                                  sizeof(UInt32), NULL, &modifiers);

                HandleContentClick(prefsWindow, mouseLocation,
                                   (EventModifiers)modifiers);
                result = noErr;
            }
            break;
        }
        break;

    case kEventClassMouse:
        switch (eventKind)
        {
        case kEventMouseWheelMoved:
            GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, NULL,
                              sizeof(Point), NULL, &mouseLocation);
            GlobalToLocal(&mouseLocation);

            GetEventParameter(event, kEventParamWindowRef, typeWindowRef, NULL,
                              sizeof(WindowRef), NULL, &prefsWindow);
            GetWindowProperty(prefsWindow, kAppSignature, kIconListTag,
                              sizeof(ListHandle), NULL, &iconList);
            GetListViewBounds(iconList, &iconListRect);
            iconListRect.right += kScrollBarWidth;

            if (PtInRect(mouseLocation, &iconListRect))
            {
                EventMouseWheelAxis axis;
                long mouseWheelDelta;
                SInt16 pixelDepth;
                Boolean isColorDevice;

                GetEventParameter(event, kEventParamMouseWheelAxis, typeMouseWheelAxis,
                                  NULL, sizeof(EventMouseWheelAxis), NULL, &axis);
                GetEventParameter(event, kEventParamMouseWheelDelta, typeLongInteger,
                                  NULL, sizeof(long), NULL, &mouseWheelDelta);

                GetWindowDeviceDepthAndColor(prefsWindow, &pixelDepth, &isColorDevice);
                SetThemeBackground(kThemeBrushWhite, pixelDepth, isColorDevice);
                // LScroll draws the newly visible cells immediately
                if (axis == kEventMouseWheelAxisX)			// (no update event)
                    LScroll(-mouseWheelDelta, 0, iconList);
                else	// axis == kEventMouseWheelAxisY
                    LScroll(0, -mouseWheelDelta, iconList);

                result = noErr;
            }
            break;
        }
        break;

    case kEventClassTextInput:
        switch (eventKind)
        {
        case kEventTextInputUnicodeForKeyEvent:
            prefsWindow = FrontNonFloatingWindow();

            if (prefsWindow != NULL)
            {
                EventRef keyboardEvent;
                UInt32 keyCode;

                GetEventParameter(event, kEventParamTextInputSendKeyboardEvent,
                                  typeEventRef, NULL, sizeof(EventRef), NULL,
                                  &keyboardEvent);
                GetEventParameter(keyboardEvent, kEventParamKeyCode, typeUInt32, NULL,
                                  sizeof(UInt32), NULL, &keyCode);

                HandleKeyDown((char)keyCode, prefsWindow);
                result = noErr;
            }
            break;
        }
        break;
    }

    return result;
} // windowEventHandler