int main(int argc, char *argv[])
{

  #ifdef __APPLE__ || __MACH__ || OSX
    glutInit(&argc,argv);
  #endif

  #ifdef LINUX
    setenv("__GL_SYNC_TO_VBLANK","1",true);
  #else
    // SDL console output hack
    freopen( "CON", "w", stdout );
  #endif


  /// configure the screen
  g_screen.setCaptionText("SDL EXAMPLE");
  g_screen.addFlags(SDL_SRCALPHA | SDL_ANYFORMAT | SDL_OPENGL);
//  g_screen.addFlags(SDL_FULLSCREEN);


  //Initialize
  if( g_screen.init() == false )
  {
      return 1;
  }


  // Init glew
  if (GLEW_OK != glewInit())
  {
    std::cout << "'glewInit()' failed." << std::endl;
    exit(0);
  }


  // some gl state calls
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_NORMALIZE);
  glDisable(GL_COLOR_MATERIAL);



  /// loading ...
  init();



  // main loop
  while (!g_input.getKeyState(SDLK_ESCAPE))
  {



      /// update event handler
      g_input.update();

      /// handle events
      checkEvents();


      if (g_frameDone == false)
      {
        /// render 3d content
        renderVolume();

        /// render 2d content
        render2d();


        glFlush();
        SDL_GL_SwapBuffers();
      }
  }


  // clean up sdl
  clean_up();



  return 0;
}