int main( int argc, char *argv[] )
{
   glutInit( &argc, argv );
   glutInitWindowPosition( 200, 200 );
   glutInitWindowSize( 800, 500 );
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutCreateWindow("World of Awesome");
   glutReshapeFunc( ReshapeGL );
   glutDisplayFunc( Draw );
   glutKeyboardFunc( keyboard );
   glutMouseFunc( mouse );
   glutMotionFunc( mouseMove );
   glutPassiveMotionFunc( passiveMove );
   glutTimerFunc(TIMER_DELAY, tock, 0);

   g_width = g_height = 200;

#ifdef _WIN32 
   GLenum err = glewInit();
   if (GLEW_OK != err)
   {
      std::cerr << "Error initializing glew! " << glewGetErrorString(err) << std::endl;
      return 1;
   }
#endif
#ifdef __APPLE__
   glutSetCursor(GLUT_CURSOR_NONE); 
#endif

   backShade = glm::vec3(0.2,0.5,0.9);

   Initialize();
   
   //test the openGL version
   getGLversion();
   //install the shader
   if (!InstallShader(textFileRead((char *)"shaders/vert.glsl"), textFileRead((char *)"shaders/frag.glsl")))   {
      printf("Error installing shader!\n");
      return 0;
   }

   InitGeom();


   g_shadeType = PHONG;

   g_pitch = 0;
   g_yaw = M_PI / 2;
   float tx = cos(g_pitch)*cos(g_yaw);
   float ty = sin(g_pitch);
   float tz = cos(g_pitch)*cos(M_PI/2 - g_yaw);
   eye = glm::vec3(0, 2.5, 0);
   target = eye + glm::vec3(tx, ty, tz);
   sunDir = normalize(vec3(-0.2, -1.0, 0.0));


   sunShade = glm::vec3(1.0, 1.0, 0.9);

   glutMainLoop();
   return 0;
}