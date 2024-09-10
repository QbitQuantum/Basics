/**************************************************************************
 *				DRIVER_SendMessage		[internal]
 */
inline static LRESULT DRIVER_SendMessage(LPWINE_DRIVER lpDrv, UINT16 msg,
					 LPARAM lParam1, LPARAM lParam2)
{
    WORD args[8];
    DWORD ret;

    TRACE("Before CallDriverProc proc=%p driverID=%08lx wMsg=%04x p1=%08lx p2=%08lx\n",
	  lpDrv->lpDrvProc, lpDrv->dwDriverID, msg, lParam1, lParam2);

    args[7] = HIWORD(lpDrv->dwDriverID);
    args[6] = LOWORD(lpDrv->dwDriverID);
    args[5] = lpDrv->hDriver16;
    args[4] = msg;
    args[3] = HIWORD(lParam1);
    args[2] = LOWORD(lParam1);
    args[1] = HIWORD(lParam2);
    args[0] = LOWORD(lParam2);
    WOWCallback16Ex( (DWORD)lpDrv->lpDrvProc, WCB16_PASCAL, sizeof(args), args, &ret );
    return ret;
}