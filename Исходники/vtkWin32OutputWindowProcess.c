/* Function to setup remote process that waits for this process to
   exit and then deletes its executable.  */
static int SelfDelete()
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);

  /* Create a process using the explorer executable but suspend it
     immediately.  */
  if(CreateProcess(0, _T("explorer.exe"), 0, 0, 0,
                   (CREATE_SUSPENDED | IDLE_PRIORITY_CLASS),
                   0, 0, &si, &pi))
    {
    /* Structure to store code and data to copy to remote process.  */
    SelfDeleteRemoteCode code;

    DWORD oldProtect;
    CONTEXT context;
    DWORD entryPoint;

    /* Setup pointers to kernel functions for the remote code to call.  */
    code.fnWaitForSingleObject  = WaitForSingleObject;
    code.fnCloseHandle          = CloseHandle;
    code.fnDeleteFile           = DeleteFile;
    code.fnSleep                = Sleep;
    code.fnExitProcess          = ExitProcess;
    code.fnGetLastError         = GetLastError;

    /* Give the remote process a copy of our own process handle.  */
    DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(),
                    pi.hProcess, &code.hParent, 0, FALSE, 0);

    /* Store the file name of this process's executable.  */
    GetModuleFileName(0, code.szFileName, MAX_PATH);

    /* Store the binary code to execute remotely.  */
    memcpy(code.opCodes, SelfDeleteRemoteThread, SELF_DELETE_CODESIZE);

    /* Allocate some space on process's stack and place our
       SelfDeleteRemoteCode structure there.  Then set the instruction
       pointer to this location and let the process resume.  */
    context.ContextFlags = (CONTEXT_INTEGER | CONTEXT_CONTROL);
    GetThreadContext(pi.hThread, &context);

    /* Allocate space on stack that is aligned to cache-line boundary.  */
    entryPoint = (context.Esp - sizeof(SelfDeleteRemoteCode)) & ~0x1F;

    /* Place a pointer to the structure at the bottom-of-stack.  This
       pointer is located in such a way that it becomes the
       SelfDeleteRemoteThread's first argument.  */
    code.Arg0 = (SelfDeleteRemoteCode*)entryPoint;

    /* Set dummy return address for remote thread.  It will never return.  */
    context.Esp = entryPoint - 4;

    /* Set remote thread to execute the opCodes we copy to the process.  */
    context.Eip = entryPoint + (((char*)&code.opCodes) - ((char*)&code));

    /* Copy the code and data to the remote process entry point.  */
    VirtualProtectEx(pi.hProcess, (PVOID)entryPoint, sizeof(code),
                     PAGE_EXECUTE_READWRITE, &oldProtect);
    WriteProcessMemory(pi.hProcess, (PVOID)entryPoint, &code, sizeof(code), 0);

    /* Make sure the new code will be loaded.  */
    FlushInstructionCache(pi.hProcess, (PVOID)entryPoint, sizeof(code));

    /* Set the remote thread to execute at our entry point.  */
    SetThreadContext(pi.hThread, &context);

    /* Let the remote process continue.  It will block until this
       process exits.  */
    ResumeThread(pi.hThread);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 1;
    }

  return 0;
}