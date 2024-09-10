void gl_onKeyboard(unsigned char key, int x, int y)
{
  switch(key){
  case 27:
    gContext.Shutdown();
    exit(1);
    break;
  case 't':
    setMainWindow((winMode == DEPTH_WINDOW)? IMAGE_WINDOW : DEPTH_WINDOW);
    break;
  }
}