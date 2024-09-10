/*************************************************************************
 * RunDLL_CallEntry16
 *
 * Only exported from shell32 on Windows, probably imported
 * from shell through the 16/32 thunks.
 */
void WINAPI RunDLL_CallEntry16( DWORD proc, HWND hwnd, HINSTANCE inst, LPCSTR cmdline, INT cmdshow )
{
    WORD args[5];
    SEGPTR cmdline_seg;

    TRACE( "proc %x hwnd %p inst %p cmdline %s cmdshow %d\n",
           proc, hwnd, inst, debugstr_a(cmdline), cmdshow );

    cmdline_seg = MapLS( cmdline );
    args[4] = HWND_16(hwnd);
    args[3] = MapHModuleLS(inst);
    args[2] = SELECTOROF(cmdline_seg);
    args[1] = OFFSETOF(cmdline_seg);
    args[0] = cmdshow;
    WOWCallback16Ex( proc, WCB16_PASCAL, sizeof(args), args, NULL );
    UnMapLS( cmdline_seg );
}