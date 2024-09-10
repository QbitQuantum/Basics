void cbLuaBreakHook(lua_State *L, lua_Debug *ar)
{
    // Need some other way to do this in Linux.
#ifdef __PRAXIS_WINDOWS__
    // Force GetAsyncKeyState to be called for both keys so that
    // their respective statuses are up to date.
    // Previously, only Ctrl was kept up to date. Q was checked only if Ctrl held down.
    // Press q, then other stuff, then when Ctrl pressed, a break would be triggered.
    bool bCtrlDown = ::GetAsyncKeyState(VK_LCONTROL) != 0;
    bool bQDown = ::GetAsyncKeyState(0x51) != 0;
    if(bCtrlDown && bQDown) // Ctrl-Q pressed
    {
        // Break detected. Check the time since last break.

        // If its too low, ignore.
        int nTime = ::timeGetTime();
        if(nTime < (g_nLastBreakTime + 200))
            return;

        // If its high enough, then break.
        g_nLastBreakTime = nTime;

        lua_pushstring(L, "User break.");
        lua_error(L);
        return;
    }
#endif

#ifdef __PRAXIS_LINUX__
    // SDL_GetKeyState
    // http://sdl.beuc.net/sdl.wiki/SDL_GetKeyState
    //
    // #include "SDL.h"
    // Uint8 *SDL_GetKeyState(int *numkeys);
    //
    // Example:
    //
    // Uint8 *keystate = SDL_GetKeyState(NULL);
    // if ( keystate[SDLK_RETURN] ) printf("Return Key Pressed.\n");
    // if ( keystate[SDLK_RIGHT] && keystate[SDLK_UP] ) printf("Right and Up Keys Pressed.\n");
    //
    // Note: Use SDL_PumpEvents to update the state array
    //
    // http://sdl.beuc.net/sdl.wiki/SDLKey
    // SDLK_LCTRL
    // SDLK_RCTRL
    // SDLK_q
    //
    // Calling SDL_PumpEvents shouldn't have side effects because SDL isn't being used for OpenGL

    char keys_return[32];

    //glutMainLoopEvent();
    XQueryKeymap(g_pAppDisplay, keys_return);

#if 0
    bool bNonZero = false;
    for (int i = 0; i < 32; i++)
    {
        if(keys_return[i] != 0)
            bNonZero = true;
    }

    if(bNonZero)
    {
        for (int i = 0; i < 32; i++)
        {
            printf("%d ", (unsigned int)keys_return[i]);
        }
        printf("\n");
    }
#endif

    if(keys_return[3] == 1 && keys_return[4] == 32)
    {
        // Break detected. Check the time since last break.

        // If its too low, ignore.
        int nTime = glutGet(GLUT_ELAPSED_TIME);
        if(nTime < (g_nLastBreakTime + 200))
            return;

        // If its high enough, then break.
        g_nLastBreakTime = nTime;

        lua_pushstring(L, "User break.");
        lua_error(L);
        return;
    }
#endif

    return;

#if 0
    HGLOBAL      hGlobal ;
    PTSTR        pGlobal ;

    std::string sText;

    OpenClipboard (g_AppHWND) ;
    if (hGlobal = GetClipboardData (CF_TEXT))
    {
         pGlobal = (PTSTR)GlobalLock (hGlobal) ;
         sText = pGlobal;
         GlobalUnlock(hGlobal);
    }
    CloseClipboard () ;


    if(sText == "praxis:STOP")
    {
        OpenClipboard (g_AppHWND) ;
        EmptyClipboard();
        CloseClipboard () ;

        lua_pushstring(L, "User break.");
        lua_error(L);
    }
#endif
}