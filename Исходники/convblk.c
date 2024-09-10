NET_API_STATUS
RxpConvertBlock(
    IN DWORD ApiNumber,
    IN LPBYTE ResponseBlockPointer,
    IN LPDESC ParmDescriptorString,
    IN LPDESC DataDescriptor16 OPTIONAL,
    IN LPDESC DataDescriptor32 OPTIONAL,
    IN LPDESC AuxDesc16 OPTIONAL,
    IN LPDESC AuxDesc32 OPTIONAL,
    IN va_list *FirstArgumentPointer,   // rest of API's arguments
    IN LPBYTE SmbRcvBuffer OPTIONAL,
    IN DWORD SmbRcvByteLen,
    OUT LPBYTE RcvDataBuffer OPTIONAL,
    IN DWORD RcvDataLength,
    IN DWORD Flags
    )

/*++

Routine Description:

    RxpConvertBlock translates the remote response (of a remoted API) into
    the local equivalent.  This involves converting the response (which is in
    the form of 16-bit data in the transaction response buffer) to local
    data formats, and setting them in the argument list.

Arguments:

    ApiNumber - Function number of the API required.

    ResponseBlockPointer - Points to the transaction SMB response block.

    ParmDescriptorString - A pointer to a ASCIIZ string describing the API call
        parameters (other than server name).

    DataDescriptor16 - A pointer to a ASCIIZ string describing the
        structure of the data in the call, i.e. the return data structure
        for a Enum or GetInfo call.  This string is used for adjusting pointers
        to data in the local buffers after transfer across the net.  If there
        is no structure involved in the call then DataDescriptor16 must
        be a null pointer.

    DataDescriptor32 - An optional pointer to a ASCIIZ string describing the
        32-bit structure of the return data structure.

    AuxDesc16, AuxDesc32 - Will be NULL in most cases unless a REM_AUX_COUNT
        descriptor char is present in DataDescriptor16 in which case the
        aux descriptors define a secondary data format as DataDescriptor16
        defines the primary.

    FirstArgumentPointer - Points to the va_list (variable arguments list)
        containing the API arguments (after the server name).  The caller
        must call va_start and va_end.

    SmbRcvBuffer - Optionally points to 16-bit format receive data buffer.

    SmbRcvByteLen - the number of bytes contained in SmbRcvBuffer (if not NULL)

    RcvDataBuffer - Points to the data area for the received data.  For
        instance, this may be a server info structure from NetServerGetInfo.
        This pointer will be NULL for many APIs.

        If (Flags & ALLOCATE_RESPONSE) then this pointer actually points to
        the pointer to the eventual buffer. We allocate a buffer in this routine
        and set *RcvDataBuffer to it. If we fail to get the buffer then
        *RcvDataBuffer will be set to NULL

    RcvDataLength - Length of the data area that RcvDataBuffer points to.
        If (Flags & ALLOCATE_RESPONSE) then this value will be the size that the
        caller of RxRemoteApi originally decided that the down-level server
        should use and incidentally was the original size of SmbRcvBuffer

    Flags - bit-mapped flags word. Currently defined flags are:
        NO_PERMISSION_REQUIRED  - used by RxpTransactSmb to determine whether
                                  a NULL session may be used
        ALLOCATE_RESPONSE       - used by this routine to allocate the final
                                  32-bit response data buffer based on the size
                                  of the SMB data received, multiplied by the
                                  RAP_CONVERSION_FACTOR
Return Value:

    NET_API_STATUS - return value from remote API.

--*/

{
    DWORD Converter;            // For pointer fixups.
    LPBYTE CurrentBlockPointer;
    LPDWORD        EntriesReadPtr = NULL;
    DWORD NumStruct;            // Loop count for ptr fixup.
    va_list ParmPtr;
    LPBYTE         pDataBuffer = NULL;  // pointer to returned data
    NET_API_STATUS Status;      // Return status from remote.
    DWORD TempLength;           // General purpose length.


#if DBG

    //
    // Code in this file depends on 16-bit words; the Remote Admin Protocol
    // demands it.
    //

    NetpAssert( ( (sizeof(WORD)) * CHAR_BIT) == 16);

    if (DataDescriptor16 != NULL) {
        NetpAssert(DataDescriptor32 != NULL);
    } else {
        NetpAssert(DataDescriptor32 == NULL);
    }

    if (AuxDesc16 != NULL) {
        NetpAssert(AuxDesc32 != NULL);
    } else {
        NetpAssert(AuxDesc32 == NULL);
    }
#endif


    ParmPtr = *FirstArgumentPointer;

    // The API call was successful. Now translate the return buffers
    // into the local API format.
    //
    // First copy any data from the return parameter buffer into the
    // fields pointed to by the original call parameters.
    // The return parameter buffer contains;
    //      Status,         (16 bits)
    //      Converter,      (16 bits)
    //      ...             fields described by rcv ptr types in
    //                      ParmDescriptorString


    CurrentBlockPointer = ResponseBlockPointer;
    Status = (NET_API_STATUS) SmbGetUshort( (LPWORD) CurrentBlockPointer );
    CurrentBlockPointer += sizeof(WORD);

    Converter = ((DWORD) SmbGetUshort( (LPWORD) CurrentBlockPointer )) & 0xffff;
    IF_DEBUG(CONVBLK) {
        NetpKdPrint(( PREFIX_NETAPI
                "RxpConvertBlock: Converter=" FORMAT_HEX_DWORD ".\n",
                Converter ));
    }
    CurrentBlockPointer += sizeof(WORD);

    // Set default value of NumStruct to 1, if data, 0 if no data.

    if ( (DataDescriptor16 != NULL) && (*DataDescriptor16 != '\0') ) {
        NumStruct = 1;
    } else {
        NumStruct = 0;
    }

    for( ; *ParmDescriptorString != '\0'; ParmDescriptorString++) {

        IF_DEBUG(CONVBLK) {
            NetpKdPrint(( PREFIX_NETAPI
                    "RxpConvertBlock: *parm='" FORMAT_LPDESC_CHAR
                    "', ParmPtr is:\n", *ParmDescriptorString ));
            NetpDbgHexDump((LPVOID) & ParmPtr, sizeof(va_list));
        }
        switch( *ParmDescriptorString) {
        case REM_WORD :                 // Word in old APIs (DWORD in 32-bit).
        case REM_DWORD :                // DWord.
            // BUGBUG: is array possible here?
            (void) va_arg(ParmPtr, DWORD);      // Step over this arg.
            break;

        case REM_ASCIZ :
            (void) va_arg(ParmPtr, LPSTR);      // Step over this arg.
            break;

        case REM_BYTE_PTR :
            (void) va_arg(ParmPtr, LPBYTE);     // Step over this arg.
            (void) RapArrayLength(
                        ParmDescriptorString,
                        &ParmDescriptorString,
                        Response);
            break;

        case REM_WORD_PTR :             // (WORD *) in old APIs.
        case REM_DWORD_PTR :            // (DWORD *)
            (void) va_arg(ParmPtr, LPDWORD);    // Step over this arg.
            break;

        case REM_RCV_WORD_PTR :    // pointer to rcv word(s) (DWORD in 32-bit)
            {
                LPDWORD Temp;
                DWORD ArrayCount;
                Temp = va_arg(ParmPtr, LPDWORD);

                ++ParmDescriptorString;  // point to first (possible) digit...
                ArrayCount = RapDescArrayLength(
                        ParmDescriptorString);  // updated past last.
                --ParmDescriptorString;  // point back at last digit for loop.
                IF_DEBUG(CONVBLK) {
                    NetpKdPrint(( PREFIX_NETAPI
                            "RxpConvertBlock: rcv.word.ptr, temp="
                            FORMAT_LPVOID ", ArrayCount=" FORMAT_DWORD ".\n",
                            (LPVOID) Temp, ArrayCount ));
                }

                // if the rcv buffer given to us by the user is NULL,
                // (one currently can be - it is an MBZ parameter for
                // now in the log read apis...), don't attempt to
                // copy anything. TempLength will be garbage in this
                // case, so don't update CurrentBlockPointer either.  All we
                // use RapArrayLength for is to update ParmDescriptorString if
                // the parameter was NULL.

                if ( Temp == NULL ) {
                    ;        /* NULLBODY */
                } else {

                    // Copy one or more words (expanding to DWORDS as we go).
                    DWORD WordsLeft = ArrayCount;
                    do {
                        DWORD Data;
                        // Convert byte order if necessary, and expand.
                        Data = (DWORD) SmbGetUshort(
                                (LPWORD) CurrentBlockPointer );
                        *Temp = Data;
                        Temp += sizeof(DWORD);
                        --WordsLeft;
                    } while (WordsLeft > 0);

                    // This gross hack is to fix the problem that a
                    // down level spooler (Lan Server 1.2)
                    // do not perform level checking
                    // on the w functions of the api(s):
                    // DosPrintQGetInfo
                    // and thus can return NERR_Success
                    // and bytesavail == 0.  This combination
                    // is technically illegal, and results in
                    // us attempting to unpack a buffer full of
                    // garbage.  The following code detects this
                    // condition and resets the amount of returned
                    // data to zero so we do not attempt to unpack
                    // the buffer.        Since we know the reason for the
                    // mistake at the server end is that we passed
                    // them a new level, we return ERROR_INVALID_LEVEL
                    // in this case.
                    // ERICPE, 5/16/90.

                    if ((ApiNumber == API_WPrintQGetInfo)
                    && (Status == NERR_Success)
                    && (*(LPWORD)CurrentBlockPointer == 0)
                    && (*ParmDescriptorString == REM_RCV_WORD_PTR)) {

                        Status = ERROR_INVALID_LEVEL;
                        goto ErrorExit;
                    }
                    // END OF GROSS HACK

                    CurrentBlockPointer += (ArrayCount * sizeof(WORD));
                 }
                break;
            }

        case REM_RCV_BYTE_PTR :         // pointer to rcv byte(s)
            {
                LPBYTE Temp;
                Temp = va_arg(ParmPtr, LPBYTE);
                TempLength = RapArrayLength(
                        ParmDescriptorString,
                        &ParmDescriptorString,
                        Response);

                // if the rcv buffer given to us by the user is NULL,
                // (one currently can be - it is an MBZ parameter for
                // now in the log read apis...), don't attempt to
                // copy anything. TempLength will be garbage in this
                // case, so don't update CurrentBlockPointer either.  All we
                // use RapArrayLength for is to update ParmDescriptorString if
                // the parameter was NULL.

                if ( Temp != NULL ) {
                    NetpMoveMemory(
                                Temp,                           // dest
                                CurrentBlockPointer,            // src
                                TempLength);                    // len
                    CurrentBlockPointer += TempLength;
                 }
            }
            break;

        case REM_RCV_DWORD_PTR :        // pointer to rcv Dword(s)
            {
                LPDWORD Temp;
                Temp = va_arg(ParmPtr, LPDWORD);
                TempLength = RapArrayLength(
                        ParmDescriptorString,
                        &ParmDescriptorString,
                        Response);

                // if the rcv buffer given to us by the user is NULL,
                // (one currently can be - it is an MBZ parameter for
                // now in the log read apis...), don't attempt to
                // copy anything. TempLength will be garbage in this
                // case, so don't update CurrentBlockPointer either.  All we
                // use RapArrayLength for is to update ParmDescriptorString if
                // the parameter was NULL.

                if ( Temp == NULL ) {
                    ;        /* NULLBODY */
                } else {
                    // BUGBUG: Must byte swap here if necessary!
                    NetpMoveMemory(
                                Temp,                           // dest
                                CurrentBlockPointer,            // src
                                TempLength);                    // len
                    CurrentBlockPointer += TempLength;
                }
            }
            break;

        case REM_SEND_BUF_PTR :
            (void) va_arg(ParmPtr, LPVOID);     // Step over arg.
            break;

        case REM_SEND_BUF_LEN :
            (void) va_arg(ParmPtr, DWORD);      // Step over (32-bit) buf len.
            break;

        case REM_RCV_BUF_PTR :
            (void) va_arg(ParmPtr, LPVOID);
            break;

        case REM_RCV_BUF_LEN :
            (void) va_arg(ParmPtr, DWORD);      // Step over (32-bit) buf len.
            break;

        case REM_PARMNUM :
            (void) va_arg(ParmPtr, DWORD);      // Step over (32-bit) parm num.
            break;

        case REM_ENTRIES_READ :          // Used for NumStruct
            {
                EntriesReadPtr = va_arg(ParmPtr, LPDWORD);
                NumStruct = (DWORD) SmbGetUshort((LPWORD) CurrentBlockPointer);
                // BUGBUG: Is this appropriate way to handle truncation?
                NetpAssert(! RapValueWouldBeTruncated(NumStruct));
                IF_DEBUG(CONVBLK) {
                    NetpKdPrint(( PREFIX_NETAPI
                            "RxpConvertBlock: NumStruct is now "
                            FORMAT_DWORD ".\n", NumStruct ));
                }

                // Assume all entries will fit; we'll correct this later if not.
                *EntriesReadPtr = NumStruct;

                CurrentBlockPointer += sizeof(WORD);
                break;
            }

        case REM_FILL_BYTES :
            // Special case, this was not really an input parameter so ParmPtr
            // does not get changed. However, the ParmDescriptorString
            // pointer must be advanced past the descriptor field so
            // use get RapArrayLength to do this but ignore the
            // return length.

            (void) RapArrayLength(
                        ParmDescriptorString,
                        &ParmDescriptorString,
                        Response);
            break;

        case REM_AUX_NUM :              // Can't have aux in parm desc.
        case REM_BYTE :                 // Can't push a byte, so this is bogus?
        case REM_DATA_BLOCK :           // BUGBUG: Not in parm desc?
        case REM_DATE_TIME :            // Never used?
        case REM_NULL_PTR :             // BUGBUG: Not sure what to do here.
        case REM_SEND_LENBUF :          // BUGBUG: Not sure what to do here.
        default :
            NetpBreakPoint();
            Status = NERR_InternalError;
            goto ErrorExit;

        } // switch
    } // for

    //
    // If no data was returned from the server, then there's no point in
    // continuing. Return early with the status code as returned from the
    // remoted function
    //

    if (!SmbRcvByteLen) {
        if (Flags & ALLOCATE_RESPONSE) {

            //
            // We failed to allocate the buffer; this in turn will cause
            // RxRemoteApi to fail, in which event, the calling function
            // (ie RxNetXxxx) may try to free the buffer allocated on its
            // behalf (ie the buffer we just failed to get). Ensure that
            // the caller doesn't try to free an invalid pointer by setting
            // the returned pointer to NULL
            //

            NetpAssert(RcvDataBuffer);  // address of the callers buffer pointer
            *(LPBYTE*)RcvDataBuffer = NULL;
        }

        return Status;
    }

    //
    // If the caller of RxRemoteApi requested that we allocate the final data
    // buffer on their behalf, then allocate it here. We use as the size
    // criterion
    //
    // (RAP_CONVERSION_FACTOR + 1/RAP_CONVERSION_FRACTION) * SmbRcvByteLen
    //
    // since this has the size of 16-bit data actually received.
    //
    // RAP_CONVERSION_FACTOR is 2 since that's the ratio for the size of
    // WCHAR to CHAR and of DWORD to WORD.  However, Lanman data structures
    // typically represents text as zero terminated array of CHAR within the
    // returned structure.  The array itself is of maximum size.  However,
    // the typical native representation has a 4-byte pointer to a zero
    // terminated WCHAR.  A factor of 2 wouldn't account for the 4-byte pointer.
    // Assuming the smallest lanman array size is 13 bytes (e.g., NNLEN+1), an
    // additional factor of 4/13 (about 1/3) is needed.  So,
    // RAP_CONVERSION_FRACTION is 3.
    //
    // Round the size to a multiple of the alignment for the system to allow
    // data to be packed at the trailing end of the buffer.
    //
    // NOTE: Since the original API caller expects to use NetApiBufferFree to
    // get rid of this buffer, we must use NetapipBufferAllocate
    //

    if (Flags & ALLOCATE_RESPONSE) {
        NET_API_STATUS  ConvertStatus;

        NetpAssert(RcvDataBuffer);  // address of the callers buffer pointer
        NetpAssert(SmbRcvByteLen);  // size of the data received

        RcvDataLength = SmbRcvByteLen * RAP_CONVERSION_FACTOR;
        RcvDataLength += (SmbRcvByteLen + RAP_CONVERSION_FRACTION - 1) /
                         RAP_CONVERSION_FRACTION;
        RcvDataLength = ROUND_UP_COUNT( RcvDataLength, ALIGN_WORST );

        if (ConvertStatus = NetapipBufferAllocate(RcvDataLength,
                                                  (PVOID *) &pDataBuffer)) {
            NetpKdPrint(( PREFIX_NETAPI
                    "Error: RxpConvertBlock cannot allocate memory ("
                    "error " FORMAT_API_STATUS ").\n", ConvertStatus ));

            Status = ConvertStatus;
            goto ErrorExit;
        }
        NetpAssert( pDataBuffer != NULL );

        IF_DEBUG(CONVBLK) {
            NetpKdPrint(( PREFIX_NETAPI
                    "RxpConvertBlock: allocated " FORMAT_DWORD " byte buffer "
                    "at " FORMAT_LPVOID " for caller\n",
                    RcvDataLength, (LPVOID) pDataBuffer ));
        }

        *(LPBYTE*)RcvDataBuffer = pDataBuffer;
    } else {