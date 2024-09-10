static pid_t
spawn_with_redir(const char *const *argv, int child_stdin, int child_stdout)
{
  fflush(0);
  pid_t child = fork();
  if (child == -1)
    fatal_perror("fork");
  if (child != 0)
    return child; /* to the parent */

  /* We are the child.  The parent has arranged for it to be safe for
     us to write to stderr under error conditions, but the cleanup
     handler should not do anything. */
  controller_cleanups = false;
  up_script_cleanups = false;

  /* Child-side stdin and stdout redirections. */
  if (child_stdin != 0) {
    if (close(0))
      fatal_perror("close");

    if (child_stdin < 0) {
      if (open("/dev/null", O_RDONLY) != 0)
        fatal_perror("open");
    } else {
      if (dup(child_stdin) != 0)
        fatal_perror("dup");
    }
  }

  if (child_stdout != 1) {
    if (close(1))
      fatal_perror("close");
    if (child_stdout < 1) {
      if (open("/dev/null", O_WRONLY) != 1)
        fatal_perror("open");
    } else {
      if (dup(child_stdout) != 1)
        fatal_perror("dup");
    }
  }

  become_only_root();

  if (sigprocmask(SIG_SETMASK, &child_sigmask, 0))
    fatal_perror("sigprocmask");

  execvpe(argv[0], (char *const *)argv, (char *const *)child_env);
  fatal_perror("execvpe");
}