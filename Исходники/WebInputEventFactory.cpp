WebMouseWheelEvent WebInputEventFactory::mouseWheelEvent(HWND hwnd, UINT message,
                                                         WPARAM wparam, LPARAM lparam)
{
    WebMouseWheelEvent result; //(WebInputEvent::Uninitialized());

    result.type = WebInputEvent::MouseWheel;

    // TODO(pkasting): http://b/1117926 Are we guaranteed that the message that
    // GetMessageTime() refers to is the same one that we're passed in? Perhaps
    // one of the construction parameters should be the time passed by the
    // caller, who would know for sure.
    result.timeStampSeconds = GetMessageTime() / 1000.0;

    result.button = WebMouseEvent::ButtonNone;

    // Get key state, coordinates, and wheel delta from event.
    typedef SHORT (WINAPI *GetKeyStateFunction)(int key);
    GetKeyStateFunction getKeyState;
    UINT keyState;
    float wheelDelta;
    bool horizontalScroll = false;
    if ((message == WM_VSCROLL) || (message == WM_HSCROLL)) {
        // Synthesize mousewheel event from a scroll event.  This is needed to
        // simulate middle mouse scrolling in some laptops.  Use GetAsyncKeyState
        // for key state since we are synthesizing the input event.
        getKeyState = GetAsyncKeyState;
        keyState = 0;
        if (getKeyState(VK_SHIFT))
            keyState |= MK_SHIFT;
        if (getKeyState(VK_CONTROL))
            keyState |= MK_CONTROL;
        // NOTE: There doesn't seem to be a way to query the mouse button state
        // in this case.

        POINT cursorPosition = {0};
        GetCursorPos(&cursorPosition);
        result.globalX = cursorPosition.x;
        result.globalY = cursorPosition.y;

        switch (LOWORD(wparam)) {
        case SB_LINEUP:    // == SB_LINELEFT
            wheelDelta = WHEEL_DELTA;
            break;
        case SB_LINEDOWN:  // == SB_LINERIGHT
            wheelDelta = -WHEEL_DELTA;
            break;
        case SB_PAGEUP:
            wheelDelta = 1;
            result.scrollByPage = true;
            break;
        case SB_PAGEDOWN:
            wheelDelta = -1;
            result.scrollByPage = true;
            break;
        default:  // We don't supoprt SB_THUMBPOSITION or SB_THUMBTRACK here.
            wheelDelta = 0;
            break;
        }

        if (message == WM_HSCROLL)
            horizontalScroll = true;
    } else {
        // Non-synthesized event; we can just read data off the event.
        getKeyState = GetKeyState;
        keyState = GET_KEYSTATE_WPARAM(wparam);

        result.globalX = static_cast<short>(LOWORD(lparam));
        result.globalY = static_cast<short>(HIWORD(lparam));

        wheelDelta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wparam));
        if (message == WM_MOUSEHWHEEL) {
            horizontalScroll = true;
            wheelDelta = -wheelDelta;  // Windows is <- -/+ ->, WebKit <- +/- ->.
        }
    }
    if (keyState & MK_SHIFT)
        horizontalScroll = true;

    // Set modifiers based on key state.
    if (keyState & MK_SHIFT)
        result.modifiers |= WebInputEvent::ShiftKey;
    if (keyState & MK_CONTROL)
        result.modifiers |= WebInputEvent::ControlKey;
    if (getKeyState(VK_MENU) & 0x8000)
        result.modifiers |= WebInputEvent::AltKey;
    if (keyState & MK_LBUTTON)
        result.modifiers |= WebInputEvent::LeftButtonDown;
    if (keyState & MK_MBUTTON)
        result.modifiers |= WebInputEvent::MiddleButtonDown;
    if (keyState & MK_RBUTTON)
        result.modifiers |= WebInputEvent::RightButtonDown;

    // Set coordinates by translating event coordinates from screen to client.
    POINT clientPoint = { result.globalX, result.globalY };
    MapWindowPoints(0, hwnd, &clientPoint, 1);
    result.x = clientPoint.x;
    result.y = clientPoint.y;
    result.windowX = result.x;
    result.windowY = result.y;

    // Convert wheel delta amount to a number of pixels to scroll.
    //
    // How many pixels should we scroll per line?  Gecko uses the height of the
    // current line, which means scroll distance changes as you go through the
    // page or go to different pages.  IE 7 is ~50 px/line, although the value
    // seems to vary slightly by page and zoom level.  Since IE 7 has a smoothing
    // algorithm on scrolling, it can get away with slightly larger scroll values
    // without feeling jerky.  Here we use 100 px per three lines (the default
    // scroll amount is three lines per wheel tick).
    static const float scrollbarPixelsPerLine = 100.0f / 3.0f;
    wheelDelta /= WHEEL_DELTA;
    float scrollDelta = wheelDelta;
    if (horizontalScroll) {
        unsigned long scrollChars = defaultScrollCharsPerWheelDelta;
        SystemParametersInfo(SPI_GETWHEELSCROLLCHARS, 0, &scrollChars, 0);
        // TODO(pkasting): Should probably have a different multiplier
        // scrollbarPixelsPerChar here.
        scrollDelta *= static_cast<float>(scrollChars) * scrollbarPixelsPerLine;
    } else {
        unsigned long scrollLines = defaultScrollLinesPerWheelDelta;
        SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &scrollLines, 0);
        if (scrollLines == WHEEL_PAGESCROLL)
            result.scrollByPage = true;
        if (!result.scrollByPage)
            scrollDelta *= static_cast<float>(scrollLines) * scrollbarPixelsPerLine;
    }

    // Set scroll amount based on above calculations.  WebKit expects positive
    // deltaY to mean "scroll up" and positive deltaX to mean "scroll left".
    if (horizontalScroll) {
        result.deltaX = scrollDelta;
        result.wheelTicksX = wheelDelta;
    } else {
        result.deltaY = scrollDelta;
        result.wheelTicksY = wheelDelta;
    }

    return result;
}