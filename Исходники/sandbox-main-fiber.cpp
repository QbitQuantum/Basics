INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Reset data
    i = 0;
    memset( buffer, 0, sizeof(buffer) );

    // Convert this thread
    g_pFibers[FIBER_PRIMARY] = ConvertThreadToFiber( NULL );

    // Create the fibers
    g_pFibers[FIBER1] = CreateFiber( 0, Fiber1, NULL );
    g_pFibers[FIBER2] = CreateFiber( 0, Fiber2, NULL );

    // Execute the fibers
    SwitchToFiber( g_pFibers[FIBER1] );

    // Terminate the input
    buffer[i++] = '\0';

    DeleteFiber( g_pFibers[FIBER1] );
    DeleteFiber( g_pFibers[FIBER2] );

    OutputDebugString( buffer );
}