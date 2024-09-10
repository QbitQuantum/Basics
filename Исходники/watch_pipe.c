void get_lock_or_die(char *pipename, char* lockname, int pid)
{
  int lock_state;
  do {
    lock_state=lockfile(lockname,241);
    if (!lock_state) {
      fprintf(stderr,"Can't get lock on %s\n",lockname);
      exit(1);
    }
    if (lock_state==2) {
      if (!checkPid(pid)) {
        unlink(pipename);
        unlink(lockname);
        exit(1);
      };
    }
  } while (lock_state==2);
}