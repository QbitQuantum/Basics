void
COSXScreen::fakeMouseButton(ButtonID id, bool press)
{
	NXEventHandle handle = NXOpenEventStatus();
	double clickTime = NXClickTime(handle);
	
	if ((ARCH->time() - m_lastDoubleClick) <= clickTime) {
		// drop all down and up fakes immedately after a double click.
		// TODO: perhaps there is a better way to do this, usually in
		// finder, if you tripple click a folder, it will open it and
		// then select a folder under the cursor -- and perhaps other
		// strange behaviour might happen?
		LOG((CLOG_DEBUG1 "dropping mouse button %s",
			press ? "press" : "release"));
		return;
	}
	
	// Buttons are indexed from one, but the button down array is indexed from zero
	UInt32 index = id - kButtonLeft;
	if (index >= NumButtonIDs) {
		return;
	}
	
	CGPoint pos;
	if (!m_cursorPosValid) {
		SInt32 x, y;
		getCursorPos(x, y);
	}
	pos.x = m_xCursor;
	pos.y = m_yCursor;

	// variable used to detect mouse coordinate differences between
	// old & new mouse clicks. Used in double click detection.
	SInt32 xDiff = m_xCursor - m_lastSingleClickXCursor;
	SInt32 yDiff = m_yCursor - m_lastSingleClickYCursor;
	double diff = sqrt(xDiff * xDiff + yDiff * yDiff);
	// max sqrt(x^2 + y^2) difference allowed to double click
	// since we don't have double click distance in NX APIs
	// we define our own defaults.
	const double maxDiff = sqrt(2) + 0.0001;

	if (press && (id == kButtonLeft) &&
		((ARCH->time() - m_lastSingleClick) <= clickTime) &&
		diff <= maxDiff) {

		LOG((CLOG_DEBUG1 "faking mouse left double click"));
		
		// finder does not seem to detect double clicks from two separate
		// CGEventCreateMouseEvent calls. so, if we detect a double click we
		// use CGEventSetIntegerValueField to tell the OS.
		// 
		// the caveat here is that findor will see this as a single click 
		// followed by a double click (even though there should be only a
		// double click). this may cause weird behaviour in other apps.
		//
		// for some reason using the old CGPostMouseEvent function, doesn't
		// cause double clicks (though i'm sure it did work at some point).
		
		CGEventRef event = CGEventCreateMouseEvent(
			NULL, kCGEventLeftMouseDown, pos, kCGMouseButtonLeft);
		
		CGEventSetIntegerValueField(event, kCGMouseEventClickState, 2);
		m_buttonState.set(index, kMouseButtonDown);
		CGEventPost(kCGHIDEventTap, event);
		
		CGEventSetType(event, kCGEventLeftMouseUp);
		m_buttonState.set(index, kMouseButtonUp);
		CGEventPost(kCGHIDEventTap, event);
		
		CFRelease(event);
	
		m_lastDoubleClick = ARCH->time();
	}
	else {
		
		// ... otherwise, perform a single press or release as normal.
		
		MouseButtonState state = press ? kMouseButtonDown : kMouseButtonUp;
		
		LOG((CLOG_DEBUG1 "faking mouse button %s", press ? "press" : "release"));
		
		MouseButtonEventMapType thisButtonMap = MouseButtonEventMap[index];
		CGEventType type = thisButtonMap[state];
		
		CGEventRef event = CGEventCreateMouseEvent(NULL, type, pos, index);
	
		m_buttonState.set(index, state);
		CGEventPost(kCGHIDEventTap, event);
		
		CFRelease(event);
	
		m_lastSingleClick = ARCH->time();
		m_lastSingleClickXCursor = m_xCursor;
		m_lastSingleClickYCursor = m_yCursor;
	}
}