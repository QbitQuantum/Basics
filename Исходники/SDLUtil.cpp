bool SDLwindow::oneStep()
{
    if (!initialized){
        // init() must be executed in the thread where draw() is called
        init();
    }
    double startT = SDL_GetTicks();
    if (!processEvents()) return false;
    draw();
    swapBuffers();
    double dt = SDL_GetTicks() - startT;
    if (dt < 1000.0/30){
        SDL_Delay(1000.0/30 - dt);
    }
    return true;
}