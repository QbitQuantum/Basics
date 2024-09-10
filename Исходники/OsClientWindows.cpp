//////////////////////////////////////////////////////////////////////////
// setMouseLock
void OsClientWindows::setMouseLock( BcBool Enabled )
{
	// Hide cursor too.
	CURSORINFO CursorInfo;
	CursorInfo.cbSize = sizeof(CursorInfo);
	GetCursorInfo( &CursorInfo );

	if( Enabled )
	{
		if( MouseLocked_ == BcFalse )
		{
			POINT MousePosition;
			POINT WindowPosition;
			RECT Rect;

			// Get window rect in screen space.
			::GetWindowRect( hWnd_, &Rect );
		
			// Screen space cood of the client area.
			WindowPosition.x = 0;
			WindowPosition.y = 0;
			::ClientToScreen( hWnd_, &WindowPosition );
		
			// Get the cursor position
			::GetCursorPos( &MousePosition );

			const BcS32 WX = ( Rect.right - Rect.left );
			const BcS32 WY = ( Rect.bottom - Rect.top );

			// Reset delta.
			MouseDelta_ = MaVec2d( 0.0f, 0.0f );
			MousePrevDelta_ = MaVec2d( 0.0f, 0.0f );

			// Position in center of screen.
			::SetCursorPos( Rect.left + ( WX / 2 ), Rect.top + ( WY / 2 ) );

			if ( CursorInfo.flags == CURSOR_SHOWING )
			{
				while ( ShowCursor( FALSE ) >= 0 )
				{
				}
			}
		}
	}
	else
	{
		if ( CursorInfo.flags != CURSOR_SHOWING )
		{
			while ( ShowCursor( TRUE ) < 0 )
			{
			}
		}
	}

	MouseLocked_ = Enabled;
}