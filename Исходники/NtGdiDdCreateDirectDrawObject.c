/*
 * Test see if we getting a DirectDrawObject from win32k
 *
 */
HANDLE
test_NtGdiDdCreateDirectDrawObject()
{
    HANDLE retValue=0;
    int fails=0;
    HDC hdc=CreateDCW(L"Display",NULL,NULL,NULL);

    if (hdc == NULL)
    {
        printf("No hdc was created with Display, trying now with DISPLAY\n");
        hdc=CreateDCW(L"DISPLAY",NULL,NULL,NULL);
        if (hdc == NULL)
        {
            printf("No hdc was created with DISPLAY, trying now with NULL\n");
            hdc=CreateDCW(NULL,NULL,NULL,NULL);
        }
    }

    if (hdc == NULL)
    {
        printf("No hdc was created at all perpare all test will fail\n");
        return NULL;
    }

    printf("Start testing of NtGdiDdCreateDirectDrawObject\n");

    retValue = OsThunkDdCreateDirectDrawObject(NULL);
    testing_noteq(retValue,NULL,fails,"NtGdiDdCreateDirectDrawObject(NULL);\0");

    retValue = OsThunkDdCreateDirectDrawObject(hdc);
    testing_eq(retValue,NULL,fails,"NtGdiDdCreateDirectDrawObject(hdc);\0");

    show_status(fails, "NtGdiDdCreateDirectDrawObject\0");

    return retValue;
}