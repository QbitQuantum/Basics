static void test_ChooseFontA(void)
{
    LOGFONTA lfa;
    CHOOSEFONTA cfa;
    BOOL ret;
    int dpiy = get_dpiy();
    int expected_pointsize, expected_lfheight;
    HDC printer_ic;

    memset(&lfa, 0, sizeof(LOGFONTA));
    lfa.lfHeight = -16;
    lfa.lfWeight = FW_NORMAL;
    strcpy(lfa.lfFaceName, "Symbol");

    memset(&cfa, 0, sizeof(CHOOSEFONTA));
    cfa.lStructSize = sizeof(cfa);
    cfa.lpLogFont = &lfa;
    cfa.Flags = CF_ENABLEHOOK|CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS;
    cfa.lpfnHook = CFHookProcOK;

    ret = ChooseFontA(&cfa);

    expected_pointsize = MulDiv(16, 72, dpiy) * 10;
    expected_lfheight = -MulDiv(expected_pointsize, dpiy, 720);

    ok(ret == TRUE, "ChooseFontA returned FALSE\n");
    ok(cfa.iPointSize == expected_pointsize, "Expected %i, got %i\n", expected_pointsize, cfa.iPointSize);
    ok(lfa.lfHeight == expected_lfheight, "Expected %i, got %i\n", expected_lfheight, lfa.lfHeight);
    ok(lfa.lfWeight == FW_NORMAL, "Expected FW_NORMAL, got %i\n", lfa.lfWeight);
    ok(strcmp(lfa.lfFaceName, "Symbol") == 0, "Expected Symbol, got %s\n", lfa.lfFaceName);

    printer_ic = get_printer_ic();
    if (!printer_ic)
        skip("can't get a DC for a local printer\n");
    else
    {
        memset(&lfa, 0, sizeof(LOGFONTA));
        lfa.lfHeight = -16;
        lfa.lfWeight = FW_NORMAL;
        strcpy(lfa.lfFaceName, "Symbol");

        memset(&cfa, 0, sizeof(CHOOSEFONTA));
        cfa.lStructSize = sizeof(cfa);
        cfa.lpLogFont = &lfa;
        cfa.Flags = CF_ENABLEHOOK|CF_INITTOLOGFONTSTRUCT|CF_PRINTERFONTS;
        cfa.hDC = printer_ic;
        cfa.lpfnHook = CFHookProcOK;

        ret = ChooseFontA(&cfa);

        expected_pointsize = MulDiv(16, 72, dpiy) * 10;
        expected_lfheight = -MulDiv(expected_pointsize, dpiy, 720);

        ok(ret == TRUE, "ChooseFontA returned FALSE\n");
        ok(cfa.iPointSize == expected_pointsize, "Expected %i, got %i\n", expected_pointsize, cfa.iPointSize);
        ok(lfa.lfHeight == expected_lfheight, "Expected %i, got %i\n", expected_lfheight, lfa.lfHeight);
        ok(lfa.lfWeight == FW_NORMAL, "Expected FW_NORMAL, got %i\n", lfa.lfWeight);
        ok(strcmp(lfa.lfFaceName, "Symbol") == 0, "Expected Symbol, got %s\n", lfa.lfFaceName);

        DeleteDC(printer_ic);
    }
}