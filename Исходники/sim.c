/**
 * Opens the references file, reads in each line, and dispatches the commands
 * specified as appropriate to the CPU and OS modules.
 */
void sim_readdata(void) {
  FILE *fp;
  char buff[512];

  if ((fp = fopen(filename, "r")) == NULL) {
    PERROR(filename);
    exit(EXIT_FAILURE);
  }

  /* For each line in the file... */
  while (fgets(buff, sizeof(buff), fp) != NULL) {
    char *cmd, *arg1, *arg2, *arg3;
    int pid;
    vaddr_t addr;
    word_t val, val2;
    
    /* Parse command and possible arguments */
    cmd  = strtok(buff, WHITESPACE);
    arg1 = strtok(NULL, WHITESPACE);
    arg2 = strtok(NULL, WHITESPACE);
    arg3 = strtok(NULL, WHITESPACE);

    switch (cmd[0]) {

    /* Create a new process */
    case '@':
      pid = atoi(arg1);
      if (pid < max_jobs) {
        printf("Forking new process %s (pid %d)...\n", arg2, pid);
        proc_fork(pid, arg2);
      } else {
        printf("Too many jobs, not forking new process!\n");
      }
      break;

    /* Load from a memory location */
    case 'l':
      pid = atoi(arg1);
      addr = atoi(arg2);
      val = atoi(arg3) % 256;
      if (pid >= max_jobs) {
        break;
      } else if (current == NULL || current->pid != pid) {
        printf("Switching to %s (pid %d)...\n", proc_getname(pid), pid);
        proc_switch(pid);
      }
      val2 = mem_load(addr);
      if (val2 != val) {
        printf(" ERROR! loaded value did not equal expected!\n");
        /* XXX: Dump a mem image here and quit */
      } else {
        printf("...OK\n");
      }
      break;
      
    /* Store to a memory location */
    case 's':
      pid = atoi(arg1);
      addr = atoi(arg2);
      val = atoi(arg3) % 256;
      if (pid >= max_jobs) {
        break;
      } else if (current == NULL || current->pid != pid) {
        printf("Switching to %s (pid %d)...\n", proc_getname(pid), pid);
        proc_switch(pid);
      }
      mem_store(addr, val);
      printf("...OK\n");

    /* Ignore other commands (for comments and the like */
    default:
      break;
    }
  }

  fclose(fp);
}