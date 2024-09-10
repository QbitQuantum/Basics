void I_InitGraphics(void)
{
    SDL_Event dummy;
    byte *doompal;
    int flags = 0;
    char *env;

    // Pass through the XSCREENSAVER_WINDOW environment variable to 
    // SDL_WINDOWID, to embed the SDL window into the Xscreensaver
    // window.

    env = getenv("XSCREENSAVER_WINDOW");

    if (env != NULL)
    {
        char winenv[30];
        int winid;

        sscanf(env, "0x%x", &winid);
        sprintf(winenv, "SDL_WINDOWID=%i", winid);

        putenv(winenv);
    }

    SetSDLVideoDriver();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        I_Error("Failed to initialize video: %s", SDL_GetError());
    }

    // Check for command-line video-related parameters.

    CheckCommandLine();

    doompal = W_CacheLumpName (DEH_String("PLAYPAL"),PU_CACHE);

    if (screensaver_mode)
    {
        windowwidth = 0;
        windowheight = 0;
    }
    else
    {
        if (autoadjust_video_settings)
        {
            I_AutoAdjustSettings();
        }

        windowwidth = screen_width;
        windowheight = screen_height;

        screen_mode = I_FindScreenMode(windowwidth, windowheight);

        if (screen_mode == NULL)
        {
            I_Error("I_InitGraphics: Unable to find a screen mode small "
                    "enough for %ix%i", windowwidth, windowheight);
        }

        if (windowwidth != screen_mode->width
         || windowheight != screen_mode->height)
        {
            printf("I_InitGraphics: %s (%ix%i within %ix%i)\n",
                   WindowBoxType(screen_mode, windowwidth, windowheight),
                   screen_mode->width, screen_mode->height,
                   windowwidth, windowheight);
        }

        // Generate lookup tables before setting the video mode.

        if (screen_mode->InitMode != NULL)
        {
            screen_mode->InitMode(doompal);
        }
    }

    // Set up title and icon.  Windows cares about the ordering; this
    // has to be done before the call to SDL_SetVideoMode.

    I_SetWindowCaption();
#if !SDL_VERSION_ATLEAST(1, 3, 0)
    I_SetWindowIcon();
#endif

    // Set the video mode.

    flags |= SDL_SWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF;

    if (fullscreen)
    {
        flags |= SDL_FULLSCREEN;
    }

    screen = SDL_SetVideoMode(windowwidth, windowheight, 8, flags);

    if (screen == NULL)
    {
        I_Error("Error setting video mode: %s\n", SDL_GetError());
    }

    // Start with a clear black screen
    // (screen will be flipped after we set the palette)

    if (SDL_LockSurface(screen) >= 0)
    {
        byte *screenpixels;
        int y;

        screenpixels = (byte *) screen->pixels;

        for (y=0; y<screen->h; ++y)
            memset(screenpixels + screen->pitch * y, 0, screen->w);

        SDL_UnlockSurface(screen);
    }

    // Set the palette

    I_SetPalette(doompal);
    SDL_SetColors(screen, palette, 0, 256);

    CreateCursors();

    UpdateFocus();
    UpdateGrab();

    // In screensaver mode, now find a screen_mode to use.

    if (screensaver_mode)
    {
        screen_mode = I_FindScreenMode(screen->w, screen->h);

        if (screen_mode == NULL)
        {
            I_Error("I_InitGraphics: Unable to find a screen mode small "
                    "enough for %ix%i", screen->w, screen->h);
        }

        // Generate lookup tables before setting the video mode.

        if (screen_mode->InitMode != NULL)
        {
            screen_mode->InitMode(doompal);
        }
    }
    
    // On some systems, it takes a second or so for the screen to settle
    // after changing modes.  We include the option to add a delay when
    // setting the screen mode, so that the game doesn't start immediately
    // with the player unable to see anything.

    if (fullscreen && !screensaver_mode)
    {
        SDL_Delay(startup_delay);
    }

    // Check if we have a native surface we can use
    // If we have to lock the screen, draw to a buffer and copy
    // Likewise if the screen pitch is not the same as the width
    // If we have to multiply, drawing is done to a separate 320x200 buf

    native_surface = !SDL_MUSTLOCK(screen) 
                  && screen_mode == &mode_scale_1x
                  && screen->pitch == SCREENWIDTH
                  && aspect_ratio_correct;

    // If not, allocate a buffer and copy from that buffer to the 
    // screen when we do an update

    if (native_surface)
    {
	screens[0] = (unsigned char *) screen->pixels;

        screens[0] += (screen->h - SCREENHEIGHT) / 2;
    }
    else
    {
	screens[0] = (unsigned char *) Z_Malloc (SCREENWIDTH * SCREENHEIGHT, 
                                                 PU_STATIC, NULL);
    }

    // "Loading from disk" icon

    LoadDiskImage();

    // Clear the screen to black.

    memset(screens[0], 0, SCREENWIDTH * SCREENHEIGHT);

    // We need SDL to give us translated versions of keys as well

    SDL_EnableUNICODE(1);

    // Repeat key presses - this is what Vanilla Doom does
    // Not sure about repeat rate - probably dependent on which DOS
    // driver is used.  This is good enough though.

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    // clear out any events waiting at the start and center the mouse
  
    while (SDL_PollEvent(&dummy));

    if (usemouse && !nomouse && (fullscreen || grabmouse))
    {
        CenterMouse();
    }

    initialized = true;
}