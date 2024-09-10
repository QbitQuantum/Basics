int
wmain(void) {
    uint64 PerfCountFrequency = SDL_GetPerformanceFrequency();
    SDL_Event Event;
    SDL_Window *Window;
    SDL_Renderer *Renderer;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0) {
        char *Error = "Could not initialize SDL: %s\n";
        printf(Error, SDL_GetError());

        return -1;
    }

    atexit(SDL_Quit);

    int WindowWidth = 1300;
    int WindowHeight = 870;
    int BytesPerPixel = 4;

    Window = SDL_CreateWindow("Echelon",
                              30, 30,
                              WindowWidth, WindowHeight,
                              SDL_WINDOW_RESIZABLE);
    
    if(Window) {
        Renderer = SDL_CreateRenderer(Window, -1, 0);

        if(Renderer) {
            GlobalRunning = true;
            window_dimensions Dimensions = SDLGetWindowDimensions(Window);
            SDLCreateNewTexture(&GlobalBuffer,
                                Renderer,
                                Dimensions.Width, Dimensions.Height,
                                BytesPerPixel);

            uint64 LastCounter = SDL_GetPerformanceCounter();
            uint64 LastCycleCount = __rdtsc();

            real64 DebugTimer = 0;
            real64 FPSTimer = 0;
            real64 UpdateTimer = 0;

            uint32 FPS = 0;
            uint32 UPS = 0;
            
            keyboard_input KeyboardInput = {};
            gamepad_input GamePadInput = {};

            game_code Game = LoadGameCode();

            game_memory GameMemory = {0};
            GameMemory.IsInitialized = false;
            GameMemory.PlayRumble = SDLPlayRumble;
            GameMemory.WindowDimensions = SDLGetWindowDimensions(Window);
            GameMemory.PermanentStorageSize = Gigabytes(4);
            GameMemory.PermanentStorage = VirtualAlloc(0,
                                                       GameMemory.PermanentStorageSize,
                                                       MEM_COMMIT, PAGE_READWRITE);

            //Assert((GameMemory.PermanentStorageSize));
            
            GameMemory.TransientStorageSize = Megabytes(4);
            GameMemory.TransientStorage = VirtualAlloc(0,
                                                       GameMemory.TransientStorageSize,
                                                       MEM_COMMIT, PAGE_READWRITE);
            //Assert((GameMemory.TransientStorageSize));

            Game.GameInit(&GameMemory);
            
            while(GlobalRunning) {
                // NOTE(Redab): This needs to while loop because we need
                // to handle events as long as they are available.
                while(SDL_PollEvent(&Event)) {
                    SDLHandleEvent(&Event, &Dimensions);
                    SDLHandleUserInput(&Event, &Game, &GameMemory, &KeyboardInput, &GamePadInput);
                }

                uint64 EndCycleCount = __rdtsc();
                uint64 EndCounter = SDL_GetPerformanceCounter();
                uint64 CounterElapsed = EndCounter - LastCounter;
                uint64 CyclesElapsed = EndCycleCount - LastCycleCount;

                // NOTE(Redab): CounterElapsed Contains the number of
                // clock cycles since last check. So we need to divide
                // this by the number of cycles per second which we
                // have in PerCountFrequency. Multiplied by 1000 to
                // get milliseconds.

                real64 SecondsPerFrame = ((real64)CounterElapsed / (real64)PerfCountFrequency);
                real64 MSPerFrame = SecondsPerFrame * 1000.0f;
                
                real64 KCPF = ((real64)CyclesElapsed / (1000.0f));

                FPSTimer += MSPerFrame;
                UpdateTimer += MSPerFrame;
                DebugTimer += MSPerFrame;

                if(UpdateTimer >= (1000.0f / 60.0f)) {
                    GameMemory.WindowDimensions = Dimensions;                        
                    Game.GameUpdate(&GameMemory, &KeyboardInput, &GamePadInput, UpdateTimer / 1000.0f);

                    UPS++;
                    UpdateTimer = 0;
                }

                if(FPSTimer >= (1000.0f / 60.0f)) {
                    SDLGameRender(&GlobalBuffer, &Game);
                    SDLBlitFrameToWindow(&GlobalBuffer, Renderer);
                    SDL_RenderPresent(Renderer); // Flip
                    
                    FPS++;
                    FPSTimer = 0;
                }
                
                if(DebugTimer >= 1000.0f) {
                    printf("%.05fms/f, FPS: %d, UPS: %d, %.02fKc/f, Timer: %.02f\n",
                           MSPerFrame, FPS, UPS, KCPF, DebugTimer);

                    FPS = 0;
                    UPS = 0;
                    DebugTimer = 0;
                }

                LastCycleCount = EndCycleCount;
                LastCounter = EndCounter;
            }
        } else {
            printf("Failed to create SDL_Renderer: %s\n", SDL_GetError());
        }
    } else {
        printf("Failed to create SDL_Window: %s\n", SDL_GetError());
    }

    SDL_CloseAudio();
    SDL_Quit();
    return 0;
}