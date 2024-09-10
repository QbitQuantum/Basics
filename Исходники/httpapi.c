static void test_HttpCreateHttpHandle(void)
{
    HANDLE handle, handle2;
    ULONG ret;
    BOOL b;

    ret = HttpCreateHttpHandle(NULL, 0);
todo_wine
    ok(ret == ERROR_INVALID_PARAMETER, "Unexpected ret value %u.\n", ret);

    /* Non-zero reserved parameter is accepted on XP/2k3. */
    handle = NULL;
    ret = HttpCreateHttpHandle(&handle, 0);
todo_wine {
    ok(!ret, "Unexpected ret value %u.\n", ret);
    ok(handle != NULL, "Unexpected handle value %p.\n", handle);
}
    handle2 = NULL;
    ret = HttpCreateHttpHandle(&handle2, 0);
todo_wine {
    ok(!ret, "Unexpected ret value %u.\n", ret);
    ok(handle2 != NULL && handle != handle2, "Unexpected handle %p.\n", handle2);
}
    b = CloseHandle(handle);
todo_wine
    ok(b, "Failed to close queue handle.\n");
}