/******************************************************************
 *		WDML_InvokeCallback16
 *
 *
 */
static HDDEDATA	CALLBACK WDML_InvokeCallback16(DWORD pfn16, UINT uType, UINT uFmt,
                                               HCONV hConv, HSZ hsz1, HSZ hsz2,
                                               HDDEDATA hdata, ULONG_PTR dwData1, ULONG_PTR dwData2)
{
    DWORD               d1 = 0;
    HDDEDATA            ret;
    CONVCONTEXT16       cc16;
    WORD args[16];

    switch (uType)
    {
    case XTYP_CONNECT:
    case XTYP_WILDCONNECT:
        if (dwData1)
        {
            map3216_conv_context(&cc16, (const CONVCONTEXT*)dwData1);
            d1 = MapLS(&cc16);
        }
        else
        break;
    default:
        d1 = dwData1;
        break;
    }
    args[15] = HIWORD(uType);
    args[14] = LOWORD(uType);
    args[13] = HIWORD(uFmt);
    args[12] = LOWORD(uFmt);
    args[11] = HIWORD(hConv);
    args[10] = LOWORD(hConv);
    args[9]  = HIWORD(hsz1);
    args[8]  = LOWORD(hsz1);
    args[7]  = HIWORD(hsz2);
    args[6]  = LOWORD(hsz2);
    args[5]  = HIWORD(hdata);
    args[4]  = LOWORD(hdata);
    args[3]  = HIWORD(d1);
    args[2]  = LOWORD(d1);
    args[1]  = HIWORD(dwData2);
    args[0]  = LOWORD(dwData2);
    WOWCallback16Ex(pfn16, WCB16_PASCAL, sizeof(args), args, (DWORD *)&ret);

    switch (uType)
    {
    case XTYP_CONNECT:
    case XTYP_WILDCONNECT:
        if (d1 != 0) UnMapLS(d1);
        break;
    }
    return ret;
}