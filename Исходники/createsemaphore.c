int __cdecl main (int argc, char **argv)
{
    int i;
    int j;

    if(0 != (PAL_Initialize(argc, argv)))
    {
        return (FAIL);
    }
    /* create semaphores */
    for (i = 0; i < sizeof(testCases)/sizeof(struct testcase); i++)
    {
        hSemaphore[i] = CreateSemaphoreA (testCases[i].lpSemaphoreAttributes,
                                          testCases[i].lInitialCount,
                                          testCases[i].lMaximumCount,
                                          testCases[i].lpName);

        if (NULL == hSemaphore[i])
        {
            if (!testCases[i].bNegativeTest)
            {
                Trace("PALSUITE ERROR: CreateSemaphoreA('%p' '%ld' '%ld' "
                      "'%p') returned NULL at index %d.\nGetLastError "
                      "returned %d.\n", testCases[i].lpSemaphoreAttributes,
                      testCases[i].lInitialCount, testCases[i].lMaximumCount,
                      testCases[i].lpName, i, GetLastError());
                if (i > 0)
                {
                    cleanup(i - 1);
                }
                Fail("");
            }
            else
            {
                continue;
            }
        }
        /* incriment semaphore count to lMaximumCount */
        for (j = testCases[i].lInitialCount; j <= testCases[i].lMaximumCount;
                j++)
        {
            if (testCases[i].lMaximumCount == j)
            {
                /* Call ReleaseSemaphore once more to ensure ReleaseSemaphore
                   fails */
                if(ReleaseSemaphore(hSemaphore[i], 1, NULL))
                {
                    Trace("PALSUITE ERROR: ReleaseSemaphore('%p' '%ld' '%p') "
                          "call returned %d\nwhen it should have returned "
                          "%d.\nThe semaphore's count was %d.\nGetLastError "
                          "returned %d.\n", hSemaphore[i], 1, NULL, TRUE,
                          FALSE, j, GetLastError());
                    cleanup(i);
                    Fail("");
                }
            }
            else
            {
                int previous;
                BOOL bRet = ReleaseSemaphore(hSemaphore[i], 1, &previous);
                DWORD dwError = GetLastError();

                if(!bRet)
                {
                    Trace("PALSUITE ERROR: ReleaseSemaphore('%p' '%ld' '%p') "
                          "call returned %d\nwhen it should have returned "
                          "%d.\nThe semaphore count was %d and it's "
                          "lMaxCount was %d.\nGetLastError returned %d.\n",
                          hSemaphore[i], 1, &previous, bRet, TRUE, j,
                          testCases[i].lMaximumCount, dwError);
                    cleanup(i);
                    Fail("");
                }
                if (previous != j)
                {
                    Trace("PALSUITE ERROR: ReleaseSemaphore('%p' '%ld' '%p') "
                          "call set %p to %d instead of %d.\n The semaphore "
                          "count was %d and GetLastError returned %d.\n",
                          hSemaphore[i], 1, &previous, &previous, previous,
                          j, j, dwError);
                    cleanup(i);
                    Fail("");
                }
            }
        }
        /* decrement semaphore count to 0 */
        for (j = testCases[i].lMaximumCount; j >= 0; j--)
        {
            DWORD dwRet = WaitForSingleObject(hSemaphore[i], 0);
            DWORD dwError = GetLastError();

            if (0 == j)
            {
                /* WaitForSingleObject should report that the
                   semaphore is nonsignaled */
                if (WAIT_TIMEOUT != dwRet)
                {
                    Trace("PALSUITE ERROR: WaitForSingleObject('%p' '%u') "
                          "call returned %d\nwhen it should have returned "
                          "%d.\nThe semaphore's count was %d.\nGetLastError "
                          "returned %d.\n", hSemaphore[i], 0, dwRet,
                          WAIT_TIMEOUT, j, dwError);
                    cleanup(i);
                    Fail("");
                }
            }
            else
            {
                /* WaitForSingleObject should report that the
                   semaphore is signaled */
                if (WAIT_OBJECT_0 != dwRet)
                {
                    Trace("PALSUITE ERROR: WaitForSingleObject('%p' '%u') "
                          "call returned %d\nwhen it should have returned "
                          "%d.\nThe semaphore's count was %d.\nGetLastError "
                          "returned %d.\n", hSemaphore[i], 0, dwRet,
                          WAIT_OBJECT_0, j, dwError);
                    cleanup(i);
                    Fail("");
                }
            }
        }
    }
    PAL_Terminate();
    return (PASS);
}