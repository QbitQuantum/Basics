void run() {
  pid_t pid;
  int i;
  struct sembuf inc[2] = {{0, a_size/2, 0}, {1, a_size/2, 0}};
  
  x_semop(semid, &inc[0], 1);

  for(i = 0; i < a_size/2; i++) {
    pid = x_fork();

    if(ISCHILD(pid)) {
      run_comparator(i, cascades);
      exit(0);
    }
  }

  i = 0;
  while(13) {
    x_semop(semid, &swait[i%2], 1);
    x_semop(semid, &inc[(i + 1)%2], 1);
    
    i++;
    if(cascades == i) {
      break;
    }
  }
}