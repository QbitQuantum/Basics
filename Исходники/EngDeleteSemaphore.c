void Test_EngDeleteSemaphore()
{
    HSEMAPHORE hsem;
    PRTL_CRITICAL_SECTION lpcrit;

    /* test Create then delete */
    hsem = EngCreateSemaphore();
    ok(hsem != NULL, "EngCreateSemaphore failed\n");
    if (!hsem) return;
    lpcrit = (PRTL_CRITICAL_SECTION)hsem;
    EngDeleteSemaphore(hsem);

//    ok(lpcrit->LockCount > 0); doesn't work on XP
    ok(lpcrit->RecursionCount == 0, "lpcrit->RecursionCount=%ld\n", lpcrit->RecursionCount);
    ok(lpcrit->OwningThread == 0, "lpcrit->OwningThread=%p\n", lpcrit->OwningThread);
    ok(lpcrit->LockSemaphore == 0, "lpcrit->LockSemaphore=%p\n", lpcrit->LockSemaphore);
    ok(lpcrit->SpinCount == 0, "lpcrit->SpinCount=%ld\n", lpcrit->SpinCount);

    //ok(lpcrit->DebugInfo != NULL, "no DebugInfo\n");
    if (lpcrit->DebugInfo)
    {
        ok(lpcrit->DebugInfo->Type != 0, "DebugInfo->Type=%d\n", lpcrit->DebugInfo->Type);
        ok(lpcrit->DebugInfo->CreatorBackTraceIndex != 0, "DebugInfo->CreatorBackTraceIndex=%d\n", lpcrit->DebugInfo->CreatorBackTraceIndex);
        //ok(lpcrit->DebugInfo->EntryCount != 0, "DebugInfo->EntryCount=%ld\n", lpcrit->DebugInfo->EntryCount);
        //ok(lpcrit->DebugInfo->ContentionCount != 0, "DebugInfo->ContentionCount=%ld\n", lpcrit->DebugInfo->ContentionCount);
    }

    /* test EngAcquireSemaphore and release it, then delete it */
    hsem = EngCreateSemaphore();
    ok(hsem != NULL, "EngCreateSemaphore failed\n");
    if (!hsem) return;
    lpcrit = (PRTL_CRITICAL_SECTION)hsem;

    EngAcquireSemaphore(hsem);
    EngReleaseSemaphore(hsem);
    EngDeleteSemaphore(hsem);

    //ok(lpcrit->LockCount > 0, "lpcrit->LockCount=%ld\n", lpcrit->LockCount);
    ok(lpcrit->RecursionCount == 0, "lpcrit->RecursionCount=%ld\n", lpcrit->RecursionCount);
    ok(lpcrit->OwningThread == 0, "lpcrit->OwningThread=%p\n", lpcrit->OwningThread);
    ok(lpcrit->LockSemaphore == 0, "lpcrit->LockSemaphore=%p\n", lpcrit->LockSemaphore);
    ok(lpcrit->SpinCount == 0, "lpcrit->SpinCount=%ld\n", lpcrit->SpinCount);

    //ok(lpcrit->DebugInfo != NULL, "no DebugInfo\n");
    if (lpcrit->DebugInfo)
    {
        ok(lpcrit->DebugInfo->Type != 0, "DebugInfo->Type=%d\n", lpcrit->DebugInfo->Type);
        ok(lpcrit->DebugInfo->CreatorBackTraceIndex != 0, "DebugInfo->CreatorBackTraceIndex=%d\n", lpcrit->DebugInfo->CreatorBackTraceIndex);
        //ok(lpcrit->DebugInfo->EntryCount != 0, "DebugInfo->EntryCount=%ld\n", lpcrit->DebugInfo->EntryCount);
        //ok(lpcrit->DebugInfo->ContentionCount != 0, "DebugInfo->ContentionCount=%ld\n", lpcrit->DebugInfo->ContentionCount);
    }
}