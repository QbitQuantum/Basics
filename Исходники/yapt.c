BOOLEAN
WriteRandom(
    ULONG Iterations
    )
{
    ULONG      j,
               outstandingRequests,
               remaining = Iterations;
    ULONG      start,end;
    DOUBLE     testTime,thruPut = 0.0,seconds = 0;
    HANDLE     file,
               port;
    OVERLAPPED overlapped,
               *overlapped2;
    DWORD      bytesWritten,
               bytesWritten2,
               completionKey,
               errCode,
               version;
    BOOLEAN    status;
    PUCHAR     buffer;
    ULONG      min = FileSize,max = 0;

    printf("Starting Random Writes of %d Meg file, using %d K I/O size\n", FileSize / 1024*1024, BufferSize / 1024);

    version = GetVersion() >> 16;

    buffer = VirtualAlloc(NULL,
                          BufferSize + SectorSize - 1,
                          MEM_COMMIT | MEM_RESERVE,
                          PAGE_READWRITE);

    (ULONG)buffer &= ~(SectorSize - 1);

    if ( !buffer ) {
        Log(0,"Error allocating buffer: %x\n",GetLastError());
        return FALSE;
    }

    file = CreateFile(FileName,
                      GENERIC_READ | GENERIC_WRITE,
                      FILE_SHARE_READ | FILE_SHARE_WRITE,
                      NULL,
                      OPEN_ALWAYS,
                      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
                      NULL );

    if ( file == INVALID_HANDLE_VALUE ) {
        Log(0,"Error opening Target file: %x\n",GetLastError());
        VirtualFree(buffer,
                    BufferSize + SectorSize - 1,
                    MEM_DECOMMIT);
        return FALSE;
    }

    port = CreateIoCompletionPort(file,
                                  NULL,
                                  (DWORD)file,
                                  0);
    if ( !port ) {
        Log(0,"Error creating completion port: %x\n",GetLastError());
        VirtualFree(buffer,
                    BufferSize + SectorSize - 1,
                    MEM_DECOMMIT);
        return FALSE;
    }

    while (remaining--) {

        start = GetTickCount();

        memset(&overlapped,0,sizeof(overlapped));

        outstandingRequests = 0;

        for (j = 0; j < FileSize / BufferSize; j++) {
            do {

                status = WriteFile(file,
                                  buffer,
                                  BufferSize,
                                  &bytesWritten,
                                  &overlapped);

                errCode = GetLastError();

                if (!status) {
                    if (errCode == ERROR_IO_PENDING) {
                        break;
                    } else if (errCode == ERROR_NOT_ENOUGH_QUOTA ||
                               errCode == ERROR_INVALID_USER_BUFFER ||
                               errCode == ERROR_WORKING_SET_QUOTA ||
                               errCode == ERROR_NOT_ENOUGH_MEMORY) {
                        //
                        // Allow this to retry.
                        //

                    } else {
                        Log(0,"Error in WriteFile: %x\n",errCode);
                        VirtualFree(buffer,
                                    BufferSize + SectorSize - 1,
                                    MEM_DECOMMIT);
                        return FALSE;
                    }

                }

            } while (!status);

            outstandingRequests++;
            overlapped.Offset = GetRandomOffset(0,FileSize - BufferSize);
            if (overlapped.Offset > max) {
                max = overlapped.Offset;
            }
            if (overlapped.Offset < min) {
                min = overlapped.Offset;
            }
        }

        for (j = 0; j < outstandingRequests; j++) {

            status = GetQueuedCompletionStatus(port,
                                               &bytesWritten2,
                                               &completionKey,
                                               &overlapped2,
                                               (DWORD)-1);

            if (!status) {
                Log(0,"GetQueuedCompletionStatus error: %x\n",GetLastError());
                VirtualFree(buffer,
                            BufferSize + SectorSize - 1,
                            MEM_DECOMMIT);
                return FALSE;
            }

        }

        end = GetTickCount();
        testTime = end - start;
        testTime /= 1000.0;
        seconds += testTime;
        Log(1,"Iteration %2d -> %4.3f MB/S\n",Iterations - remaining,(FileSize / testTime)/(1024*1024));

    }

    CloseHandle(port);
    CloseHandle(file);

    thruPut = FileSize * Iterations / seconds;
    printf("\nAverage Throughput %4.3f MB/S\n",thruPut/(1024*1024));
    Log(2,"Min = %Lu, Max = %Lu, FileSize = %Lu\n",min,max,FileSize);

    VirtualFree(buffer,
                BufferSize + SectorSize - 1,
                MEM_DECOMMIT);

    return TRUE;
}