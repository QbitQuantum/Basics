//=============================================================================
//  FUNCTION: IndexFileAdd
// ----------------------------------------------------------------------------
//! Add an entry to the index file.
//!
//! \param FileHandle 
//!     The handle for the index file to use.
//! \param  FileIndex
//!     The index that we are looking to add to the list of indexes.
//!
//! \retval DB_ERROR_CRITICAL
//!     Something really bad happened and we have no way to recover.
//! \retval DB_ERROR_NONE
//!     The index was successfully added to the index file.
//!
//=============================================================================
static _reentrant INT IndexFileAdd(INT FileHandle, INT FileIndex)
{
    INT TempIndex;
    LONG FilePosition;
    LONG lPosition;
    
    //
    // Need to see if this entry has already been deleted.
    //
    FilePosition = Ftell(FileHandle);
    lPosition = FilePosition;
    Fseek(FileHandle, 0, SEEK_SET);

    while (lPosition > 0)
    {
        if (DB_STRING_HANDLE_SIZE != Fread(FileHandle, &TempIndex, 
                    DB_STRING_HANDLE_SIZE, 
                    DEFAULT_MEMORY, -1))
        {
            return(DB_ERROR_CRITICAL);
        }
        if (TempIndex == FileIndex)
        {
            break;
        }
        lPosition -= DB_STRING_HANDLE_SIZE;
    }    

    if (0 == lPosition)
    {
        //
        // Seek back to the original position.
        //
        Fseek(FileHandle, FilePosition, SEEK_SET);

        //
        // Update deleted list.
        //
        if (DB_STRING_HANDLE_SIZE != Fwrite(FileHandle, &FileIndex, 
                DB_STRING_HANDLE_SIZE, 
                DEFAULT_MEMORY, -1))
        {
            return(DB_ERROR_CRITICAL);
        }
    }
    return(DB_ERROR_NONE);
}