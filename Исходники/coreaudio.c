/**************************************************************************
 * 				DriverProc (WINECOREAUDIO.1)
 */
LRESULT CALLBACK CoreAudio_DriverProc(DWORD_PTR dwDevID, HDRVR hDriv, UINT wMsg, 
                                 LPARAM dwParam1, LPARAM dwParam2)
{
     TRACE("(%08lX, %p, %s (%08X), %08lX, %08lX)\n",
           dwDevID, hDriv, wMsg == DRV_LOAD ? "DRV_LOAD" :
           wMsg == DRV_FREE ? "DRV_FREE" :
           wMsg == DRV_OPEN ? "DRV_OPEN" :
           wMsg == DRV_CLOSE ? "DRV_CLOSE" :
           wMsg == DRV_ENABLE ? "DRV_ENABLE" :
           wMsg == DRV_DISABLE ? "DRV_DISABLE" :
           wMsg == DRV_QUERYCONFIGURE ? "DRV_QUERYCONFIGURE" :
           wMsg == DRV_CONFIGURE ? "DRV_CONFIGURE" :
           wMsg == DRV_INSTALL ? "DRV_INSTALL" :
           wMsg == DRV_REMOVE ? "DRV_REMOVE" : "UNKNOWN", 
           wMsg, dwParam1, dwParam2);

    switch(wMsg) {
    case DRV_LOAD:		return CoreAudio_drvLoad();
    case DRV_FREE:		return CoreAudio_drvFree();
    case DRV_OPEN:		return CoreAudio_drvOpen((LPSTR)dwParam1);
    case DRV_CLOSE:		return CoreAudio_drvClose(dwDevID);
    case DRV_ENABLE:		return 1;
    case DRV_DISABLE:		return 1;
    case DRV_QUERYCONFIGURE:	return 1;
    case DRV_CONFIGURE:		MessageBoxA(0, "CoreAudio driver!", "CoreAudio driver", MB_OK); return 1;
    case DRV_INSTALL:		return DRVCNF_RESTART;
    case DRV_REMOVE:		return DRVCNF_RESTART;
    default:
	return DefDriverProc(dwDevID, hDriv, wMsg, dwParam1, dwParam2);
    }
}