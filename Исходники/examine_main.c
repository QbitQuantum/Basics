static int
exm_dll_inject(Exm *exm)
{
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;
    HANDLE              process;
    HANDLE              remote_thread;
    LPVOID              remote_string;
    DWORD               exit_code; /* actually the base address of the mapped DLL */

    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    printf(" * creating child process %s... ", exm->filename);
    if (!CreateProcess(NULL, exm->filename, NULL, NULL, TRUE,
                       CREATE_SUSPENDED, NULL, NULL, &si, &pi))
    {
        printf("failed\n * can't spawn child process %s\n", exm->filename);
        return 0;
    }
    printf("done\n");

    printf(" * waiting for the child process to initialize... ");
    if (!WaitForInputIdle(pi.hProcess, INFINITE))
    {
        printf("failed\n * no process for %s\n", exm->filename);
        goto close_handles;
    }
    printf("done\n");

    printf(" * opening child process... ");
    process = OpenProcess(CREATE_THREAD_ACCESS, FALSE, pi.dwProcessId);
    if (!process)
    {
        printf("failed\n * no process for %s\n", exm->filename);
        goto close_handles;
    }
    printf("done\n");

    printf(" * mapping process handle 0x%p... ", pi.hProcess);
    exm->map_process.handle = CreateFileMapping(INVALID_HANDLE_VALUE,
                                                NULL, PAGE_READWRITE, 0, sizeof(HANDLE),
                                                "shared_process_handle");
    if (!exm->map_process.handle)
    {
        printf("failed\n");
        goto close_process;
    }

    exm->map_process.base = MapViewOfFile(exm->map_process.handle, FILE_MAP_WRITE,
                                          0, 0, sizeof(HANDLE));
    if (!exm->map_process.base)
    {
        printf("failed\n");
        goto close_process_handle;
    }

    CopyMemory(exm->map_process.base, &pi.hProcess, sizeof(HANDLE));
    printf("done\n");

    printf(" * allocating virtual memory... ");
    remote_string = VirtualAllocEx(process, NULL, exm->dll_length, MEM_COMMIT, PAGE_READWRITE);
    if (!remote_string)
    {
        printf("failed\n");
        goto unmap_process_handle;
    }
    printf("done\n");

    printf(" * writing process in virtual memory... ");
    if (!WriteProcessMemory(process, remote_string, exm->dll_fullname, exm->dll_length, NULL))
    {
        printf("failed\n");
        goto virtual_free;
    }
    printf("done\n");

    printf(" * execute thread... ");
    remote_thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)exm->ll, remote_string, 0, NULL);
    if (!remote_thread)
    {
        printf("failed\n");
        goto virtual_free;
    }
    printf("done\n");

    WaitForSingleObject(remote_thread, INFINITE);

    printf(" * getting exit code... ");
    if (!GetExitCodeThread(remote_thread, &exit_code))
    {
        printf("failed\n");
        goto close_thread;
    }
    printf("done\n");

    CloseHandle(remote_thread);
    VirtualFreeEx(process, remote_string, 0, MEM_RELEASE);

    printf(" * resume child process\n");
    ResumeThread(pi.hThread);

    exm->child.process1 = pi.hProcess;
    exm->child.thread = pi.hThread;
    exm->child.process2 = process;
    exm->exit_code = exit_code;

    return 1;

  close_thread:
    CloseHandle(remote_thread);
  virtual_free:
    VirtualFreeEx(process, remote_string, 0, MEM_RELEASE);
  unmap_process_handle:
    UnmapViewOfFile(exm->map_process.base);
  close_process_handle:
    CloseHandle(exm->map_process.handle);
  close_process:
    CloseHandle(process);
  close_handles:
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}