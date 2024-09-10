VOID Delete(
    IN PCHAR FileName
    )
{
    NTSTATUS Status;

    HANDLE FileHandle;
    OBJECT_ATTRIBUTES ObjectAttributes;
    STRING NameString;
    IO_STATUS_BLOCK IoStatus;

    //
    //  Get the filename
    //

    simprintf("Delete ", 0); simprintf(FileName, 0); simprintf("\n", 0);

    //
    //  Open the file for delete access
    //

    RtlInitString( &NameString, FileName );
    InitializeObjectAttributes( &ObjectAttributes, &NameString, 0, NULL, NULL );
    if (!NT_SUCCESS(Status = NtCreateFile( &FileHandle,
                                           DELETE | SYNCHRONIZE,
                                           &ObjectAttributes,
                                           &IoStatus,
                                           (PLARGE_INTEGER)NULL,
                                           0L,
                                           0L,
                                           FILE_OPEN,
                                           WriteThrough,
                                           (PVOID)NULL,
                                           0L ))) {
        CreateFileError( Status, FileName );
        return;
    }

    //
    //  Mark the file for delete
    //

    ((PFILE_DISPOSITION_INFORMATION)&Buffer[0])->DeleteFile = TRUE;

    if (!NT_SUCCESS(Status = NtSetInformationFile( FileHandle,
                                                   &IoStatus,
                                                   Buffer,
                                                   sizeof(FILE_DISPOSITION_INFORMATION),
                                                   FileDispositionInformation))) {
        SetInformationFileError( Status );
        return;
    }

    //
    //  Now close the file
    //

    if (!NT_SUCCESS(Status = NtClose( FileHandle ))) {
        CloseError( Status );
    }

    //
    //  And return to our caller
    //

    return;
}