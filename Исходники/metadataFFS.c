void
getInodeAccessTimes(struct sub_data *inodeAccess, char **dname, char **fname,
		    int numdirs, int numFiles)
{
  int *perm;
  int fd, i, j;
  int startTime, endTime;
  struct alfs_stat buf;

#ifdef DEBUG
  printf("InodeAccessTime\n");
#endif

  perm = (int *) myMalloc (sizeof(int) * numFiles);

  /* create the files */
  for (i = 0; i < numFiles; i++) {
    if ((fd = open(fname[i], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1) {
      perror("inodeAccess, create");
      exit(1);
    }
    close(fd);
  }
    
  for (j = 0; j < reps; j++) {
    /* create permuation */
    createPerm(&perm, numFiles, 1, numFiles);

    /* flush buffers */
    flushAll();
    
    /* stat the path to get the path into the cache */
    for (i = 0; i < numdirs; i++)
      if (stat(dname[i], &buf) < 0) {
	perror("inodeAccess, stat path");
	exit(1);
      }

    /* stat in creation order */
    gettimeofday(&startTime, (struct timezone *) NULL);
    for (i = 0; i < numFiles; i++) {
      if (stat(fname[i], &buf) < 0) {
	perror("inodeAccess, stat seq");
	exit(1);
      }
    }
    gettimeofday(&endTime, (struct timezone *) NULL);
    inodeAccess->time1[j] = diffTime(startTime, endTime);
#ifdef DEBUG
    printf("SEQ: numFiles: %d, time: %f\n", numFiles, inodeAccess->time1[j]);
#endif

    /* flush buffers */
    flushAll();

    /* stat the path to get the path into the cache */
    for (i = 0; i < numdirs; i++)
      if (stat(dname[i], &buf) < 0) {
	perror("inodeAccess, stat path 2");
	exit(1);
      }

    /* stat in random order */
    gettimeofday(&startTime, (struct timezone *) NULL);
    for (i = 0; i < numFiles; i++) {
      if (stat(fname[perm[i]], &buf) < 0) {
	perror("inodeAccess, stat rand");
	exit(1);
      }
    }
    gettimeofday(&endTime, (struct timezone *) NULL);
    inodeAccess->time2[j] = diffTime(startTime, endTime);
#ifdef DEBUG
    printf("RAND: numFiles: %d, time: %f\n", numFiles, inodeAccess->time2[j]);
#endif
  }

  /* clean-up */
  for (i = 0; i < numFiles; i++)
    if (unlink(fname[i]) < 0) {
      perror("inodeAccessTime, unlink");
      exit(1);
    }
  free(perm);
}