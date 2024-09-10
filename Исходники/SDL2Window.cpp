bool SDL2Window::initialize() {

    arx_assert(!m_displayModes.empty());

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#if ARX_PLATFORM == ARX_PLATFORM_WIN32
    // Used on Windows to prevent software opengl fallback.
    // The linux situation:
    // Causes SDL to require visuals without caveats.
    // On linux some drivers only supply multisample capable GLX Visuals
    // with a GLX_NON_CONFORMANT_VISUAL_EXT caveat.
    // see: https://www.opengl.org/registry/specs/EXT/visual_rating.txt
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#endif

    // TODO EGL and core profile are not supported yet
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    if(gldebug::isEnabled()) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    }


    int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
    Uint32 windowFlags = getSDLFlagsForMode(m_size, m_fullscreen);
    windowFlags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

    for(int msaa = m_maxMSAALevel; msaa > 0; msaa--) {
        bool lastTry = (msaa == 1);

        // Cleanup context and window from previous tries
        if(m_glcontext) {
            SDL_GL_DeleteContext(m_glcontext);
            m_glcontext = NULL;
        }
        if(m_window) {
            SDL_DestroyWindow(m_window);
            m_window = NULL;
        }

        SDL_ClearError();

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, msaa > 1 ? 1 : 0);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa > 1 ? msaa : 0);

        m_window = SDL_CreateWindow(m_title.c_str(), x, y, m_size.x, m_size.y, windowFlags);
        if(!m_window) {
            if(lastTry) {
                LogError << "Could not create window: " << SDL_GetError();
                return false;
            }
            continue;
        }

        m_glcontext = SDL_GL_CreateContext(m_window);
        if(!m_glcontext) {
            if(lastTry) {
                LogError << "Could not create GL context: " << SDL_GetError();
                return false;
            }
            continue;
        }

        // Verify that the MSAA setting matches what was requested
        int msaaEnabled, msaaValue;
        SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &msaaEnabled);
        SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &msaaValue);
        if(!lastTry) {
            if(!msaaEnabled || msaaValue < msaa) {
                continue;
            }
        }
        if(msaaEnabled) {
            m_MSAALevel = msaaValue;
        } else {
            m_MSAALevel = 0;
        }

        // Verify that we actually got an accelerated context
        (void)glGetError(); // clear error flags
        GLint texunits = 0;
        glGetIntegerv(GL_MAX_TEXTURE_UNITS, &texunits);
        if(glGetError() != GL_NO_ERROR || texunits < GLint(m_minTextureUnits)) {
            if(lastTry) {
                LogError << "Not enough GL texture units available: have " << texunits
                         << ", need at least " << m_minTextureUnits;
                return false;
            }
            continue;
        }

        // All good
        const char * system = "(unknown)";
        {
            ARX_SDL_SysWMinfo info;
            info.version.major = 2;
            info.version.minor = 0;
            info.version.patch = 4;
            if(SDL_GetWindowWMInfo(m_window, reinterpret_cast<SDL_SysWMinfo *>(&info))) {
                switch(info.subsystem) {
                case ARX_SDL_SYSWM_UNKNOWN:
                    break;
                case ARX_SDL_SYSWM_WINDOWS:
                    system = "Windows";
                    break;
                case ARX_SDL_SYSWM_X11:
                    system = "X11";
                    break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
                case ARX_SDL_SYSWM_WINRT:
                    system = "WinRT";
                    break;
#endif
                case ARX_SDL_SYSWM_DIRECTFB:
                    system = "DirectFB";
                    break;
                case ARX_SDL_SYSWM_COCOA:
                    system = "Cocoa";
                    break;
                case ARX_SDL_SYSWM_UIKIT:
                    system = "UIKit";
                    break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
                case ARX_SDL_SYSWM_WAYLAND:
                    system = "Wayland";
                    break;
                case ARX_SDL_SYSWM_MIR:
                    system = "Mir";
                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
                case ARX_SDL_SYSWM_ANDROID:
                    system = "Android";
                    break;
#endif
                }
            }
        }

        int red = 0, green = 0, blue = 0, alpha = 0, depth = 0, doublebuffer = 0;
        SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red);
        SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green);
        SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue);
        SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha);
        SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depth);
        SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &doublebuffer);
        LogInfo << "Window: " << system << " r:" << red << " g:" << green << " b:" << blue
                << " a:" << alpha << " depth:" << depth << " aa:" << msaa << "x"
                << " doublebuffer:" << doublebuffer;
        break;
    }

    // Use the executable icon for the window
#if ARX_PLATFORM == ARX_PLATFORM_WIN32
    {
        SDL_SysWMinfo info;
        SDL_VERSION(&info.version);
        if(SDL_GetWindowWMInfo(m_window, &info) && info.subsystem == SDL_SYSWM_WINDOWS) {
            platform::WideString filename;
            filename.allocate(filename.capacity());
            while(true) {
                DWORD size = GetModuleFileNameW(NULL, filename.data(), filename.size());
                if(size < filename.size()) {
                    filename.resize(size);
                    break;
                }
                filename.allocate(filename.size() * 2);
            }
            HICON largeIcon = 0;
            HICON smallIcon = 0;
            ExtractIconExW(filename, 0, &largeIcon, &smallIcon, 1);
            if(smallIcon) {
                SendMessage(info.info.win.window, WM_SETICON, ICON_SMALL, LPARAM(smallIcon));
            }
            if(largeIcon) {
                SendMessage(info.info.win.window, WM_SETICON, ICON_BIG, LPARAM(largeIcon));
            }
        }
    }
#endif

    setVSync(m_vsync);

    SDL_ShowWindow(m_window);
    SDL_ShowCursor(SDL_DISABLE);

    m_renderer->initialize();

    onCreate();
    onToggleFullscreen(m_fullscreen);
    updateSize(true);

    onShow(true);
    onFocus(true);

    return true;
}