void close() {
  //Free loadded images
  g_sceneTexture.free();
  
  //Destroy window
  SDL_DestroyRenderer(g_renderer);
  g_window.free();

  //Quit SDL subsystem
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}