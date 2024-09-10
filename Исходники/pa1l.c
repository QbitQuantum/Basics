void Main ()
{
    int ppid, pid1, pid2;

    ppid = Getpid ();

    if ((pid1 = Fork ()) == 0) {

        /* first child executes here */
        if ((pid2 = Fork ()) == 0) {
            /* Second child executes here */
            Printf ("I am the second child, my pid is %d\n", Getpid());
            Yield(ppid);
            Exit();
        }

        Printf ("I am the first child, my pid is %d\n", Getpid ());
        Yield(pid2);
        Exit ();
    }


    Yield (pid1);

    Printf ("I am the parent, my pid is %d\n", Getpid ());
}