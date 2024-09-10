/***********************************************************************
 *           SystemHeapInfo   (TOOLHELP.71)
 */
BOOL16 WINAPI SystemHeapInfo16( SYSHEAPINFO *pHeapInfo )
{
    STACK16FRAME* stack16 = MapSL((SEGPTR)NtCurrentTeb()->WOW32Reserved);
    HANDLE16 oldDS = stack16->ds;
    WORD user = LoadLibrary16( "USER.EXE" );
    WORD gdi = LoadLibrary16( "GDI.EXE" );
    stack16->ds = user;
    pHeapInfo->wUserFreePercent = (int)LocalCountFree16() * 100 / LocalHeapSize16();
    stack16->ds = gdi;
    pHeapInfo->wGDIFreePercent  = (int)LocalCountFree16() * 100 / LocalHeapSize16();
    stack16->ds = oldDS;
    pHeapInfo->hUserSegment = user;
    pHeapInfo->hGDISegment  = gdi;
    FreeLibrary16( user );
    FreeLibrary16( gdi );
    return TRUE;
}