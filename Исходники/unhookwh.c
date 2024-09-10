BOOL PASCAL _Cover_UnhookWindowsHook( int nhook, FARPROC proc )
{
    return( UnhookWindowsHook( nhook, (FARPROC)RealProcAddr( proc ) ) );
}