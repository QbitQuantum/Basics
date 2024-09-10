DWORD
WINAPI
RetrieveLogRecords(
    _In_ LPVOID lpParameter
    )
/*++

Routine Description:

    This runs as a separate thread.  Its job is to retrieve log records
    from the filter and then output them

Arguments:

    lpParameter - Contains context structure for synchronizing with the
        main program thread.

Return Value:

    The thread successfully terminated

--*/
{
    PLOG_CONTEXT context = (PLOG_CONTEXT)lpParameter;
    DWORD bytesReturned = 0;
    DWORD used;
    PVOID alignedBuffer[BUFFER_SIZE/sizeof( PVOID )];
    PCHAR buffer = (PCHAR) alignedBuffer;
    HRESULT hResult;
    PLOG_RECORD pLogRecord;
    PRECORD_DATA pRecordData;
    COMMAND_MESSAGE commandMessage;

    //printf("Log: Starting up\n");

#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant

    while (TRUE) {

#pragma warning(pop)

        //
        //  Check to see if we should shut down.
        //

        if (context->CleaningUp) {

            break;
        }

        //
        //  Request log data from MiniSpy.
        //

        commandMessage.Command = GetMiniSpyLog;

        hResult = FilterSendMessage( context->Port,
                                     &commandMessage,
                                     sizeof( COMMAND_MESSAGE ),
                                     buffer,
                                     sizeof(alignedBuffer),
                                     &bytesReturned );

        if (IS_ERROR( hResult )) {

            if (HRESULT_FROM_WIN32( ERROR_INVALID_HANDLE ) == hResult) {

                printf( "The kernel component of minispy has unloaded. Exiting\n" );
                ExitProcess( 0 );
            } else {

                if (hResult != HRESULT_FROM_WIN32( ERROR_NO_MORE_ITEMS )) {

                    printf( "UNEXPECTED ERROR received: %x\n", hResult );
                }

                Sleep( POLL_INTERVAL );
            }

            continue;
        }

        //
        //  Buffer is filled with a series of LOG_RECORD structures, one
        //  right after another.  Each LOG_RECORD says how long it is, so
        //  we know where the next LOG_RECORD begins.
        //

        pLogRecord = (PLOG_RECORD) buffer;
        used = 0;

        //
        //  Logic to write record to screen and/or file
        //

        for (;;) {

            if (used+FIELD_OFFSET(LOG_RECORD,Name) > bytesReturned) {

                break;
            }

            if (pLogRecord->Length < (sizeof(LOG_RECORD)+sizeof(WCHAR))) {

                printf( "UNEXPECTED LOG_RECORD->Length: length=%d expected>=%d\n",
                        pLogRecord->Length,
                        (sizeof(LOG_RECORD)+sizeof(WCHAR)));

                break;
            }

            used += pLogRecord->Length;

            if (used > bytesReturned) {

                printf( "UNEXPECTED LOG_RECORD size: used=%d bytesReturned=%d\n",
                        used,
                        bytesReturned);

                break;
            }

            pRecordData = &pLogRecord->Data;

            //
            //  See if a reparse point entry
            //

            if (FlagOn(pLogRecord->RecordType,RECORD_TYPE_FILETAG)) {

                if (!TranslateFileTag( pLogRecord )){

                    //
                    // If this is a reparse point that can't be interpreted, move on.
                    //

                    pLogRecord = (PLOG_RECORD)Add2Ptr(pLogRecord,pLogRecord->Length);
                    continue;
                }
            }

            if (context->LogToScreen) {

                ScreenDump( pLogRecord->SequenceNumber,
                            pLogRecord->Name,
                            pRecordData );
            }

            if (context->LogToFile) {

                FileDump( pLogRecord->SequenceNumber,
                          pLogRecord->Name,
                          pRecordData,
                          context->OutputFile );
            }

            //
            //  The RecordType could also designate that we are out of memory
            //  or hit our program defined memory limit, so check for these
            //  cases.
            //

            if (FlagOn(pLogRecord->RecordType,RECORD_TYPE_FLAG_OUT_OF_MEMORY)) {

                if (context->LogToScreen) {

                    printf( "M:  %08X System Out of Memory\n",
                            pLogRecord->SequenceNumber );
                }

                if (context->LogToFile) {

                    fprintf( context->OutputFile,
                             "M:\t0x%08X\tSystem Out of Memory\n",
                             pLogRecord->SequenceNumber );
                }

            } else if (FlagOn(pLogRecord->RecordType,RECORD_TYPE_FLAG_EXCEED_MEMORY_ALLOWANCE)) {

                if (context->LogToScreen) {

                    printf( "M:  %08X Exceeded Mamimum Allowed Memory Buffers\n",
                            pLogRecord->SequenceNumber );
                }

                if (context->LogToFile) {

                    fprintf( context->OutputFile,
                             "M:\t0x%08X\tExceeded Mamimum Allowed Memory Buffers\n",
                             pLogRecord->SequenceNumber );
                }
            }

            //
            // Move to next LOG_RECORD
            //

            pLogRecord = (PLOG_RECORD)Add2Ptr(pLogRecord,pLogRecord->Length);
        }

        //
        //  If we didn't get any data, pause for 1/2 second
        //

        if (bytesReturned == 0) {

            Sleep( POLL_INTERVAL );
        }
    }

    printf( "Log: Shutting down\n" );
    ReleaseSemaphore( context->ShutDown, 1, NULL );
    printf( "Log: All done\n" );
    return 0;
}