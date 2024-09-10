static int mysystem(const char *command)
{
  int ret;
  STARTUPINFOA        si; //  = { sizeof(si)};
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi;
  char cmd[4096];

  //strcpy(cmd,command);
  ExpandEnvironmentStringsA(command,cmd,sizeof(cmd)-1);
  ret = (int) CreateProcessA( NULL, cmd
                           , NULL, NULL
                           , FALSE, CREATE_NO_WINDOW
                           , NULL, NULL
                           , &si, &pi);
  return ret;
}