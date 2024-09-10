// --------------------------------------------------------------
void
GDeviceWin32::MoveTo( float x, float y )
{
	::MoveToEx( mHDC, RInt(x), RInt(y), NULL );
}