int Execute(HANDLE hPlugin,char *CmdStr,int HideOutput,int Silent,int ShowTitle,char *ListFileName)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  int ExitCode,ExitCode2,LastError;

  memset(&si,0,sizeof(si));
  si.cb=sizeof(si);

  HANDLE hChildStdoutRd,hChildStdoutWr;
  HANDLE StdInput=GetStdHandle(STD_INPUT_HANDLE);
  HANDLE StdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE StdError=GetStdHandle(STD_ERROR_HANDLE);
  HANDLE hScreen=NULL;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (HideOutput)
  {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 32768))
    {
      if (Silent)
      {
        /*hScreen=Info.SaveScreen(0,0,-1,0);
        Info.Text(2,0,LIGHTGRAY,GetMsg(MWaitForExternalProgram))*/;
      }
      else
      {
        hScreen=Info.SaveScreen(0,0,-1,-1);
        const char *MsgItems[]={"",GetMsg(MWaitForExternalProgram)};
        Info.Message(Info.ModuleNumber,0,NULL,MsgItems,
                      ARRAYSIZE(MsgItems),0);
      }
      SetStdHandle(STD_OUTPUT_HANDLE,hChildStdoutWr);
      SetStdHandle(STD_ERROR_HANDLE,hChildStdoutWr);
    }
    else
      HideOutput=FALSE;
  }
  else
  {
    Info.Control(hPlugin, FCTL_GETUSERSCREEN, NULL);
    GetConsoleScreenBufferInfo(StdOutput, &csbi);
    COORD C = { 0, csbi.dwCursorPosition.Y };
    SetConsoleCursorPosition(StdOutput, C);
  }


  DWORD ConsoleMode;
  GetConsoleMode(StdInput,&ConsoleMode);
  SetConsoleMode(StdInput,ENABLE_PROCESSED_INPUT|ENABLE_LINE_INPUT|
                 ENABLE_ECHO_INPUT|ENABLE_MOUSE_INPUT);

  char ExpandedCmd[MAX_COMMAND_LENGTH];
  ExpandEnvironmentStrings(CmdStr,ExpandedCmd,sizeof(ExpandedCmd));
  FSF.LTrim(ExpandedCmd); //$ AA 12.11.2001

  char SaveTitle[512];
  GetConsoleTitle(SaveTitle,sizeof(SaveTitle));
  if (ShowTitle)
    SetConsoleTitle(ExpandedCmd);

  /* $ 14.02.2001 raVen
     делать окошку minimize, если в фоне */
  if (Opt.Background)
  {
    si.dwFlags=si.dwFlags | STARTF_USESHOWWINDOW;
    si.wShowWindow=SW_MINIMIZE;
  }
  /* raVen $ */

  ExitCode2=ExitCode=CreateProcess(NULL,ExpandedCmd,NULL,NULL,HideOutput,
            (Opt.Background?CREATE_NEW_CONSOLE:0)|PriorityProcessCode[Opt.PriorityClass],
            NULL,NULL,&si,&pi);

  LastError=!ExitCode?GetLastError():0;
  if (HideOutput)
  {
    SetStdHandle(STD_OUTPUT_HANDLE,StdOutput);
    SetStdHandle(STD_ERROR_HANDLE,StdError);
    CloseHandle(hChildStdoutWr);
  }

  SetLastError(LastError);
  if(!ExitCode2 /*|| !FindExecuteFile(ExecuteName,NULL,0)*/) //$ 06.03.2002 AA
  {
    char Msg[100];
    char ExecuteName[NM];
    lstrcpyn(ExecuteName,ExpandedCmd+(*ExpandedCmd=='"'), NM);
    char *Ptr;
    Ptr=strchr(ExecuteName,(*ExpandedCmd=='"')?'"':' ');
    if(Ptr)
      *Ptr=0;
    FindExecuteFile(ExecuteName,NULL,0);

    char NameMsg[NM];
    FSF.TruncPathStr(lstrcpyn(NameMsg,ExecuteName,sizeof(NameMsg)),MAX_WIDTH_MESSAGE);
    FSF.sprintf(Msg,GetMsg(MCannotFindArchivator),NameMsg);
    const char *MsgItems[]={GetMsg(MError),Msg, GetMsg(MOk)};
    Info.Message(Info.ModuleNumber,FMSG_WARNING|FMSG_ERRORTYPE,
                 NULL,MsgItems,ARRAYSIZE(MsgItems),1);
    ExitCode=RETEXEC_ARCNOTFOUND;
  }

  if (ExitCode && ExitCode!=RETEXEC_ARCNOTFOUND)
  {
    if (HideOutput)
    {
      WaitForSingleObject(pi.hProcess,1000);

      char PipeBuf[32768];
      DWORD Read;
      while (ReadFile(hChildStdoutRd,PipeBuf,sizeof(PipeBuf),&Read,NULL))
        ;
      CloseHandle(hChildStdoutRd);
    }
    /* $ 13.09.2000 tran
       фоновой выполнение */
    if ( !Opt.Background )
    {
        WaitForSingleObject(pi.hProcess,INFINITE);
        GetExitCodeProcess(pi.hProcess,(LPDWORD)&ExitCode);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
    else
    {
        StartThreadForKillListFile(&pi,ListFileName); // нехай за процессом тред следит, и файл бъет тапком
        ExitCode=0;
    }
    /* tran 13.09.2000 $ */
  }
  SetConsoleTitle(SaveTitle);
  SetConsoleMode(StdInput,ConsoleMode);
  if (!HideOutput)
  {
    Info.Control(hPlugin,FCTL_SETUSERSCREEN,NULL);
  }
  if (hScreen)
  {
    Info.RestoreScreen(NULL);
    Info.RestoreScreen(hScreen);
  }

  return ExitCode;
}