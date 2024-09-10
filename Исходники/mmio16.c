/******************************************************************
 *		MMIO_Callback3216
 *
 *
 */
static LRESULT MMIO_Callback3216(SEGPTR cb16, LPMMIOINFO lpmmioinfo, UINT uMessage,
                                 LPARAM lParam1, LPARAM lParam2)
{
    DWORD 		result;
    MMIOINFO16          mmioInfo16;
    SEGPTR		segmmioInfo16;
    LPARAM		lp1 = lParam1, lp2 = lParam2;
    WORD                args[7];

    if (!cb16) return MMSYSERR_INVALPARAM;

    memset(&mmioInfo16, 0, sizeof(MMIOINFO16));
    mmioInfo16.lDiskOffset = lpmmioinfo->lDiskOffset;
    mmioInfo16.adwInfo[0]  = lpmmioinfo->adwInfo[0];
    mmioInfo16.adwInfo[1]  = lpmmioinfo->adwInfo[1];
    mmioInfo16.adwInfo[2]  = lpmmioinfo->adwInfo[2];
    /* map (lParam1, lParam2) into (lp1, lp2) 32=>16 */
    if ((result = MMIO_Map32To16(uMessage, &lp1, &lp2)) != MMSYSERR_NOERROR)
        return result;

    segmmioInfo16 = MapLS(&mmioInfo16);
    args[6] = HIWORD(segmmioInfo16);
    args[5] = LOWORD(segmmioInfo16);
    args[4] = uMessage;
    args[3] = HIWORD(lp1);
    args[2] = LOWORD(lp1);
    args[1] = HIWORD(lp2);
    args[0] = LOWORD(lp2);
    WOWCallback16Ex( cb16, WCB16_PASCAL, sizeof(args), args, &result );
    UnMapLS(segmmioInfo16);
    MMIO_UnMap32To16(uMessage, lParam1, lParam2, lp1, lp2);

    lpmmioinfo->lDiskOffset = mmioInfo16.lDiskOffset;
    lpmmioinfo->adwInfo[0]  = mmioInfo16.adwInfo[0];
    lpmmioinfo->adwInfo[1]  = mmioInfo16.adwInfo[1];
    lpmmioinfo->adwInfo[2]  = mmioInfo16.adwInfo[2];

    return result;
}