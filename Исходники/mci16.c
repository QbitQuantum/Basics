static UINT MCI_Yield1632(DWORD pfn16, MCIDEVICEID id, DWORD yield_data)
{
    WORD args[8];

    if (!pfn16)
    {
        MSG msg;
        PeekMessageW( &msg, 0, 0, 0, PM_REMOVE | PM_QS_SENDMESSAGE );
        return 0;
    }

    /* 16 bit func, call it */
    TRACE("Function (16 bit) !\n");

    args[2] = (MCIDEVICEID16)id;
    args[1] = HIWORD(yield_data);
    args[0] = LOWORD(yield_data);
    return WOWCallback16Ex(pfn16, WCB16_PASCAL, sizeof(args), args, NULL);
}