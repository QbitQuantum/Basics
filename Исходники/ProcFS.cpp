FILE *ProcFS::OpenFILE(pid_t pid, char const *what, const char *mode) {
  return OpenFILE(pid, pid, what, mode);
}