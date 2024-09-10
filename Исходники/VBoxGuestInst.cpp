int performTest(void)
{
    int rc = 0;

    HANDLE hDevice = openDriver();

    if (hDevice != INVALID_HANDLE_VALUE)
    {
        DWORD cbReturned;

        closeDriver(hDevice);
    } else
    {
        printf("openDriver failed!\n");
    }


    return rc;
}