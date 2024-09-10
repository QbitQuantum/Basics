uint64 TZipIn::GetFLen(const TStr& ZipFNm) {
  #ifdef GLib_WIN
  HANDLE ZipStdoutRd, ZipStdoutWr;
  // create pipes
  SECURITY_ATTRIBUTES saAttr;
  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = NULL;
    // Create a pipe for the child process's STDOUT.
  const int PipeBufferSz = 32*1024;
  EAssertR(CreatePipe(&ZipStdoutRd, &ZipStdoutWr, &saAttr, PipeBufferSz), "Stdout pipe creation failed");
  // Ensure the read handle to the pipe for STDOUT is not inherited.
  SetHandleInformation(ZipStdoutRd, HANDLE_FLAG_INHERIT, 0);
  //CreateZipProcess(GetCmd(FNm), FNm);
  { const TStr CmdLine = TStr::Fmt("7z.exe l %s", ZipFNm.CStr());
  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION));
  ZeroMemory( &siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdOutput = ZipStdoutWr;
  siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
  // Create the child process.
  const BOOL FuncRetn = CreateProcess(NULL, (LPSTR) CmdLine.CStr(),
    NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo);
  EAssertR(FuncRetn!=0, TStr::Fmt("Can not execute '%s'", CmdLine.CStr()).CStr());
  CloseHandle(piProcInfo.hProcess);
  CloseHandle(piProcInfo.hThread); }
  #else
  const TStr CmdLine = TStr::Fmt("7za l %s", ZipFNm.CStr());
  FILE* ZipStdoutRd = popen(CmdLine.CStr(), "r");
  if (ZipStdoutRd == NULL) { // try using SevenZipPath
    ZipStdoutRd = popen((TZipIn::SevenZipPath+"/"+CmdLine).CStr(), "r");
  }
  EAssertR(ZipStdoutRd != NULL, TStr::Fmt("Can not execute '%s'", CmdLine.CStr()).CStr());
  #endif
  // Read output from the child process
  const int BfSz = 32*1024;
  char* Bf = new char [BfSz];
  int BfC=0, BfL=0;
  memset(Bf, 0, BfSz);
  #ifdef GLib_WIN
  DWORD BytesRead;
  EAssert(ReadFile(ZipStdoutRd, Bf, MxBfL, &BytesRead, NULL) != 0);
  #else
  size_t BytesRead = fread(Bf, 1, MxBfL, ZipStdoutRd);
  EAssert(BytesRead != 0);
  EAssert(pclose(ZipStdoutRd) != -1);
  #endif
  BfL = (int) BytesRead;  IAssert((BfC!=0)||(BfL!=0));
  BfC = 0; Bf[BfL] = 0;
  // find file lenght
  TStr Str(Bf);  delete [] Bf;
  TStrV StrV; Str.SplitOnWs(StrV);
  int n = StrV.Len()-1;
  while (n > 0 && ! StrV[n].IsPrefix("-----")) { n--; }
  if (n-7 <= 0) {
    WrNotify(TStr::Fmt("Corrupt file %s: MESSAGE:\n", ZipFNm.CStr()).CStr(), Str.CStr());
    SaveToErrLog(TStr::Fmt("Corrupt file %s. Message:\n:%s\n", ZipFNm.CStr(), Str.CStr()).CStr());
    return 0;
  }
  return StrV[n-7].GetInt64();
}