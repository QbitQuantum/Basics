void fileaccess(int fd, int count){
   void lockfile (void);
   void unlockfile (void);

   int i, k, value; pid_t pid;
   char buff[MAXSIZE];

   shmid = shmget(SHMKEY, sizeof(syncvars), PERMS | IPC_CREAT);
   shmptr = (syncvars *) shmat(shmid, (void *) NULL, 0);

   pid = getpid();

   for(i = 0; i < count; i++){
      lockfile();
      while(shmptr->turn == 0 && shmptr->flag[0] == TRUE );

      //critical stuff
      lseek(fd, 0L, 0);
      k = read(fd, buff, MAXSIZE); buff[k] = '\0';
      sscanf(buff, "%d\n", &value);
      value++;

      sprintf(buff, "%10d\n", value);
      lseek(fd, 0l, 0);
      k = strlen(buff); write(fd, buff, k);
      printf("pid = %d, new value = %d\n", pid, value);
      unlockfile();
   }
}