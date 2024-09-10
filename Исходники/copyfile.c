NET_API_STATUS
ReplCopyFile(
    IN LPCTSTR SourcePath,
    IN LPCTSTR DestPath,
    IN BOOL bFailIfExists
    )

/*++

Routine Description:

    ReplCopyFile copies everthing contained in a file.  ("Everything" includes
    data, alternate data, extended attributes, attributes, timestamps, and
    security info.)

Arguments:

    SourcePath - Points to source file path, which might be a UNC name.

    DestPath - Points to destination file path name.

    bFailIfExists - a boolean which is TRUE iff this routine should fail
        if the destination already exists.

Return Value:

    NET_API_STATUS

Threads:

    Used by client and syncer threads.

--*/

{
    NET_API_STATUS       ApiStatus;
    BOOL                 DestExists;
    HANDLE               DestHandle = INVALID_HANDLE_VALUE;
    PSECURITY_ATTRIBUTES DestSecurityAttr = NULL;
    DWORD                SourceAttributes = (DWORD) (-1);

#ifdef USE_BACKUP_APIS
    DWORD ActualBufferSizeRead = 0;
    DWORD ActualBufferSizeWritten;
    LPVOID BackupBuffer = NULL;
    LPVOID DestContext = NULL;
    LPVOID SourceContext = NULL;
    HANDLE SourceHandle = INVALID_HANDLE_VALUE;
#endif


    //
    // Check for caller errors.
    //

    NetpAssert( SourcePath != NULL );
    NetpAssert( (*SourcePath) != TCHAR_EOS );
    NetpAssert( STRLEN(SourcePath) <= PATHLEN );
    NetpAssert( DestPath != NULL );
    NetpAssert( (*DestPath) != TCHAR_EOS );
    NetpAssert( STRLEN(DestPath) <= PATHLEN );

    DestExists = ReplFileOrDirExists( DestPath );
    if (bFailIfExists && DestExists) {
        // DON'T GOTO CLEANUP FROM HERE, AS IT WOULD DELETE FILE!!!
        return (ERROR_ALREADY_EXISTS);
    }

    //
    // What kind of source (file/directory) is it?
    //

    SourceAttributes = GetFileAttributes( (LPTSTR) SourcePath );

    if ( SourceAttributes == (DWORD) -1 ) {

        //
        // File doesn't exist, bad syntax, or something along those lines.
        //
        ApiStatus = (NET_API_STATUS) GetLastError();
        NetpAssert( ApiStatus != NO_ERROR );
        // DON'T GOTO CLEANUP FROM HERE, AS IT WOULD DELETE FILE!!!
        return (ApiStatus);

    } else if ((SourceAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {

        //
        // Source is a directory tree.  We don't handle this!
        //
        NetpKdPrint(( PREFIX_REPL_CLIENT
                "ReplCopyFile: source is directory!  path: '"
                FORMAT_LPTSTR "', src attr " FORMAT_HEX_DWORD ".\n",
                SourcePath, SourceAttributes ));
        ApiStatus = NERR_InternalError;
        // DON'T GOTO CLEANUP FROM HERE, AS IT WOULD DELETE FILE!!!
        return (ApiStatus);

    } else {

        //
        // Simple case: source exists and is just a single file.
        // Start off by setting desired destination security attributes.
        //

        ApiStatus = ReplMakeSecurityAttributes(
                SourcePath,
                &DestSecurityAttr );  // alloc and set ptr
        if (ApiStatus==ERROR_NOT_SUPPORTED) {

            // Just downlevel master, so set default security and continue.
            DestSecurityAttr = NULL;

        } else if (ApiStatus != NO_ERROR) {
            // DON'T GOTO CLEANUP FROM HERE, AS IT WOULD DELETE FILE!!!
            return (ApiStatus);
        } else {
            NetpAssert( ApiStatus == NO_ERROR );
            NetpAssert( DestSecurityAttr != NULL );
        }

#ifdef USE_BACKUP_APIS
        //
        // Open source file.
        //
        SourceHandle = CreateFile(
                SourcePath,
                GENERIC_READ,           // desired access
                FILE_SHARE_READ,        // share mode
                NULL,                   // no security attributes
                OPEN_EXISTING,          // open if exists; fail if not.
                FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_SEQUENTIAL_SCAN,  // flags
                (HANDLE) NULL           // no template
                );

        if (SourceHandle == INVALID_HANDLE_VALUE) {
            ApiStatus = (NET_API_STATUS) GetLastError();

            NetpKdPrint(( PREFIX_REPL_CLIENT
                    "ReplCopyFile: open of source '" FORMAT_LPTSTR
                    "' gave status " FORMAT_API_STATUS ".\n",
                    SourcePath, ApiStatus ));

            NetpAssert( ApiStatus != NO_ERROR );

            if (DestSecurityAttr != NULL) {
                NetpMemoryFree( DestSecurityAttr );
            }

            // DON'T GOTO CLEANUP FROM HERE, AS IT WOULD DELETE FILE!!!
            return (ApiStatus);
        }
#endif

        //
        // Delete the destination file.  Why?  Because...
        // We're going to set the security on destination file using
        // the CreateFile API.  This will ignore setting the security if the
        // file already exists.  So, we need to delete it to force this to
        // happen.
        //

        if (DestExists) {
            ApiStatus = ReplDeleteFile( DestPath );
            if (ApiStatus != NO_ERROR) {
                goto Cleanup;
            }
        }
        NetpAssert( !ReplFileOrDirExists( DestPath ) );

        //
        // Open dest file.  Since we already deleted any existing one, we know
        // this will create the file from scratch.  This is important, because
        // we're depending on CreateFile's use of DestSecurityAttr to set
        // security on the file.
        //

        DestHandle = CreateFile(
                DestPath,
                GENERIC_WRITE           // desired...
                | WRITE_DAC             //   ...
                | WRITE_OWNER,          //     access
                FILE_SHARE_WRITE,                      // share mode: none
                DestSecurityAttr,       // desired security attributes
                CREATE_NEW,             // disposition create new (fail exist)
#ifdef USE_BACKUP_APIS
                FILE_FLAG_BACKUP_SEMANTICS,  // flags
#else
                0,                      // flags
#endif
                (HANDLE) NULL           // no template
                );

        if (DestHandle == INVALID_HANDLE_VALUE) {
            ApiStatus = (NET_API_STATUS) GetLastError();

            NetpKdPrint(( PREFIX_REPL_CLIENT
                    "ReplCopyFile: open of dest '" FORMAT_LPTSTR
                    "' gave status " FORMAT_API_STATUS ".\n",
                    DestPath, ApiStatus ));

            NetpAssert( ApiStatus != NO_ERROR );
            goto Cleanup;
        }

#ifndef USE_BACKUP_APIS

        //
        // Close the dest file and copy the data.
        // (In this case, we're using CopyFile API, which is not handle-based.)
        //

        NetpAssert( DestHandle != INVALID_HANDLE_VALUE );
        (VOID) CloseHandle( DestHandle );
        DestHandle = INVALID_HANDLE_VALUE;

        if ( !CopyFile(
                (LPTSTR) SourcePath,
                (LPTSTR) DestPath,
                FALSE  /* don't fail if exists */  ) ) {

            ApiStatus = (NET_API_STATUS) GetLastError();
            NetpAssert( ApiStatus != NO_ERROR );
            goto Cleanup;

        }

        NetpAssert( ReplFileOrDirExists( DestPath ) );

        // Timestamps and attributes will be copied below.
        // BUGBUG  no way to copy EAs, alt data.
        ApiStatus = NO_ERROR;


#else  // defined(USE_BACKUP_APIS)

        BackupBuffer = NetpMemoryAllocate( REPL_BACKUP_BUFFER_SIZE );
        if (BackupBuffer == NULL) {
            ApiStatus = ERROR_NOT_ENOUGH_MEMORY;
            goto Cleanup;
        }


        IF_DEBUG( SYNC ) {
            NetpKdPrint(( PREFIX_REPL_CLIENT
                    "ReplCopyFile: copying" ));
        }

        for (;;) {  // until end of file...

            IF_DEBUG( SYNC ) {
                NetpKdPrint(( "<" ));
            }

            if ( !BackupRead(
                    SourceHandle,
                    BackupBuffer,
                    REPL_BACKUP_BUFFER_SIZE,
                    & ActualBufferSizeRead,
                    FALSE,              // don't abort yet
                    REPL_PROCESS_SECURITY,
                    & SourceContext
                    ) ) {

                // Process read error.
                ApiStatus = (NET_API_STATUS) GetLastError();

                NetpKdPrint(( PREFIX_REPL_CLIENT
                        "ReplCopyFile: BackupRead"
                        " gave status " FORMAT_API_STATUS ".\n",
                        ApiStatus ));
                NetpAssert( ApiStatus != NO_ERROR );
                goto Cleanup;
            }

            // No error on read, how about EOF?
            if (ActualBufferSizeRead == 0) {  // normal end of file.
                ApiStatus = NO_ERROR;

                IF_DEBUG( SYNC ) {
                    NetpKdPrint(( "DONE(OK)\n" ));
                }

                break;
            }

            IF_DEBUG( SYNC ) {
                NetpKdPrint(( ">" ));
            }

            if ( !BackupWrite(
                    DestHandle,
                    BackupBuffer,
                    ActualBufferSizeRead,
                    & ActualBufferSizeWritten,
                    FALSE,              // don't abort yet
                    REPL_PROCESS_SECURITY,
                    & DestContext
                    ) ) {

                ApiStatus = (NET_API_STATUS) GetLastError();
                NetpKdPrint(( PREFIX_REPL_CLIENT
                        "ReplCopyFile: BackupWrite"
                        " gave status " FORMAT_API_STATUS ".\n",
                        ApiStatus ));
                NetpAssert( ApiStatus != NO_ERROR );
                goto Cleanup;
            }

        } // until end of file
        ApiStatus = NO_ERROR;


#endif


    } // else (just single file)