//-----------------------------------------------------------------------------
// Name: HeapCopy()
// Desc: Allocate buffer in memory and copy the content of sName to the
//       buffer, then return the address of the buffer.
//-----------------------------------------------------------------------------
CHAR* HeapCopy( CHAR *sName )
{
    DWORD dwLen = (DWORD) strlen( sName ) + 1;
    CHAR * sNewName = new CHAR[ dwLen ];
    if( sNewName )
        StringCchCopyA( sNewName, dwLen, sName );
    return sNewName;
}