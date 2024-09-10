void WindowsMouseController::grab()
{
    RECT clipRegion;
    GetWindowRect( mWindowHandle, &clipRegion );
    clipRegion.left += 10;
    clipRegion.right -= 10;
    clipRegion.top += 33;
    clipRegion.bottom -= 10;
    ClipCursor( &clipRegion );
}