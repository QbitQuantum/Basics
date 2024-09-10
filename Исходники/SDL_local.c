int SDL_WM_CreateTempContext() {
  
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  if (SDL_GetWMInfo(&info) == -1) {
    // Could not get SDL version info.
    return 1;
  }
  
  temp_device = GetDC(info.window);

  temp_context = wglCreateContext(temp_device);
  if (temp_context == NULL) {
    // Could not create OpenGL context
    return 2;
  }

  if (!wglShareLists(info.hglrc, temp_context)) {
    // Could not share lists with temp context.
    return 3;
  }
  
  return 0;
  
}