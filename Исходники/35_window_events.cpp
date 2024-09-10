void close()
{
    //Free loaded images
    gSceneTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    gWindow.free();

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}