pid_t
waitpid (pid_t pid, int *statusp, int options)
{
  return _cwait (statusp, pid, WAIT_CHILD);
}