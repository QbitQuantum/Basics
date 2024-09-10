void close() {
  //Free loaded images
  gSplashTexture.free();

  //Close game controller with haptics
  SDL_HapticClose( gControllerHaptic );
  SDL_JoystickClose( gGameController );
  gGameController = NULL;
  gControllerHaptic = NULL;

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}