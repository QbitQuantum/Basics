/***********************************************************************
 *           LZClose   (LZEXPAND.6)
 */
void WINAPI LZClose16( HFILE16 fd )
{
    if (IS_LZ_HANDLE(fd)) LZClose( fd );
    else DisposeLZ32Handle( DosFileHandleToWin32Handle((HFILE)fd) );
}