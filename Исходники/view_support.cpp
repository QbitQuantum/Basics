///initialize GLUT
bool init_glut()
{
  static int argc = 1;
  static const char* argv[1] = { "x" };

  //prepare GLUT environment
  if (!glut_initialized) {
    glutInit(&argc, (char**) argv);
    glut_initialized = true;
  }
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ACCUM);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

  //obtain other parameters
#ifdef WIN32
  double_click_delay_ms = GetDoubleClickTime();
#endif

  return true;
}