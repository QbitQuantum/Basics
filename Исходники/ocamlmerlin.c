int main(int argc, char **argv)
{
  char result = 0;
  int err = 0;
  struct stat st;
#ifdef _WIN32
  HANDLE fds[3];
  ULONG pid;
  HANDLE hProcess, hServerProcess;
  DWORD dwNumberOfBytesRead;
  CHAR argv0[PATHSZ];
  GetModuleFileName(NULL, argv0, PATHSZ);
  compute_merlinpath(merlin_path, argv0, &st);
#else
  compute_merlinpath(merlin_path, argv[0], &st);
#endif
  if (argc >= 2 && strcmp(argv[1], "server") == 0)
  {
    IPC_SOCKET_TYPE sock;
    ssize_t len;
#ifdef _WIN32
    compute_socketname(socketname, eventname, merlin_path);
#else
    compute_socketname(socketname, &st);
#endif

    sock = connect_and_serve(socketname, eventname, merlin_path);
    len = prepare_args(argbuffer, sizeof(argbuffer), argc-2, argv+2);
#ifdef _WIN32
    hProcess = GetCurrentProcess();
    if (!GetNamedPipeServerProcessId(sock, &pid))
      failwith_perror("GetNamedPipeServerProcessId");
    hServerProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, pid);
    if (hServerProcess == INVALID_HANDLE_VALUE)
      failwith_perror("OpenProcess");
    if (!DuplicateHandle(hProcess, GetStdHandle(STD_INPUT_HANDLE), hServerProcess, &fds[0], 0, FALSE, DUPLICATE_SAME_ACCESS))
      failwith_perror("DuplicateHandle(stdin)");
    if (!DuplicateHandle(hProcess, GetStdHandle(STD_OUTPUT_HANDLE), hServerProcess, &fds[1], 0, FALSE, DUPLICATE_SAME_ACCESS))
      failwith_perror("DuplicateHandle(stdout)");
    CloseHandle(GetStdHandle(STD_OUTPUT_HANDLE));
    if (!DuplicateHandle(hProcess, GetStdHandle(STD_ERROR_HANDLE), hServerProcess, &fds[2], 0, FALSE, DUPLICATE_SAME_ACCESS))
      failwith_perror("DuplicateHandle(stderr)");
#else
    int fds[3] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };
#endif
    ipc_send(sock, argbuffer, len, fds);

#ifdef _WIN32
    if (ReadFile(sock, &result, 1, &dwNumberOfBytesRead, NULL) && dwNumberOfBytesRead == 1)
      err = 1;
#else
    NO_EINTR(err, read(sock, &result, 1));
#endif
    if (err == 1)
      exit(result);

    unexpected_termination(argc, argv);
  }
  else
  {
    argv[0] = ocamlmerlin_server;
    execvp(merlin_path, argv);
    failwith_perror("execvp(ocamlmerlin-server)");
  }
}