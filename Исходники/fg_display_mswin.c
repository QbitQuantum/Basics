void fgPlatformGlutSwapBuffers( SFG_PlatformDisplay *pDisplayPtr, SFG_Window* CurrentWindow )
{
    SwapBuffers( CurrentWindow->Window.pContext.Device );
}