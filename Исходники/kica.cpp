void gl_onKeyboard(unsigned char key, int x, int y)
{
  XnUInt16 nUser = 16;
  XnUserID users[16];
  
  switch(key){
  case 27:
    gContext.Shutdown();
    exit(1);
    break;
  case 'c':
    gUserGenerator.GetUsers(users, nUser);
    if(nUser == 0){
      fprintf(stderr, "cannot find user\n");
    }else if(capture->start(*std::min_element(users, &users[nUser]))){
      fprintf(stderr, "start recording\n");
    }
    break;
  case 's':
    if(capture->stop()){
      fprintf(stderr, "stop recording\n");
    }
    break;
  }
}