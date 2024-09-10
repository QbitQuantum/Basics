void test_calls_wptr (Workspace p, int i)
{
    void *ptr;

    Reschedule (p);
    if (i == 0) {
        SetErr (p);
        SetErrM (p, "test");
        Shutdown (p);
    }

    ptr = MAlloc (p, i);
    MRelease (p, ptr);
}