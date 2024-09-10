void processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            // alt + f4 handling
            if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT))
            {
                g_application.Terminate();
                break;
            }
            g_application.OnKeyPress( SDLKeyToKeyCode( event.key.keysym.sym ) );
            break;
        case SDL_KEYUP:
            g_application.OnKeyRelease(SDLKeyToKeyCode(event.key.keysym.sym));
            break;
        case SDL_MOUSEMOTION:
            g_application.OnMouseMove(event.motion.x, event.motion.y);
            break;
        case SDL_QUIT:
            g_application.Terminate();
            break;
            // window events      
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                g_application.OnWindowResize(event.window.data1, event.window.data2);
                break;
            }
            break;
        }
    }
}