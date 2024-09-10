DWORD RedirectStdIO(LPSTR pszCommandLine,
                    fnWriteStdIn pfnWriteStdIn,
                    fnReadStdOutErr pfnReadStdOut,
                    fnReadStdOutErr pfnReadStdErr,
                    DWORD* pdwReturnCode,
                    LPVOID lpUser,
                    DWORD dwDefaultBufferSize,
                    WORD wShowWindow
                   )
{
  RedirStdIOContext context;
  ZeroMemory(&context, sizeof(RedirStdIOContext));

  context.pfnWriteStdIn = pfnWriteStdIn;
  context.pfnReadStdOut = pfnReadStdOut;
  context.pfnReadStdErr = pfnReadStdErr;
  context.lpUser = lpUser;

  SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

  context.dwBufferSize = dwDefaultBufferSize;
  // デフォルトバッファサイズ
  if(context.dwBufferSize <= 0) context.dwBufferSize = BUFFER_SIZE;

  // パイプ作りまくり
  CreatePipe(&context.StdIn.hRead, &context.StdIn.hWrite, &sa, context.dwBufferSize);
  DuplicateHandle(GetCurrentProcess(), context.StdIn.hWrite, GetCurrentProcess(), &context.hStdInWritePipeDup, 0, FALSE, DUPLICATE_SAME_ACCESS);
  CloseHandle(context.StdIn.hWrite);
  CreatePipe(&context.StdOut.hRead, &context.StdOut.hWrite, &sa, context.dwBufferSize);
  CreatePipe(&context.StdErr.hRead, &context.StdErr.hWrite, &sa, context.dwBufferSize);

  STARTUPINFO si = { sizeof(STARTUPINFO) };

  si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
  si.wShowWindow = wShowWindow;
  si.hStdInput = context.StdIn.hRead;
  si.hStdOutput = context.StdOut.hWrite;
  si.hStdError = context.StdErr.hWrite;

  PROCESS_INFORMATION pi;
  // れっつ起動
  BOOL r = CreateProcess(NULL, pszCommandLine, &sa, NULL, TRUE, DETACHED_PROCESS | CREATE_NO_WINDOW,
                         NULL, NULL, &si, &pi);
  if(r)
  {
    // 入力待ちに入るまで待っててやる
    WaitForInputIdle(pi.hProcess, WAIT_FOR_READY);

    // stdin 不要なら先に閉じてしまう
    if(!context.pfnWriteStdIn)
      CloseHandle(context.hStdInWritePipeDup);

    // 転送用バッファ。
    context.pbyBuffer = new BYTE[context.dwBufferSize];

    DWORD dwRet;
    do
    {
      // ポンプを動かす
      if(!PumpPipe(&context))
        break;
      dwRet = WaitForSingleObject(pi.hProcess, WAIT_FOR_RUN);
    }while(dwRet != WAIT_OBJECT_0); // ターゲットプロセスが生きている間

    DWORD dwBytesInStdOut = 0, dwBytesInStdErr = 0;
    while(1)
    {
      BOOL r;
      r = PeekNamedPipe(context.StdOut.hRead, NULL, 0, NULL, &dwBytesInStdOut, NULL);
      r = r && PeekNamedPipe(context.StdErr.hRead, NULL, 0, NULL, &dwBytesInStdErr, NULL);
      if(!r || (!dwBytesInStdOut && !dwBytesInStdErr))
        break;
      PumpPipe(&context);             // 書き残し、読み残しはないか？
      Sleep(WAIT_FOR_RUN);
    }

    delete[] context.pbyBuffer;

    // 終了コード
    if(pdwReturnCode) GetExitCodeProcess(pi.hProcess, pdwReturnCode);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
  }
  // 後始末
  CloseHandle(context.StdIn.hRead);
  CloseHandle(context.StdOut.hRead); CloseHandle(context.StdOut.hWrite);
  CloseHandle(context.StdErr.hRead); CloseHandle(context.StdErr.hWrite);

  return r;
}