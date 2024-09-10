void Main ()
{
    int i, me;
    void printMyThread();

    initThreads ();

    me = getThread ();
    for(i=1; i<MAXTHREADS; i++)
        spawnThread(printMyThread,0);

    for (i = 0; i < NUMYIELDS; i++) {
        Printf("0 T%d\n",me);
        yieldThread(1);
    }

    exitThread ();
}