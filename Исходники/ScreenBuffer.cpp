/**********************************************************************
* Purpose: Draws all characters in character buffer to the console window.
*
* Precondition:
*     None
*
* Postcondition:
*     _chbuf drawn.
*
************************************************************************/
void ScreenBuffer::Draw()
{
	WriteConsoleOutputW(_hStdout, _chbuf, _chbuf_size, _chbuf_coord, &_write_area);
}