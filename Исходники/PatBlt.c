void Test_BrushOrigin()
{
    ULONG aulBits[2] = {0x5555AAAA, 0};
    HBITMAP hbmp;
    HBRUSH hbr;
    BOOL ret;

    hbmp = CreateBitmap(2, 2, 1, 1, aulBits);
    if (!hbmp)
    {
        printf("Couln not create a bitmap\n");
        return;
    }

    hbr = CreatePatternBrush(hbmp);
    if (!hbr)
    {
        printf("Couln not create a bitmap\n");
        return;
    }

    if (!SelectObject(hdcTarget, hbr))
    {
        printf("failed to select pattern brush\n");
        return;
    }

    ret = PatBlt(hdcTarget, 0, 0, 2, 2, PATCOPY);
    ok_long(ret, 1);
    ok_long(gpulTargetBits[0], 0xffffff);
    ok_long(gpulTargetBits[1], 0);
    ok_long(gpulTargetBits[16], 0);
    ok_long(gpulTargetBits[17], 0xffffff);
    //printf("0x%lx, 0x%lx\n", gpulTargetBits[0], gpulTargetBits[1]);

    ret = PatBlt(hdcTarget, 1, 0, 2, 2, PATCOPY);
    ok_long(ret, 1);
    ok_long(gpulTargetBits[0], 0xffffff);
    ok_long(gpulTargetBits[1], 0);
    ok_long(gpulTargetBits[2], 0xffffff);
    ok_long(gpulTargetBits[16], 0);
    ok_long(gpulTargetBits[17], 0xffffff);
    ok_long(gpulTargetBits[18], 0);

}