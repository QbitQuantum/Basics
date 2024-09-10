/* Test each page.  */
static bool
TestPage(const char *pagelabel, uintptr_t pageaddr, int should_succeed)
{
  const char *oplabel;
  uintptr_t opaddr;

  bool failed = false;
  for (unsigned int test = 0; test < 3; test++) {
    switch (test) {
      // The execute test must be done before the write test, because the
      // write test will clobber memory at the target address.
    case 0: oplabel = "reading"; opaddr = pageaddr + PAGESIZE/2 - 1; break;
    case 1: oplabel = "executing"; opaddr = pageaddr + PAGESIZE/2; break;
    case 2: oplabel = "writing"; opaddr = pageaddr + PAGESIZE/2 - 1; break;
    default: abort();
    }

#ifdef _WIN32
    BOOL badptr;

    switch (test) {
    case 0: badptr = IsBadReadPtr((const void*)opaddr, 1); break;
    case 1: badptr = IsBadExecPtr(opaddr); break;
    case 2: badptr = IsBadWritePtr((void*)opaddr, 1); break;
    default: abort();
    }

    if (badptr) {
      if (should_succeed) {
        printf("TEST-UNEXPECTED-FAIL | %s %s\n", oplabel, pagelabel);
        failed = true;
      } else {
        printf("TEST-PASS | %s %s\n", oplabel, pagelabel);
      }
    } else {
      // if control reaches this point the probe succeeded
      if (should_succeed) {
        printf("TEST-PASS | %s %s\n", oplabel, pagelabel);
      } else {
        printf("TEST-UNEXPECTED-FAIL | %s %s\n", oplabel, pagelabel);
        failed = true;
      }
    }
#else
    pid_t pid = fork();
    if (pid == -1) {
      printf("ERROR | %s %s | fork=%s\n", oplabel, pagelabel,
             LastErrMsg());
      exit(2);
    } else if (pid == 0) {
      volatile unsigned char scratch;
      switch (test) {
      case 0: scratch = *(volatile unsigned char *)opaddr; break;
      case 1: JumpTo(opaddr); break;
      case 2: *(volatile unsigned char *)opaddr = 0; break;
      default: abort();
      }
      (void)scratch;
      _exit(0);
    } else {
      int status;
      if (waitpid(pid, &status, 0) != pid) {
        printf("ERROR | %s %s | wait=%s\n", oplabel, pagelabel,
               LastErrMsg());
        exit(2);
      }

      if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        if (should_succeed) {
          printf("TEST-PASS | %s %s\n", oplabel, pagelabel);
        } else {
          printf("TEST-UNEXPECTED-FAIL | %s %s | unexpected successful exit\n",
                 oplabel, pagelabel);
          failed = true;
        }
      } else if (WIFEXITED(status)) {
        printf("ERROR | %s %s | unexpected exit code %d\n",
               oplabel, pagelabel, WEXITSTATUS(status));
        exit(2);
      } else if (WIFSIGNALED(status)) {
        if (should_succeed) {
          printf("TEST-UNEXPECTED-FAIL | %s %s | unexpected signal %d\n",
                 oplabel, pagelabel, WTERMSIG(status));
          failed = true;
        } else {
          printf("TEST-PASS | %s %s | signal %d (as expected)\n",
                 oplabel, pagelabel, WTERMSIG(status));
        }
      } else {
        printf("ERROR | %s %s | unexpected exit status %d\n",
               oplabel, pagelabel, status);
        exit(2);
      }
    }
#endif
  }
  return failed;
}