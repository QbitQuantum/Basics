//--------------------------------------------------------------------
// @mfunc Set the offset into the file in bytes for a particular row.
// If the Index is beyond current allocation, reallocation is attempted.
//
// @rdesc BOOLEAN value
//      @flag TRUE | Succeeded
//      @flag FALSE | Failed to Initialize
//
BOOL CFileIdx::SetIndex
(
    DBCOUNTITEM	ulDex,        //@parm IN | Row Index value
    size_t		ulOffset      //@parm IN | Offset of Row in the File
)
{
    // Check index and realloc if beyond our current range
    if (m_ulDexCnt <= ulDex)
        if (FALSE == ReAlloc( ARRAY_INIT_SIZE ))
            return FALSE;

    m_rgDex[ulDex].ulOffset = ulOffset;
    m_rgDex[ulDex].bStatus = FALSE;

    return TRUE;
}