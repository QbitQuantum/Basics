static int
do_test (void)
{
    pthread_t th;
    int err;

    printf ("&cond = %p\n&mut = %p\n", &cond, &mut);

    puts ("parent: get mutex");

    err = pthread_barrier_init (&bar, NULL, 2);
    if (err != 0)
    {
        puts ("parent: cannot init barrier");
        exit (1);
    }

    puts ("parent: create child");

    err = pthread_create (&th, NULL, tf1, NULL);
    if (err != 0)
    {
        puts ("parent: cannot create thread");
        exit (1);
    }

    puts ("parent: wait for child to lock mutex");

    err = pthread_barrier_wait (&bar);
    if (err != 0 && err != PTHREAD_BARRIER_SERIAL_THREAD)
    {
        puts ("parent: cannot wait for barrier");
        exit (1);
    }

    err = pthread_mutex_lock (&mut);
    if (err != 0)
    {
        puts ("parent: mutex_lock failed");
        exit (1);
    }

    err = pthread_mutex_unlock (&mut);
    if (err != 0)
    {
        puts ("parent: mutex_unlock failed");
        exit (1);
    }

    if (pthread_cancel (th) != 0)
    {
        puts ("cannot cancel thread");
        exit (1);
    }

    void *r;
    err = pthread_join (th, &r);
    if (err != 0)
    {
        puts ("parent: failed to join");
        exit (1);
    }

    if (r != PTHREAD_CANCELED)
    {
        puts ("child hasn't been canceled");
        exit (1);
    }



    puts ("parent: create 2nd child");

    err = pthread_create (&th, NULL, tf2, NULL);
    if (err != 0)
    {
        puts ("parent: cannot create thread");
        exit (1);
    }

    puts ("parent: wait for child to lock mutex");

    err = pthread_barrier_wait (&bar);
    if (err != 0 && err != PTHREAD_BARRIER_SERIAL_THREAD)
    {
        puts ("parent: cannot wait for barrier");
        exit (1);
    }

    err = pthread_mutex_lock (&mut);
    if (err != 0)
    {
        puts ("parent: mutex_lock failed");
        exit (1);
    }

    err = pthread_mutex_unlock (&mut);
    if (err != 0)
    {
        puts ("parent: mutex_unlock failed");
        exit (1);
    }

    if (pthread_cancel (th) != 0)
    {
        puts ("cannot cancel thread");
        exit (1);
    }

    err = pthread_join (th, &r);
    if (err != 0)
    {
        puts ("parent: failed to join");
        exit (1);
    }

    if (r != PTHREAD_CANCELED)
    {
        puts ("child hasn't been canceled");
        exit (1);
    }

    puts ("done");

    return 0;
}