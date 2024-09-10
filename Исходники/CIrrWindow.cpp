void CIrrWindow::_OnRButtonUp	( uiMouseEvent mouseEvent, int x, int y )
{
	releaseCapture();

	SEvent irrEvent;
	memset(&irrEvent, 0, sizeof(SEvent));

	irrEvent.EventType			= irr::EET_MOUSE_INPUT_EVENT;
	irrEvent.MouseInput.Event	= irr::EMIE_RMOUSE_LEFT_UP;
	irrEvent.MouseInput.X		= (short)x;
	irrEvent.MouseInput.Y		= (short)y;
	irrEvent.MouseInput.Shift	= mouseEvent.isShiftKeyDown();
	irrEvent.MouseInput.Control = mouseEvent.isCtrlKeyDown();
	irrEvent.MouseInput.Alt		= mouseEvent.isAltKeyDown();
	irrEvent.MouseInput.ButtonStates |= irr::EMBSM_LEFT;

	// post event
	m_device->postEventFromUser(irrEvent);

	// controller event
	// CControllerManager::getInstance()->getCurrentController()->onRMouseUp( x, y );

	//  set focus
	uiApplication::getRoot()->setFocus();
}