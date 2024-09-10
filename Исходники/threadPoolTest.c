void *
fthSchedPthread(void *arg)
{
//  get  the fthread engine going

    waitee.waitType = PTOF_WAIT;
    waitee.wu.ptof = mbox;
    test_rock = 1;
    pool = createThreadPool(test_fn, test_rock, &waitee,
                            NUM_THREADS, STACK_SIZE);

    printf("Got the new threadPool %p\n", pool);
    sem_post(&general_sem);
    printf("Posted the semaphore\n", pool);
    fthSchedulerPthread(0);

    printf("Scheduler halted\n");
    return NULL;
}