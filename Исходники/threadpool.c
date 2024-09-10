static void test_tp_wait(void)
{
    TP_CALLBACK_ENVIRON environment;
    TP_WAIT *wait1, *wait2;
    struct wait_info info;
    HANDLE semaphores[2];
    LARGE_INTEGER when;
    NTSTATUS status;
    TP_POOL *pool;
    DWORD result;

    semaphores[0] = CreateSemaphoreW(NULL, 0, 2, NULL);
    ok(semaphores[0] != NULL, "failed to create semaphore\n");
    semaphores[1] = CreateSemaphoreW(NULL, 0, 1, NULL);
    ok(semaphores[1] != NULL, "failed to create semaphore\n");
    info.semaphore = semaphores[0];

    /* allocate new threadpool */
    pool = NULL;
    status = pTpAllocPool(&pool, NULL);
    ok(!status, "TpAllocPool failed with status %x\n", status);
    ok(pool != NULL, "expected pool != NULL\n");

    /* allocate new wait items */
    memset(&environment, 0, sizeof(environment));
    environment.Version = 1;
    environment.Pool = pool;

    wait1 = NULL;
    status = pTpAllocWait(&wait1, wait_cb, &info, &environment);
    ok(!status, "TpAllocWait failed with status %x\n", status);
    ok(wait1 != NULL, "expected wait1 != NULL\n");

    wait2 = NULL;
    status = pTpAllocWait(&wait2, wait_cb, &info, &environment);
    ok(!status, "TpAllocWait failed with status %x\n", status);
    ok(wait2 != NULL, "expected wait2 != NULL\n");

    /* infinite timeout, signal the semaphore immediately */
    info.userdata = 0;
    pTpSetWait(wait1, semaphores[1], NULL);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 1, "expected info.userdata = 1, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* relative timeout, no event */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)200 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[0], 200);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* repeat test with call to TpWaitForWait(..., TRUE) */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)200 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    pTpWaitForWait(wait1, TRUE);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[0], 200);
    ok(result == WAIT_OBJECT_0 || broken(result == WAIT_TIMEOUT) /* Win 8 */,
       "WaitForSingleObject returned %u\n", result);
    if (result == WAIT_OBJECT_0)
        ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);
    else
        ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* relative timeout, with event */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)200 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 1, "expected info.userdata = 1, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* repeat test with call to TpWaitForWait(..., TRUE) */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)200 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    pTpWaitForWait(wait1, TRUE);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0 || broken(result == WAIT_TIMEOUT) /* Win 8 */,
       "WaitForSingleObject returned %u\n", result);
    if (result == WAIT_OBJECT_0)
    {
        ok(info.userdata == 1, "expected info.userdata = 1, got %u\n", info.userdata);
        result = WaitForSingleObject(semaphores[1], 0);
        ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    }
    else
    {
        ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
        result = WaitForSingleObject(semaphores[1], 0);
        ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    }

    /* absolute timeout, no event */
    info.userdata = 0;
    NtQuerySystemTime( &when );
    when.QuadPart += (ULONGLONG)200 * 10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[0], 200);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* absolute timeout, with event */
    info.userdata = 0;
    NtQuerySystemTime( &when );
    when.QuadPart += (ULONGLONG)200 * 10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 1, "expected info.userdata = 1, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* test timeout of zero */
    info.userdata = 0;
    when.QuadPart = 0;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* cancel a pending wait */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)250 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    pTpSetWait(wait1, NULL, (void *)0xdeadbeef);
    Sleep(50);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0, "expected info.userdata = 0, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);

    /* test with INVALID_HANDLE_VALUE */
    info.userdata = 0;
    when.QuadPart = 0;
    pTpSetWait(wait1, INVALID_HANDLE_VALUE, &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);

    /* cancel a pending wait with INVALID_HANDLE_VALUE */
    info.userdata = 0;
    when.QuadPart = (ULONGLONG)250 * -10000;
    pTpSetWait(wait1, semaphores[1], &when);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    when.QuadPart = 0;
    pTpSetWait(wait1, INVALID_HANDLE_VALUE, &when);
    Sleep(50);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 0x10000, "expected info.userdata = 0x10000, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);

    CloseHandle(semaphores[1]);
    semaphores[1] = CreateSemaphoreW(NULL, 0, 2, NULL);
    ok(semaphores[1] != NULL, "failed to create semaphore\n");

    /* add two wait objects with the same semaphore */
    info.userdata = 0;
    pTpSetWait(wait1, semaphores[1], NULL);
    pTpSetWait(wait2, semaphores[1], NULL);
    Sleep(50);
    ReleaseSemaphore(semaphores[1], 1, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 1, "expected info.userdata = 1, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* repeat test above with release count 2 */
    info.userdata = 0;
    pTpSetWait(wait1, semaphores[1], NULL);
    pTpSetWait(wait2, semaphores[1], NULL);
    Sleep(50);
    result = ReleaseSemaphore(semaphores[1], 2, NULL);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    result = WaitForSingleObject(semaphores[0], 100);
    ok(result == WAIT_OBJECT_0, "WaitForSingleObject returned %u\n", result);
    ok(info.userdata == 2, "expected info.userdata = 2, got %u\n", info.userdata);
    result = WaitForSingleObject(semaphores[1], 0);
    ok(result == WAIT_TIMEOUT, "WaitForSingleObject returned %u\n", result);

    /* cleanup */
    pTpReleaseWait(wait1);
    pTpReleaseWait(wait2);
    pTpReleasePool(pool);
    CloseHandle(semaphores[0]);
    CloseHandle(semaphores[1]);
}