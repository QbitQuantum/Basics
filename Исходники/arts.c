/**************************************************************************
 * 				DriverProc (WINEARTS.@)
 */
LRESULT CALLBACK ARTS_DriverProc(DWORD_PTR dwDevID, HDRVR hDriv, UINT wMsg,
                                 LPARAM dwParam1, LPARAM dwParam2)
{
/* EPP     TRACE("(%08lX, %04X, %08lX, %08lX, %08lX)\n",  */
/* EPP 	  dwDevID, hDriv, wMsg, dwParam1, dwParam2); */

    switch(wMsg) {
#ifdef HAVE_ARTS
    case DRV_LOAD:		if (ARTS_WaveInit()<0) return 0;
				return 1;
    case DRV_FREE:	        return ARTS_WaveClose();
    case DRV_OPEN:		return ARTS_drvOpen((LPSTR)dwParam1);
    case DRV_CLOSE:		return ARTS_drvClose(dwDevID);
    case DRV_ENABLE:		return 1;
    case DRV_DISABLE:		return 1;
    case DRV_QUERYCONFIGURE:	return 1;
    case DRV_CONFIGURE:		MessageBoxA(0, "aRts MultiMedia Driver!", "aRts Driver", MB_OK);	return 1;
    case DRV_INSTALL:		return DRVCNF_RESTART;
    case DRV_REMOVE:		return DRVCNF_RESTART;
#endif
    default:
	return DefDriverProc(dwDevID, hDriv, wMsg, dwParam1, dwParam2);
    }
}