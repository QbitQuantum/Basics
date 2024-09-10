/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t DeleteTree(uint8_t *filePath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to the directory path

   Outputs:       Returns 0 on success else an error code
                   
   Description:   Deletes all the files and directories of the specified path
<
----------------------------------------------------------------------------*/
RtStatus_t DeleteTree(uint8_t * filePath)
{
    RtStatus_t RetValue = SUCCESS;
    int32_t HandleNumber = 0;
    int32_t StartingCluster;
    FindData_t _finddata;
    uint8_t Buf[32];
    HandleTable_t TempHandle;
//  int64_t lTemp;

    if ((RetValue = Chdir(filePath)) < 0)
        return RetValue;

    TempHandle = Handle[CWD_HANDLE];

    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (RtStatus_t) HandleNumber;

    Handle[HandleNumber] = Handle[CWD_HANDLE];

    if ((Handle[HandleNumber].StartingCluster) ==
        MediaTable[Handle[HandleNumber].Device].RootdirCluster)
        return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;

    if ((ReadDirectoryRecord(HandleNumber, 1, Buf)) <= 0)
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;

    // sdk 2.6 first corrected the shift direction to left instead of right.  3.095 release had left since it had fix from sdk2.6.
    StartingCluster =
        ((FSGetWord(Buf, DIR_FSTCLUSLOOFFSET)) | (FSGetWord(Buf, DIR_FSTCLUSHIOFFSET) << 16));

    if ((RetValue = Fseek(HandleNumber, 0, SEEK_SET)) < 0)
        return RetValue;

    Freehandle(HandleNumber);

    if ((RetValue =
         DeleteAllRecords(StartingCluster, &_finddata)) == ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE) {
        Handle[CWD_HANDLE] = TempHandle;
        return SUCCESS;
    } else {
        Handle[CWD_HANDLE] = TempHandle;
        return RetValue;
    }
}