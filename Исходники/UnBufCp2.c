VOID
ReadLoop(
    ULARGE_INTEGER FileSize
    )
{
    ULARGE_INTEGER ReadPointer;
    BOOL Success;
    DWORD NumberBytes;
    LPOVERLAPPED CompletedOverlapped;
    DWORD_PTR Key;
    PCOPY_CHUNK Chunk;
    int PendingIO = 0;
    int i;

    //
    // Start reading the file. Kick off MAX_CONCURRENT_IO reads, then just
    // loop waiting for writes to complete.
    //
    ReadPointer.QuadPart = 0;

    for (i=0; i < MAX_CONCURRENT_IO; i++) {
        if (ReadPointer.QuadPart >= FileSize.QuadPart) {
            break;
        }
        //
        // Use VirtualAlloc so we get a page-aligned buffer suitable
        // for unbuffered I/O.
        //
        CopyChunk[i].Buffer = VirtualAlloc(NULL,
                                           BUFFER_SIZE,
                                           MEM_COMMIT,
                                           PAGE_READWRITE);
        if (CopyChunk[i].Buffer == NULL) {
            fprintf(stderr, "VirtualAlloc %d failed, error %d\n",i, GetLastError());
            exit(1);
        }
        CopyChunk[i].Overlapped.Offset = ReadPointer.LowPart;
        CopyChunk[i].Overlapped.OffsetHigh = ReadPointer.HighPart;
        CopyChunk[i].Overlapped.hEvent = NULL;     // not needed

        Success = ReadFile(SourceFile,
                           CopyChunk[i].Buffer,
                           BUFFER_SIZE,
                           &NumberBytes,
                           &CopyChunk[i].Overlapped);

        if (!Success && (GetLastError() != ERROR_IO_PENDING)) {
            fprintf(stderr,
                    "ReadFile at %lx failed, error %d\n",
                    ReadPointer.LowPart,
                    GetLastError());
            exit(1);
        } else {
            ReadPointer.QuadPart += BUFFER_SIZE;
            ++PendingIO;

        }
    }

    //
    // We have started the initial async. reads, enter the main loop.
    // This simply waits until a write completes, then issues the next
    // read.
    //
    while (PendingIO) {
        Success = GetQueuedCompletionStatus(WritePort,
                                            &NumberBytes,
                                            &Key,
                                            &CompletedOverlapped,
                                            INFINITE);
        if (!Success) {
            //
            // Either the function failed to dequeue a completion packet
            // (CompletedOverlapped is not NULL) or it dequeued a completion
            // packet of a failed I/O operation (CompletedOverlapped is NULL).  
            //
            fprintf(stderr,
                    "GetQueuedCompletionStatus on the IoPort failed, error %d\n",
                    GetLastError());
            exit(1);
        }
        //
        // Issue the next read using the buffer that has just completed.
        //
        if (ReadPointer.QuadPart < FileSize.QuadPart) {
            Chunk = (PCOPY_CHUNK)CompletedOverlapped;
            Chunk->Overlapped.Offset = ReadPointer.LowPart;
            Chunk->Overlapped.OffsetHigh = ReadPointer.HighPart;
            ReadPointer.QuadPart += BUFFER_SIZE;
            Success = ReadFile(SourceFile,
                               Chunk->Buffer,
                               BUFFER_SIZE,
                               &NumberBytes,
                               &Chunk->Overlapped);

            if (!Success && (GetLastError() != ERROR_IO_PENDING)) {
                fprintf(stderr,
                        "ReadFile at %lx failed, error %d\n",
                        Chunk->Overlapped.Offset,
                        GetLastError());
                exit(1);
            }
        }
        else {
            //
            // There are no more reads left to issue, just wait
            // for the pending writes to drain.
            //
            --PendingIO;

        }
    }
    //
    // All done. There is no need to call VirtualFree() to free CopyChunk 
    // buffers here. The buffers will be freed when this process exits.
    //
}