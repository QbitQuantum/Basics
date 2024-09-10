int main(void) {

    PlatformState state;
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDLInputContext sdlIC;
    SDLSoundRingBuffer srb;
    GameSoundOutput sb;
    GameMemory gameMemory;

    //controller input state
    InputContext inputStates[2]; //contains old and new state
    InputContext* newInputState = &inputStates[0];
    InputContext* oldInputState = &inputStates[1];
    real32_t secsSinceLastFrame = 0;


    sb.volume = 2500;

    gameMemory.permanentStorageSize = MB(64);
    gameMemory.transientStorageSize = MB(64);
    state.gameMemorySize = gameMemory.transientStorageSize + gameMemory.permanentStorageSize;
    state.memoryBlock = mmap(nullptr, state.gameMemorySize, PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_PRIVATE ,
            -1,
            0);
    gameMemory.permanentStorage = state.memoryBlock;
    gameMemory.transientStorage = (uint8_t*)(gameMemory.transientStorage) + gameMemory.transientStorageSize;


    initSDL(&window, &renderer, &gOsb, &sdlIC, &srb);

    GameCode gameCode = loadGameCode();

    assert(gameCode.guarf);

    uint64_t startCount = SDL_GetPerformanceCounter();
    real32_t targetFrameSeconds = 1./getRefreshRate(window);

    SDL_PauseAudio(0);
    while(state.running) {

        if(getCreateTimeOfFile(GAME_LIB_PATH) != gameCode.dateLastModified) {
            reloadGameCode(&gameCode);
        }

        //keyboard input
        ControllerInput* newKeyInput = getContoller(newInputState, 0);

        //TODO: figure out why this is special
        ControllerInput* oldKeyInput = getContoller(oldInputState, 0);
        *newKeyInput = {};

        for(size_t i = 0; i < ARRAY_SIZE(oldKeyInput->buttons); i++) {
            newKeyInput->buttons[i] = oldKeyInput->buttons[i];
        }
        while(SDL_PollEvent(&e)) {
            processEvent(&e, newInputState, &state);
        }


        //controller input
        for(int i = 0; i < MAX_SDL_CONTROLLERS; i++) {
            if(sdlIC.controllers[i] != nullptr && SDL_GameControllerGetAttached(sdlIC.controllers[i])) {

                ControllerInput* newCIState = getContoller(newInputState, i+1);
                ControllerInput* oldCIState = getContoller(oldInputState, i+1);


                int16_t xVal = SDL_GameControllerGetAxis(sdlIC.controllers[i], SDL_CONTROLLER_AXIS_LEFTX);
                int16_t yVal = SDL_GameControllerGetAxis(sdlIC.controllers[i], SDL_CONTROLLER_AXIS_LEFTY);

                newCIState->avgX = normalizeStickInput(xVal, LEFT_THUMB_DEADZONE);
                newCIState->avgY = normalizeStickInput(yVal, LEFT_THUMB_DEADZONE);

                if(newCIState->avgX != 0 || newCIState->avgY != 0) {
                    newCIState->isAnalog = true;
                }

                processControllerButtonInput(&newCIState->actionDown, &oldCIState->actionDown, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_A);
                processControllerButtonInput(&newCIState->actionUp, &oldCIState->actionUp, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_Y);
                processControllerButtonInput(&newCIState->actionLeft, &oldCIState->actionLeft, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_X);
                processControllerButtonInput(&newCIState->actionRight, &oldCIState->actionRight, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_B);

                processControllerButtonInput(&newCIState->directionDown, &oldCIState->directionDown, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
                processControllerButtonInput(&newCIState->directionUp, &oldCIState->directionUp, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_DPAD_UP);
                processControllerButtonInput(&newCIState->directionLeft, &oldCIState->directionLeft, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
                processControllerButtonInput(&newCIState->directionRight, &oldCIState->directionRight, &newCIState->isAnalog, sdlIC.controllers[i], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

                oldCIState->isAnalog = newCIState->isAnalog;


            }
            else {
                //TODO: Logging
            }
        }


        //TODO: Do this instead of processing input, not after
        //process recording/playback
        assert(!(state.isRecording && state.isPlayingBack));

        if(state.isRecording) {
            recordInput(newInputState, state.inputRecordFile);
        }

        if(state.isPlayingBack) {
            playInput(newInputState, state.inputRecordFile);
        }

        //calculate audio buffers' indicies and sizes
        SDL_LockAudioDevice(1);
        uint32_t startIndex = srb.runningIndex % ARRAY_SIZE(srb.samples);
        uint32_t endIndex = (srb.sampleToPlay + SOUND_LATENCY) % ARRAY_SIZE(srb.samples);
        uint32_t samplesToGetFromGame = (startIndex <= endIndex) ? endIndex - startIndex : (ARRAY_SIZE(srb.samples) - startIndex) + endIndex; 
        sb.numSamples = samplesToGetFromGame;
        SDL_UnlockAudioDevice(1);



        gameCode.guarf(&gameMemory, &gOsb, &sb, newInputState, secsSinceLastFrame);

        updateSDLSoundBuffer(&srb, &sb, startIndex, endIndex);
        updateWindow(window, gTexture);

        InputContext* temp = newInputState;
        newInputState = oldInputState;
        oldInputState = temp;

        //benchmark stuff

        real32_t secsElapsed = secondsForCountRange(startCount, SDL_GetPerformanceCounter());

        //sleep to lock frame rate
        if(secsElapsed < targetFrameSeconds) {


            //NOTE: .5 denotes the amount we will spin manually since
            //      SDL_Delay is not 100% accurate
            real32_t timeToSleep = (targetFrameSeconds - secsElapsed)*1000 - .5;
            SDL_Delay(timeToSleep);
            secsElapsed = secondsForCountRange(startCount, SDL_GetPerformanceCounter());
            
            //This assert will fire if the window is moved
            //assert(secondsForCountRange(startCount, SDL_GetPerformanceCounter()) < targetFrameSeconds); 
            
            while(secondsForCountRange(startCount, SDL_GetPerformanceCounter()) < targetFrameSeconds) {
                //wait
            }
            secsElapsed = secondsForCountRange(startCount, SDL_GetPerformanceCounter());
        }
        uint64_t endCount = SDL_GetPerformanceCounter();
        real32_t fpsCount =  ((1./secsElapsed));
        real32_t mcPerFrame = (real32_t)(endCount-startCount) / (1000 * 1000 );


        printf("TPF: %.2fms FPS: %.2f MCPF: %.2f\n", secsElapsed*1000, fpsCount, mcPerFrame);

        startCount = endCount;
        secsSinceLastFrame = secsElapsed;
    }

    cleanUp(&state, &gameCode);
    return 0;
}