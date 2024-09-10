/***********************************************************************
 *		ICSendMessage			[MSVIDEO.205]
 */
LRESULT VFWAPI ICSendMessage16(HIC16 hic, UINT16 msg, DWORD lParam1, DWORD lParam2) 
{
    LRESULT     ret = ICERR_BADHANDLE;
    WINE_HIC*   whic;

    whic = MSVIDEO_GetHicPtr(HIC_32(hic));
    if (whic)
    {
        /* we've got a 16 bit driver proc... call it directly */
        if (whic->driverproc16)
        {
            WORD args[8];
            DWORD result;

            /* FIXME: original code was passing hdrv first and hic second */
            /* but this doesn't match what IC_Callback3216 does */
            args[7] = HIWORD(hic);
            args[6] = LOWORD(hic);
            args[5] = HDRVR_16(whic->hdrv);
            args[4] = msg;
            args[3] = HIWORD(lParam1);
            args[2] = LOWORD(lParam1);
            args[1] = HIWORD(lParam2);
            args[0] = LOWORD(lParam2);
            WOWCallback16Ex( whic->driverproc16, WCB16_PASCAL, sizeof(args), args, &result );
            ret = result;
        }
        else
        {
            /* map the message for a 32 bit infrastructure, and pass it along */
            void*       data16 = MSVIDEO_MapMsg16To32(msg, &lParam1, &lParam2);
    
            ret = MSVIDEO_SendMessage(whic, msg, lParam1, lParam2);
            if (data16)
                MSVIDEO_UnmapMsg16To32(msg, data16, &lParam1, &lParam2);
        }
    }
    return ret;
}