void GHOST_ScreenToClient(GHOST_WindowHandle windowhandle,
                          GHOST_TInt32 inX,
                          GHOST_TInt32 inY,
                          GHOST_TInt32 *outX,
                          GHOST_TInt32 *outY)
{
	GHOST_IWindow *window = (GHOST_IWindow *) windowhandle;

	window->screenToClient(inX, inY, *outX, *outY);
}