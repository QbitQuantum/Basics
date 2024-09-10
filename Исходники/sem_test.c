int main (int argc, char **argv)   /* argc holds command line argument count */
{                                  /* argv holds the arguments */

    int n_waiting;              /* number waiting for the semaphore */
    char name[10];              /* give your process a name to distinguish it */
    if ( argc == 2 ) {          /* read in process name from command line */
      strcpy(name,argv[1]);     /* argv[0] is the name of the executable 
                                   argv[1] is the first command line arg */
      printf("process name: %s\n",name);
    } else {
      printf("USAGE: sem_test <process name> \n");
      exit(EXIT_FAILURE);
    } 
    char pathname[30];
    int semid;
    struct sembuf sops[2];  /* will hold two operations */

    /* Generate a pseudo-unique ipc key */
    key_t ipckey;
    getcwd(pathname,30);
    strcat(pathname,"foo");  /* foo must exist in your directory */
    ipckey = ftok(pathname, 42);  
                                        
    int nsems = 1;  /* the number of semaphores you want in the set */
    /* create and set perms on the set; 4 is read, 2 is alter, 6 is BOTH */
    semid = semget(ipckey, nsems, 0666 | IPC_CREAT);
    if (semid < 0) {
          printf("Error - %s\n", strerror(errno));
          _exit(1);
    }

    my_semun.val = 1;
    semctl(semid, 0, SETVAL, my_semun);
    int sem_value = semctl(semid, 0, GETVAL);
    printf("Sem#0 value: %d\n",sem_value);

    /* now set it back */
    my_semun.val = 0;
    semctl(semid, 0, SETVAL, my_semun);

    /* initialize sembuf struct for semaphore operations */
    sops[0].sem_num = 0;  /* operation applies to the first semaphore in  set */
    sops[0].sem_flg = SEM_UNDO; /* undo action if premature exit */

    sops[1].sem_num = 0;        /* op 2 also applies to the first semaphore */
    sops[1].sem_flg = SEM_UNDO; 

    while(1)  
    {

        /* these two semaphore operations are be executed atomically */
        sops[0].sem_op = 0; /* 1st operation: wait until sem value is zero */
        sops[1].sem_op = 1; /* 2nd operation: add 1 to semaphore value */

        /* perform the two operations */
        semop(semid, sops, 2); 

        /* use semctl to get actual value of semaphore */
        n_waiting = semctl(semid, 0, GETZCNT);
        printf("%s: %d waiting for semaphore \n", name, n_waiting);

        printf("[%s] I have the semaphore\n", name);
        sleep(rand() % 3); /* critical section, take a nap for 0-2 seconds */

        /* define second operation */
        sops[0].sem_op = -1; /* decrement semaphore value by 1 */

        semop(semid, sops, 1);
        printf("[%s] Released semaphore\n", name);

        sleep(rand() % 3); /* Sleep 0-2 seconds */
    }

  
    exit(EXIT_SUCCESS);
}