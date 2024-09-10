NET_API_STATUS
RxpConvertAuditArray(
    IN LPVOID InputArray,
    IN DWORD InputByteCount,
    OUT LPBYTE * OutputArrayPtr, // will be alloc'ed (free w/ NetApiBufferFree).
    OUT LPDWORD OutputByteCountPtr
    )
{
    DWORD EntryType;
    const LPBYTE InputArrayEndPtr
            = (LPVOID) ( ((LPBYTE)InputArray) + InputByteCount );
    LPBYTE InputBytePtr;
    DWORD InputDataOffset;
    DWORD InputTotalEntrySize;
    LPBYTE InputFixedPtr;
    LPBYTE InputVariablePtr;
    DWORD InputVariableSize;
    LPVOID OutputArray;
    DWORD OutputArraySize;
    DWORD OutputBytesUsed = 0;
    DWORD OutputEntrySizeSoFar;
    LPAUDIT_ENTRY OutputFixedPtr;
    DWORD OutputVariableSize;
    LPBYTE OutputVariablePtr;
    NET_API_STATUS Status;

    //
    // Error check caller's parameters.
    // Set output parameters to make error handling easier below.
    // (Also check for memory faults while we're at it.)
    //
    if (OutputArrayPtr != NULL) {
        *OutputArrayPtr = NULL;
    }
    if (OutputByteCountPtr != NULL) {
        *OutputByteCountPtr = 0;
    }
    if ( (OutputArrayPtr == NULL) || (OutputByteCountPtr == NULL) ) {
        return (ERROR_INVALID_PARAMETER);
    }
    if ( (InputArray == NULL) || (InputByteCount == 0) ) {
        return (ERROR_INVALID_PARAMETER);
    }

    //
    // Compute size needed for output buffer, taking into account:
    //    per field expansion,
    //    per entry expansion,
    //    and alignment.
    //

    Status = RxpEstimateLogSize(
            DOWNLEVEL_AUDIT_FIXED_ENTRY_SIZE,
            InputByteCount,     // input (downlevel) array size in bytes.
            FALSE,              // no, we're not doing error log
            & OutputArraySize); // set estimated array size in bytes.
    if (Status != NO_ERROR) {
        return (Status);        // (output vars are already set.)
    }

    NetpAssert( OutputArraySize > 0 );
    NetpAssert( OutputArraySize > InputByteCount );

    *OutputByteCountPtr = OutputArraySize;

    //
    // Allocate oversize area for output; we'll realloc it to shrink it.
    //
    Status = NetApiBufferAllocate(
            OutputArraySize,
            (LPVOID *) & OutputArray );
    if (Status != NERR_Success) {
        return (Status);        // (output vars are already set.)
    }
    NetpAssert( OutputArray != NULL );
    NetpAssert( POINTER_IS_ALIGNED( OutputArray, ALIGN_WORST ) );

    //
    // Loop for each entry in the input area.
    //
    OutputFixedPtr = OutputArray;
    for (InputBytePtr = InputArray; InputBytePtr < InputArrayEndPtr; ) {

        InputFixedPtr = InputBytePtr;

        NetpAssert( POINTER_IS_ALIGNED( OutputFixedPtr, ALIGN_WORST ) );

        IF_DEBUG(AUDIT) {
            NetpKdPrint(( PREFIX_NETLIB
                    "RxpConvertAuditArray: doing input entry at "
                    FORMAT_LPVOID ", out entry at " FORMAT_LPVOID ".\n",
                    (LPVOID) InputFixedPtr, (LPVOID) OutputFixedPtr ));
        }

        //
        // Process each field in input fixed entry.
        //

        InputTotalEntrySize = (DWORD) SmbGetUshort( (LPWORD) InputBytePtr );
        if (InputTotalEntrySize < MIN_DOWNLEVEL_ENTRY_SIZE) {
            goto FileCorrupt;
        }

        {
            LPBYTE EndPos = InputBytePtr + InputTotalEntrySize;
            if (EndPos > InputArrayEndPtr) {
                goto FileCorrupt;
            }
            EndPos -= sizeof(WORD);     // the last ae_len2
            if (SmbGetUshort( (LPWORD) EndPos ) != InputTotalEntrySize) {
                goto FileCorrupt;
            }
        }
        InputBytePtr += sizeof(WORD);    // skip ae_len.

        OutputFixedPtr->ae_reserved =
                (DWORD) SmbGetUshort( (LPWORD) InputBytePtr );
        InputBytePtr += sizeof(WORD);   //  skip ae_reserved

        {
            DWORD LocalTime = (DWORD) SmbGetUlong( (LPDWORD) InputBytePtr );
            DWORD GmtTime;
            NetpLocalTimeToGmtTime( LocalTime, & GmtTime );
            OutputFixedPtr->ae_time = GmtTime;
            InputBytePtr += sizeof(DWORD);
        }

        EntryType = (DWORD) SmbGetUshort( (LPWORD) InputBytePtr );
        OutputFixedPtr->ae_type = EntryType;
        InputBytePtr += sizeof(WORD);

        InputDataOffset = (DWORD) SmbGetUshort( (LPWORD) InputBytePtr );
        NetpAssert( InputDataOffset >= DOWNLEVEL_AUDIT_FIXED_ENTRY_SIZE );
        InputBytePtr += sizeof(WORD);

        OutputEntrySizeSoFar = sizeof(AUDIT_ENTRY);


        //
        // Process variable portion (if any):
        //

        InputVariablePtr = (LPVOID)
                ( ((LPBYTE) InputFixedPtr) + InputDataOffset );
        InputVariableSize =
                (InputTotalEntrySize - InputDataOffset)
                - sizeof(WORD);  // don't include ae_len2.

        OutputVariablePtr = (LPVOID)
                ( ((LPBYTE) OutputFixedPtr) + sizeof(AUDIT_ENTRY) );

        // Align variable part.
        OutputVariablePtr = ROUND_UP_POINTER( OutputVariablePtr, ALIGN_WORST );
        OutputEntrySizeSoFar =
                ROUND_UP_COUNT( OutputEntrySizeSoFar, ALIGN_WORST );

        OutputFixedPtr->ae_data_offset = OutputEntrySizeSoFar;

        // Copy and convert the variable part.
        RxpConvertAuditEntryVariableData(
                EntryType,
                InputVariablePtr,
                OutputVariablePtr,
                InputVariableSize,
                & OutputVariableSize);

#ifdef REVISED_AUDIT_ENTRY_STRUCT
        OutputFixedPtr->ae_data_size = OutputVariableSize;
#endif

        // Account for variable area and ae_len2 in total length.
        OutputEntrySizeSoFar += (OutputVariableSize + sizeof(DWORD));

        // Round size up so next entry (if any) is worst-case aligned.
        OutputEntrySizeSoFar =
                ROUND_UP_COUNT( OutputEntrySizeSoFar, ALIGN_WORST );


#define OutputEntrySize  OutputEntrySizeSoFar


        OutputFixedPtr->ae_len = OutputEntrySize;

        {
            LPDWORD EndSizePtr = (LPVOID)
                    ( ((LPBYTE)OutputFixedPtr)
                        + OutputEntrySize - sizeof(DWORD) );
            *EndSizePtr = OutputEntrySize;   // set ae_len2.
        }

        //
        // Update for next loop iteration.
        //

        InputBytePtr = (LPVOID)
                ( ((LPBYTE) InputFixedPtr)
                    + InputTotalEntrySize);

        OutputFixedPtr = (LPVOID)
                ( ((LPBYTE) OutputFixedPtr) + OutputEntrySize );

        OutputBytesUsed += OutputEntrySize;

        NetpAssert( OutputBytesUsed <= OutputArraySize );

    }

    NetpAssert(OutputBytesUsed > 0);
    NetpAssert( OutputBytesUsed <= OutputArraySize );

    // BUGBUG: realloc OutputArray to OutputBytesUsed


    *OutputArrayPtr = OutputArray;
    *OutputByteCountPtr = OutputBytesUsed;

    return (NERR_Success);

FileCorrupt:

    NetpKdPrint(( PREFIX_NETAPI
            "RxpConvertAuditArray: corrupt audit log!\n" ));

    if (OutputArray != NULL) {
        (VOID) NetApiBufferFree( OutputArray );
    }
    if (OutputArrayPtr != NULL) {
        *OutputArrayPtr = NULL;
    }
    if (OutputByteCountPtr != NULL) {
        *OutputByteCountPtr = 0;
    }
    return (NERR_LogFileCorrupt);

}