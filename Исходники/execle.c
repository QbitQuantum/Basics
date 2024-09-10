int execle(const char *path, const char *argv0, ... /*, const char **envp */)
{
  scan_ptr();
  return spawnve(P_OVERLAY, path, (char *const *)&argv0, (char *const *)ptr);
}