VOID
ReBaseFile(
    LPSTR CurrentImageName,
    BOOL fReBase
    )
{
    DWORD dw;
    CHAR  Buffer[ MAX_PATH+1 ];
    LPSTR FilePart;
    ULONG ThisImageExpectedSize = 0;
    ULONG ThisImageRequestedBase = NewImageBase;
    ULONG TimeStamp;

    if ( !InitialBase && !BaseAddrFile ) {
        fprintf( stderr, "REBASE: -b switch must specify a non-zero base  --or--\n" );
        fprintf( stderr, "        -i must specify a filename\n" );
        exit( REBASE_ERR );
        }

    if ( BaseAddrFile && ( InitialBase || fGoingDown || CoffBaseDotTxt ) ) {
        fprintf( stderr, "REBASE: -i is incompatible with -b, -d, and -c\n" );
        exit( REBASE_ERR );
    }

    dw = GetFullPathName( CurrentImageName, sizeof(Buffer), Buffer, &FilePart );
    if ( dw == 0 || dw > sizeof(Buffer) ) {
        FilePart = CurrentImageName;
    }
    _strlwr( FilePart );  // Lowercase for consistency when displayed.

    if ( BaseAddrFile && !(ThisImageRequestedBase = FindInBaseAddrFile( FilePart, &ThisImageExpectedSize )) ) {
        fprintf( stdout, "REBASE: %-16s Not listed in %s\n", FilePart, BaseAddrFileName );
    }

    if (fSplitSymbols && !fSumOnly ) {

        if ( SplitSymbols( CurrentImageName, (PCHAR) SymbolPath, (PCHAR) DebugFilePath, SplitFlags ) ) {
            if ( fVerbose ) {
                fprintf( stdout, "REBASE: %16s symbols split into %s\n", FilePart, DebugFilePath );
            }
        }
        else if (GetLastError() != ERROR_ALREADY_ASSIGNED && GetLastError() != ERROR_BAD_EXE_FORMAT) {
            fprintf( stdout, "REBASE: %-16s - unable to split symbols (%u)\n", FilePart, GetLastError() );
        }
    }

    NewImageSize = (ULONG) -1;  // Hack so we can tell when system images are skipped.

    time( (time_t *) &TimeStamp );

    if (!ReBaseImage( CurrentImageName,
                      (PCHAR) SymbolPath,
                      fReBase && !fSumOnly,
                      fRebaseSysfileOk,
                      fGoingDown,
                      ThisImageExpectedSize,
                      &OriginalImageSize,
                      &OriginalImageBase,
                      &NewImageSize,
                      &ThisImageRequestedBase,
                      TimeStamp ) ) {

        if (ThisImageRequestedBase == 0) {
            fprintf(stderr,
                    "REBASE: %-16s ***Grew too large (Size=0x%x; ExpectedSize=0x%x)\n",
                    FilePart,
                    OriginalImageSize,
                    ThisImageExpectedSize);
        } else {
            if (GetLastError() == ERROR_BAD_EXE_FORMAT) {
                if (fVerbose) {
                    fprintf( stderr,
                            "REBASE: %-16s DOS or OS/2 image ignored\n",
                            FilePart );
                }
            } else
            if (GetLastError() == ERROR_INVALID_ADDRESS) {
                if (fVerbose) {
                    fprintf( stderr,
                            "REBASE: %-16s Rebase failed.  Relocations are missing\n",
                            FilePart );
                }
                if (RebaseLog) {
                    fprintf( RebaseLog,
                             "%16s based at 0x%08x (size 0x%08x)  Unable to rebase.\n",
                             FilePart,
                             OriginalImageBase,
                             OriginalImageSize);
                }
            } else {
                fprintf( stderr,
                        "REBASE: *** RelocateImage failed (%s).  Image may be corrupted\n",
                        FilePart );
            }
        }

        ReturnCode = REBASE_ERR;
        return;

    } else {
        if (GetLastError() == ERROR_INVALID_DATA) {
            fprintf(stderr, "REBASE: Warning: DBG checksum did not match image.\n");
        }
    }

    // Keep track of the lowest base address.

    if (MinBase > NewImageBase) {
        MinBase = NewImageBase;
    }

    if ( fSumOnly || !fReBase ) {
        if (!fQuiet) {
            fprintf( stdout,
                     "REBASE: %16s mapped at %08x\n",
                     FilePart,
                     OriginalImageBase,
                     OriginalImageSize);
        }
    } else {
        if (RebaseLog) {
            fprintf( RebaseLog,
                     "%16s rebased to 0x%08x (size 0x%08x)\n",
                     FilePart,
                     fGoingDown ? ThisImageRequestedBase : NewImageBase,
                     NewImageSize);
        }

        if ((NewImageSize != (ULONG) -1) &&
            (OriginalImageBase != (fGoingDown ? ThisImageRequestedBase : NewImageBase)) &&
            ( fVerbose || fQuiet )
           ) {
            if ( fVerbose ) {
                fprintf( stdout,
                         "REBASE: %16s initial base at 0x%08x (size 0x%08x)\n",
                         FilePart,
                         OriginalImageBase,
                         OriginalImageSize);
            }

            fprintf( stdout,
                     "REBASE: %16s rebased to 0x%08x (size 0x%08x)\n",
                     FilePart,
                     fGoingDown ? ThisImageRequestedBase : NewImageBase,
                     NewImageSize);

            if ( fVerbose && fSplitSymbols) {
                fprintf( stdout,
                         "REBASE: %16s updated image base in %s\n",
                         FilePart,
                         DebugFilePath );
            }
        }

        if (fRemoveRelocs) {
            RemoveRelocations(CurrentImageName);
        }
    }

    if ( CoffBaseDotTxt ) {
        if ( !fCoffBaseIncExt ) {
            char *n;
            if ( n  = strrchr(FilePart,'.') ) {
                *n = '\0';
            }
        }

        fprintf( CoffBaseDotTxt,
                 "%-16s 0x%08x 0x%08x\n",
                 FilePart,
                 fSumOnly ? OriginalImageBase : (fGoingDown ? ThisImageRequestedBase : NewImageBase),
                 NewImageSize);
    }

    NewImageBase = ThisImageRequestedBase;   // Set up the next one...
}