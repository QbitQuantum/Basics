static WORD VCP_Callback( LPVOID obj, UINT16 msg, WPARAM16 wParam, LPARAM lParam, LPARAM lParamRef )
{
    WORD args[8];
    DWORD ret = OK;
    if (VCP_Proc)
    {
        args[7] = HIWORD(obj);
        args[6] = LOWORD(obj);
        args[5] = msg;
        args[4] = wParam;
        args[3] = HIWORD(lParam);
        args[2] = LOWORD(lParam);
        args[1] = HIWORD(lParamRef);
        args[0] = LOWORD(lParamRef);
        WOWCallback16Ex( (DWORD)VCP_Proc, WCB16_PASCAL, sizeof(args), args, &ret );
    }
    return (WORD)ret;
}