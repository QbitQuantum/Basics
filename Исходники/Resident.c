static Bool _ExecuteProcess(MessageHandler *handler, ProcessNode *node) {
  char *module;
  int pid;
  int pAPR[2], pAPW[2], pDBR[2], pDBW[2];
  Bool rc;
  NETFILE *fpAPR, *fpAPW;
  char line[SIZE_BUFF], **cmd;

  if (handler->loadpath == NULL) {
    handler->loadpath = ExecPath;
  }
  signal(SIGPIPE, SignalHandler);
  module =
      ValueStringPointer(GetItemLongName(node->mcprec->value, "dc.module"));
  ExpandStart(line, handler->start, handler->loadpath, module, "");
  cmd = ParCommandLine(line);

  if (pipe(pAPR) != 0) {
    perror("pipe");
    exit(1);
  }
  if (pipe(pAPW) != 0) {
    perror("pipe");
    exit(1);
  }
  if (pipe(pDBR) != 0) {
    perror("pipe");
    exit(1);
  }
  if (pipe(pDBW) != 0) {
    perror("pipe");
    exit(1);
  }
  if (setjmp(SubError) == 0) {
    if ((pid = fork()) == 0) {
      dup2(pAPW[0], STDIN_FILENO);
      dup2(pAPR[1], STDOUT_FILENO);
      close(pAPW[0]);
      close(pAPW[1]);
      close(pAPR[0]);
      close(pAPR[1]);
      dup2(pDBW[0], DBIN_FILENO);
      dup2(pDBR[1], DBOUT_FILENO);
      close(pDBW[0]);
      close(pDBW[1]);
      close(pDBR[0]);
      close(pDBR[1]);
      execv(cmd[0], cmd);
    } else {
      fpAPR = FileToNet(pAPR[0]);
      close(pAPR[1]);
      fpAPW = FileToNet(pAPW[1]);
      close(pAPW[0]);
      fpDBR = FileToNet(pDBR[0]);
      close(pDBR[1]);
      fpDBW = FileToNet(pDBW[1]);
      close(pDBW[0]);
      StartDB(handler);
      PutApplication(handler, fpAPW, node);
      GetApplication(handler, fpAPR, node);
      (void)wait(&pid);
      CancelDB();
      signal(SIGPIPE, SIG_DFL);
      CloseNet(fpAPW);
      CloseNet(fpAPR);
      CloseNet(fpDBW);
      CloseNet(fpDBR);
    }
    rc = TRUE;
  } else {
    rc = FALSE;
  }
  return (rc);
}