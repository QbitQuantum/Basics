void close() {
  //Free loaded images
  gPressTexture.free();
  gUpTexture.free();
  gDownTexture.free();
  gLeftTexture.free();
  gRightTexture.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}