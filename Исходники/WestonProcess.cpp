void
xt::Process::Child(const char *program,
                   char * const *options)
{
  ::signal(SIGUSR2, SIG_IGN);
  
  /* Unblock SIGUSR2 */
  sigset_t signalMask;
  sigemptyset(&signalMask);
  sigaddset(&signalMask, SIGUSR2);
  if (sigprocmask(SIG_UNBLOCK, &signalMask, NULL))
  {
    std::stringstream ss;
    ss << "sigprocmask: " << strerror(errno);
    throw std::runtime_error(ss.str());
  }
  
  if (!getenv("XBMC_WESTON_GTEST_CHILD_STDOUT"))
  {
    ::close(STDOUT_FILENO);
    ::close(STDERR_FILENO);
  }
  
  if (execvpe(program, options, environ) == -1)
  {
    std::stringstream ss;
    ss << "execvpe: " << strerror(errno);
    throw std::runtime_error(ss.str());
  }
}