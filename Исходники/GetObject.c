void
Test_Brush(void)
{
    LOGBRUSH logbrush;
    HBRUSH hBrush;

    FillMemory(&logbrush, sizeof(LOGBRUSH), 0x77);
    hBrush = CreateSolidBrush(RGB(1,2,3));
    ok(hBrush != 0, "CreateSolidBrush failed, skipping tests.\n");
    if (!hBrush) return;

    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_BRUSH, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_BRUSH, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(WORD), NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 5, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, -5, NULL) == sizeof(LOGBRUSH), "\n");

    //ok(GetObject(hBrush, 0, &logbrush) == 0, "\n"); fails on win7
    ok(logbrush.lbStyle == 0x77777777, "\n");
    ok(GetObject(hBrush, 5, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(logbrush.lbStyle == 0, "\n");
    ok(logbrush.lbColor == 0x77777701, "\n");

    ok(GetObject(hBrush, sizeof(LOGBRUSH), &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(LOGBRUSH) - 1, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 1, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(LOGBRUSH)+2, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, -1, &logbrush) == sizeof(LOGBRUSH), "\n");
    // TODO: test all members

    ok(GetLastError() == ERROR_SUCCESS, "\n");
    DeleteObject(hBrush);

    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_BRUSH, sizeof(LOGBRUSH), &logbrush) == 0, "\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());
}