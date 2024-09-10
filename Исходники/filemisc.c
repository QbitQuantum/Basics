BOOL
APIENTRY
MoveFileExW(
    LPCWSTR lpExistingFileName,
    LPCWSTR lpNewFileName,
    DWORD dwFlags
    )

/*++

Routine Description:

    An existing file can be renamed using MoveFile.

Arguments:

    lpExistingFileName - Supplies the name of an existing file that is to be
        renamed.

    lpNewFileName - Supplies the new name for the existing file.  The new
        name must reside in the same file system/drive as the existing
        file and must not already exist.

    dwFlags - Supplies optional flag bits to control the behavior of the
        rename.  The following bits are currently defined:

        MOVEFILE_REPLACE_EXISTING - if the new file name exists, replace
            it by renaming the old file name on top of the new file name.

        MOVEFILE_COPY_ALLOWED - if the new file name is on a different
            volume than the old file name, and causes the rename operation
            to fail, then setting this flag allows the MoveFileEx API
            call to simulate the rename with a call to CopyFile followed
            by a call to DeleteFile to the delete the old file if the
            CopyFile was successful.

        MOVEFILE_DELAY_UNTIL_REBOOT - dont actually do the rename now, but
            instead queue the rename so that it will happen the next time
            the system boots.  If this flag is set, then the lpNewFileName
            parameter may be NULL, in which case a delay DeleteFile of
            the old file name will occur the next time the system is
            booted.

            The delay rename/delete operations occur immediately after
            AUTOCHK is run, but prior to creating any paging files, so
            it can be used to delete paging files from previous boots
            before they are reused.

        MOVEFILE_WRITE_THROUGH - perform the rename operation in such a
            way that the file has actually been moved on the disk before
            the API returns to the caller.  Note that this flag causes a
            flush at the end of a copy operation (if one were allowed and
            necessary), and has no effect if the rename operation is
            delayed until the next reboot.

Return Value:

    TRUE - The operation was successful.

    FALSE/NULL - The operation failed. Extended error status is available
        using GetLastError.

--*/

{
    NTSTATUS Status;
    BOOLEAN ReplaceIfExists;
    OBJECT_ATTRIBUTES Obja;
    HANDLE Handle;
    UNICODE_STRING OldFileName;
    UNICODE_STRING NewFileName;
    IO_STATUS_BLOCK IoStatusBlock;
    PFILE_RENAME_INFORMATION NewName;
    BOOLEAN TranslationStatus;
    RTL_RELATIVE_NAME RelativeName;
    PVOID FreeBuffer;
    ULONG OpenFlags;
    BOOLEAN fDoCrossVolumeMove;
    BOOLEAN b;

#ifdef _CAIRO_
    OBJECTID oid;
    OBJECTID *poid; // only can be valid when fDoCrossVolumeMove = TRUE
#else
    PVOID poid = NULL;
#endif

    //
    // if the target is a device, do not allow the rename !
    //
    if ( lpNewFileName ) {
        if ( RtlIsDosDeviceName_U((PWSTR)lpNewFileName) ) {
            SetLastError(ERROR_ALREADY_EXISTS);
            return FALSE;
        }
    }

    if (dwFlags & MOVEFILE_REPLACE_EXISTING) {
        ReplaceIfExists = TRUE;
    } else {
        ReplaceIfExists = FALSE;
    }

    TranslationStatus = RtlDosPathNameToNtPathName_U(
                            lpExistingFileName,
                            &OldFileName,
                            NULL,
                            &RelativeName
                            );

    if ( !TranslationStatus ) {
        SetLastError(ERROR_PATH_NOT_FOUND);
        return FALSE;
    }

    FreeBuffer = OldFileName.Buffer;

    if (!(dwFlags & MOVEFILE_DELAY_UNTIL_REBOOT)) {

        if ( RelativeName.RelativeName.Length ) {
            OldFileName = *(PUNICODE_STRING)&RelativeName.RelativeName;
        } else {
            RelativeName.ContainingDirectory = NULL;
        }
        InitializeObjectAttributes(
            &Obja,
            &OldFileName,
            OBJ_CASE_INSENSITIVE,
            RelativeName.ContainingDirectory,
            NULL
            );

        //
        // Open the file for delete access
        //

        OpenFlags = FILE_SYNCHRONOUS_IO_NONALERT |
                    FILE_OPEN_FOR_BACKUP_INTENT |
                    (dwFlags & MOVEFILE_WRITE_THROUGH) ? FILE_WRITE_THROUGH : 0;

        Status = NtOpenFile(
                    &Handle,
#ifdef _CAIRO_
                    FILE_READ_ATTRIBUTES |
#endif
                    (ACCESS_MASK)DELETE | SYNCHRONIZE,
                    &Obja,
                    &IoStatusBlock,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    OpenFlags
                    );

        if ( !NT_SUCCESS(Status) ) {
            RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);
            BaseSetLastNTError(Status);
            return FALSE;
        }
    }

    if (!(dwFlags & MOVEFILE_DELAY_UNTIL_REBOOT) ||
        (lpNewFileName != NULL)) {
        TranslationStatus = RtlDosPathNameToNtPathName_U(
                                lpNewFileName,
                                &NewFileName,
                                NULL,
                                NULL
                                );

        if ( !TranslationStatus ) {
            RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);
            SetLastError(ERROR_PATH_NOT_FOUND);
            NtClose(Handle);
            return FALSE;
            }
    } else {
        RtlInitUnicodeString( &NewFileName, NULL );
    }

    if (dwFlags & MOVEFILE_DELAY_UNTIL_REBOOT) {
        //
        // copy allowed is not permitted on delayed renames
        //


        //
        // (typical stevewo hack, preserved for sentimental value)
        //
        // If ReplaceIfExists is TRUE, prepend an exclamation point
        // to the new filename in order to pass this bit of data
        // along to the session manager.
        //
        if (ReplaceIfExists &&
            (NewFileName.Length != 0)) {
            PWSTR NewBuffer;

            NewBuffer = RtlAllocateHeap( RtlProcessHeap(),
                                         MAKE_TAG( TMP_TAG ),
                                         NewFileName.Length + sizeof(WCHAR) );
            if (NewBuffer != NULL) {
                NewBuffer[0] = L'!';
                CopyMemory(&NewBuffer[1], NewFileName.Buffer, NewFileName.Length);
                NewFileName.Length += sizeof(WCHAR);
                NewFileName.MaximumLength += sizeof(WCHAR);
                RtlFreeHeap(RtlProcessHeap(), 0, NewFileName.Buffer);
                NewFileName.Buffer = NewBuffer;
            }
        }

        if ( dwFlags & MOVEFILE_COPY_ALLOWED ) {
            Status = STATUS_INVALID_PARAMETER;
        } else {
            Status = BasepMoveFileDelayed(&OldFileName, &NewFileName);
        }
        RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);
        RtlFreeHeap(RtlProcessHeap(), 0, NewFileName.Buffer);

        if (NT_SUCCESS(Status)) {
            return(TRUE);
        } else {
            BaseSetLastNTError(Status);
            return(FALSE);
        }
    }

    RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);
    FreeBuffer = NewFileName.Buffer;

    NewName = RtlAllocateHeap(RtlProcessHeap(), MAKE_TAG( TMP_TAG ), NewFileName.Length+sizeof(*NewName));
    if (NewName != NULL) {
        RtlMoveMemory( NewName->FileName, NewFileName.Buffer, NewFileName.Length );

        NewName->ReplaceIfExists = ReplaceIfExists;
        NewName->RootDirectory = NULL;
        NewName->FileNameLength = NewFileName.Length;
        RtlFreeHeap(RtlProcessHeap(), 0, FreeBuffer);

        Status = NtSetInformationFile(
                    Handle,
                    &IoStatusBlock,
                    NewName,
                    NewFileName.Length+sizeof(*NewName),
                    FileRenameInformation
                    );
        RtlFreeHeap(RtlProcessHeap(), 0, NewName);
    } else {
        Status = STATUS_NO_MEMORY;
    }

    fDoCrossVolumeMove = (Status == STATUS_NOT_SAME_DEVICE) &&
                         (dwFlags & MOVEFILE_COPY_ALLOWED);

#ifdef _CAIRO_
    if (fDoCrossVolumeMove)
    {
        // Get the object'd OBJECTID
        poid = RtlQueryObjectId(Handle, &oid) == STATUS_SUCCESS ? &oid : NULL;
    }
#endif

    NtClose(Handle);
    if ( NT_SUCCESS(Status) ) {
        return TRUE;
    } else if ( fDoCrossVolumeMove ) {
        HELPER_CONTEXT Context;

        Context.pObjectId = poid;
        Context.dwFlags = dwFlags;
        b = CopyFileExW(
                lpExistingFileName,
                lpNewFileName,
                poid || dwFlags & MOVEFILE_WRITE_THROUGH ? BasepCrossVolumeMoveHelper : NULL,
                &Context,
                NULL,
                ReplaceIfExists ? 0 : COPY_FILE_FAIL_IF_EXISTS
                );
        if ( b ) {

            //
            // the copy worked... Delete the source of the rename
            // if it fails, try a set attributes and then a delete
            //

            if (!DeleteFileW( lpExistingFileName ) ) {

                //
                // If the delete fails, we will return true, but possibly
                // leave the source dangling
                //

                SetFileAttributesW(lpExistingFileName,FILE_ATTRIBUTE_NORMAL);
                DeleteFileW( lpExistingFileName );

            }
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        BaseSetLastNTError(Status);
        return FALSE;
    }
}