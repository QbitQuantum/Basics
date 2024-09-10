/***********************************************************************
 *         ImageDirectoryEntryToData   (DBGHELP.@)
 *
 * NOTES
 *   See ImageDirectoryEntryToDataEx
 */
PVOID WINAPI ImageDirectoryEntryToData( PVOID base, BOOLEAN image, USHORT dir, PULONG size )
{
    return ImageDirectoryEntryToDataEx( base, image, dir, size, NULL );
}