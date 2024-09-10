/* return -1 for normal run or any other value as exitcode */
int win9x_process(int argc, char **argv)
{
  win9x_extend_service_name();

  if (service_flag != w32_noservice && !Is9x())
  {
    if (!quiet_flag)  AllocTempConsole();
    Log((quiet_flag?0:-1), "Can't operate witn Windows 9x services: incompatible OS type%s", quiet_flag?"":"\n");
    return 1;
  }

  switch(service_flag)
  {
  case w32_queryservice:                       /* service control */
  case w32_startservice:
  case w32_stopservice:
  case w32_restartservice:
    return !win9x_service_control();

  case w32_installservice:                     /* (un)install binkd9x service */
  case w32_uninstallservice:
    return !win9x_service_un_install(argc, argv);

  case w32_noservice:                          /* Run  binkd9x */
    quiet_flag = 1;
    return -1;

  case w32_run_as_service:                     /* Run  binkd9x as service */
    {
      char *tmp = NULL;
      unsigned char *path = NULL;
      int pathlen;
      HINSTANCE hl;
      HKEY hk;
      DWORD reg_type, size;

      tmp = win9x_make_Win9xRegParm(service_name);

      if (RegOpenKey(HKEY_LOCAL_MACHINE, tmp, &hk)==ERROR_SUCCESS)
      { /* extract current directory from registry */
        size = 0;
        if ((RegQueryValueEx(hk, Win9xRegParm_Path, NULL, &reg_type, NULL, &size)==ERROR_SUCCESS)&&(reg_type == REG_SZ))
        {
          path = (unsigned char *)malloc(size);
          if ((RegQueryValueEx(hk, Win9xRegParm_Path, NULL, &reg_type, path, &size) != ERROR_SUCCESS)||(reg_type != REG_SZ))
          {
            free(path); path = NULL;
          }
        }
        RegCloseKey(hk);
      }
      free(tmp);

      if (!path)
      { /* extract current directory from argv[0] */
        tmp = extract_filename(argv[0]);
        pathlen = tmp-argv[0];
        if (pathlen>0)
        {
          path = (unsigned char *)malloc(pathlen+1);
          memcpy(path, argv[0], pathlen);
          path[pathlen] = 0;
        }
      }

      if (path)
      {
        SetCurrentDirectory((char*)path);
        free(path);
      }

      hl = LoadLibrary("KERNEL32.DLL");
      if (hl != NULL)
      {
        RegisterServiceProcess = (RSPType)GetProcAddress(hl, "RegisterServiceProcess");
        if (RegisterServiceProcess!=NULL)
          if (RegisterServiceProcess(0, RSP_SIMPLE_SERVICE))
            w9x_service_reg = 1;
        FreeLibrary(hl);
      }
      quiet_flag = 1;
    }
    return -1;

  default:
    Log((quiet_flag?0:-1), "Unknown service control code (%i)\n", service_flag);
    return 1;
  }

  return -1;
}