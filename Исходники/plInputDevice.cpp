plMouseDevice::plMouseDevice()
{
    fXPos = 0;
    fYPos = 0;
    fCursorID = CURSOR_UP;
    fButtonState = 0;
    fOpacity = 1.f;

    fCursor = nil;
    CreateCursor( fCursorID );
    plMouseDevice::fInstance = this;
    fXMsg = nil;
    fYMsg = nil;
    fB2Msg = nil;

    fLeftBMsg[0] = nil;
    fLeftBMsg[1] = nil;
    fRightBMsg[0] = nil;
    fRightBMsg[1] = nil;
    fMiddleBMsg[0] = nil;
    fMiddleBMsg[1] = nil;
    
}