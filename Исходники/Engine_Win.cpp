int Engine_Win::run()
{
    m_bRunning = true;
    std::thread threadRenderLoop( &Engine_Win::renderLoop, this );
    std::thread threadLogicLoop( &Engine_Win::logicLoop, this );

    // message loop
    BOOL bRet;
    MSG msg;
    while ( ( bRet = GetMessageW( &msg, nullptr, 0, 0 ) ) != 0 )
    {
        if ( bRet == -1 )
        {
            //Dafuq? I quit!
            quit();
        }
        else
        {
            TranslateMessage( &msg );
            DispatchMessageW( &msg );
        }
        std::this_thread::sleep_for( std::chrono::milliseconds( 4 ) );
    }

    m_bRunning = false;
    threadRenderLoop.join();
    threadLogicLoop.join();

    return 0;
}