void  ErrorCodeTest(HDC hdcScreen)
{
    char * psz = "This is ExtTextOut error code test";
    DWORD  err;
    RECT   rc;

    rc.left = 0;     // arbitrary values
    rc.right = 100;
    rc.top   = 0;
    rc.bottom = 200;

// verify that retrieving error codes works properly:

   // SetBatchLimit(1);

    ExtTextOut (
                hdcScreen,
                10,20,
                ETO_CLIPPED,    // illegal to have null rect and nonzero flags
                (LPRECT)NULL,
                psz, strlen(psz),
                (LPINT)NULL);
    GdiFlush();
    err = GetLastError();
    DbgPrint ("ExtTextOut 1, Last error  = 0x%lx = %ld\n", err, err);


    ExtTextOut (
                hdcScreen,
                10,20,
                5,                        // invalid flag
                &rc,
                psz, strlen(psz),
                (LPINT)NULL);
    GdiFlush();
    err = GetLastError();
    DbgPrint ("ExtTextOut 2,  Last error  = 0x%lx = %ld\n", err, err);


    ExtTextOut (
                0X33344455,               // INVALID HANDLE
                10,20,
                0,
                (LPRECT)NULL,
                psz, strlen(psz),
                (LPINT)NULL);
    GdiFlush();
    err = GetLastError();
    DbgPrint ("ExtTextOut 3, Last error = 0x%lx = %ld\n", err, err);


    SetTextAlign (hdcScreen,0x77777777);
    GdiFlush();
    err = GetLastError();
    DbgPrint ("SetTextAlign, Last error  = 0x%lx = %ld\n", err, err);



    AngleArc(hdcScreen,
             100,          // x
             200,          // y
             0XFFFFFFFF,   // overflows when converted to long        // radius
             (FLOAT)0,
             (FLOAT)30
             );
    GdiFlush();
    err = GetLastError();
    DbgPrint ("AngleArc, Last error = 0x%lx = %ld\n", err, err);

    vDoPause(0);
}