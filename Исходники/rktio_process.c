static intptr_t do_spawnv(rktio_t *rktio,
                          const char *command, int argc, const char * const *argv,
			  int exact_cmdline, intptr_t sin, intptr_t sout, intptr_t serr, int *pid,
			  int new_process_group, int chain_termination_here_to_child,
                          void *env, const char *wd)
{
  intptr_t i, l, len = 0;
  int use_jo;
  intptr_t cr_flag;
  char *cmdline;
  wchar_t *cmdline_w, *wd_w, *command_w;
  STARTUPINFOW startup;
  PROCESS_INFORMATION info;

  if (exact_cmdline) {
    cmdline = (char *)argv[1];
  } else {
    for (i = 0; i < argc; i++) {
      len += strlen(argv[i]) + 1;
    }

    cmdline = malloc(len);

    len = 0;
    for (i = 0; i < argc; i++) {
      l = strlen(argv[i]);
      memcpy(cmdline + len, argv[i], l);
      cmdline[len + l] = ' ';
      len += l + 1;
    }
    --len;
    cmdline[len] = 0;
  }

  memset(&startup, 0, sizeof(startup));
  startup.cb = sizeof(startup);
  startup.dwFlags = STARTF_USESTDHANDLES;
  startup.hStdInput = (HANDLE)sin;
  startup.hStdOutput = (HANDLE)sout;
  startup.hStdError = (HANDLE)serr;

  /* If none of the stdio handles are consoles, specifically
     create the subprocess without a console: */
  if (!rktio_system_fd_is_terminal(rktio, (intptr_t)startup.hStdInput)
      && !rktio_system_fd_is_terminal(rktio, (intptr_t)startup.hStdOutput)
      && !rktio_system_fd_is_terminal(rktio, (intptr_t)startup.hStdError))
    cr_flag = CREATE_NO_WINDOW;
  else
    cr_flag = 0;
  if (new_process_group)
    cr_flag |= CREATE_NEW_PROCESS_GROUP;
  cr_flag |= CREATE_UNICODE_ENVIRONMENT;

  use_jo = chain_termination_here_to_child;
  if (use_jo) {
    /* Use a job object to ensure that the new process will be terminated
       if this process ends for any reason (including a crash) */
    if (!rktio->process_job_object) {
      JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli;

      rktio->process_job_object = CreateJobObject(NULL, NULL);

      memset(&jeli, 0, sizeof(jeli));
      jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
      SetInformationJobObject(rktio->process_job_object,
			      JobObjectExtendedLimitInformation,
			      &jeli,
			      sizeof(jeli));
    }
  }

  
  cmdline_w = WIDE_PATH_copy(cmdline);
  if (!exact_cmdline)
    free(cmdline);
  wd_w = WIDE_PATH_copy(wd);
  command_w = WIDE_PATH_temp(command);

  if (cmdline_w
      && wd_w
      && command_w
      && CreateProcessW(command_w, cmdline_w, 
                        NULL, NULL, 1 /*inherit*/,
                        cr_flag, env, wd_w,
                        &startup, &info)) {
    if (use_jo)
      AssignProcessToJobObject(rktio->process_job_object, info.hProcess);
    CloseHandle(info.hThread);
    *pid = info.dwProcessId;
    free(cmdline_w);
    free(wd_w);
    return (intptr_t)info.hProcess;
  } else {
    if (cmdline_w) free(cmdline_w);
    if (wd_w) free(wd_w);
    return -1;
  }
}