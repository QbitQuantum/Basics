int main()
{
    // In this program we create 2 threads which each access the
    // same Point object.  Hence we will need to provide synchronization.
    // Because in one case we set isMover = TRUE and in the other case
    // we set isMover = FALSE, one of the threads continually changes
    // the Point's x and y values while the other thread displays these
    // values. Note that both threads have the same thread entry function
    // even though they act completely differently.

    // With the synchronization statements removed, you will have to
    // look closely at the program output to spot those locations where
    // x and y differ.  They will differ by only 1, with x being the
    // larger number.

    Point * p = new Point();

    ThreadY * o1 = new ThreadY(true, p);

    HANDLE   hth1;
    unsigned  uiThread1ID;

    hth1 = (HANDLE)_beginthreadex(NULL,         // security
        0,            // stack size
        ThreadY::ThreadStaticStartUp,
        o1,           // arg list
        CREATE_SUSPENDED,  // so we can later call ResumeThread()
        &uiThread1ID);

    if (hth1 == 0)
        printf("Failed to create thread 1\n");

    DWORD   dwExitCode;

    GetExitCodeThread(hth1, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
    printf("initial thread 1 exit code = %u\n", dwExitCode);

    ThreadY * o2 = new ThreadY(false, p);

    HANDLE   hth2;
    unsigned  uiThread2ID;

    hth2 = (HANDLE)_beginthreadex(NULL,         // security
        0,            // stack size
        ThreadY::ThreadStaticStartUp,
        o2,           // arg list
        CREATE_SUSPENDED,  // so we can later call ResumeThread()
        &uiThread2ID);

    if (hth2 == 0)
        printf("Failed to create thread 2\n");

    GetExitCodeThread(hth2, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
    printf("initial thread 2 exit code = %u\n", dwExitCode);

    // If we hadn't specified CREATE_SUSPENDED in the call to _beginthreadex()
    // we wouldn't now need to call ResumeThread().

    ResumeThread(hth1);   // Jaeschke's   // t1->Start();
    ResumeThread(hth2);

    // We now want the primary thread to sleep to allow time for
    // the other threads to come alive.  This ensures the primary
    // thread will have to compete for access to the Point object.

    Sleep(100);


    // In C++/CLI the process continues until the last thread exits.
    // That is, the thread's have independent lifetimes. Hence
    // Jaeschke's original code was designed to show that the primary
    // thread could exit and not influence the other threads.

    // However in C++ the process terminates when the primary thread exits
    // and when the process terminates all its threads are then terminated.
    // Hence if you comment out the following waits, the non-primary
    // threads will never get a chance to run.

    WaitForSingleObject(hth1, INFINITE);
    WaitForSingleObject(hth2, INFINITE);

    GetExitCodeThread(hth1, &dwExitCode);
    printf("thread 1 exited with code %u\n", dwExitCode);

    GetExitCodeThread(hth2, &dwExitCode);
    printf("thread 2 exited with code %u\n", dwExitCode);

    // The handle returned by _beginthreadex() has to be closed
    // by the caller of _beginthreadex().

    CloseHandle(hth1);
    CloseHandle(hth2);

    delete o1;
    o1 = NULL;

    delete o2;
    o2 = NULL;

    printf("Primary thread terminating.\n");
}