VOID
TestChild( VOID )
{
    NTSTATUS Status;
    STRING DirectoryName;
    HANDLE DirectoryHandle;
    OBJECT_ATTRIBUTES ObjectAttributes;

    Status = STATUS_SUCCESS;

    DbgPrint( "Entering Object Manager User Mode Child Test Program\n" );

    RtlInitString( &DirectoryName, "\\ExclusiveDir" );
    InitializeObjectAttributes( &ObjectAttributes,
                                &DirectoryName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                              );
    Status = NtOpenDirectoryObject( &DirectoryHandle,
                                    DIRECTORY_ALL_ACCESS,
                                    &ObjectAttributes
                                  );
    if (!NT_SUCCESS( Status )) {
        DbgPrint( "Unable to open %Z directory object (%X) [OK]\n",
                 &DirectoryName, Status );
        }

    InitializeObjectAttributes( &ObjectAttributes,
                                &DirectoryName,
                                OBJ_CASE_INSENSITIVE | OBJ_EXCLUSIVE,
                                NULL,
                                NULL
                              );
    Status = NtOpenDirectoryObject( &DirectoryHandle,
                                    DIRECTORY_ALL_ACCESS,
                                    &ObjectAttributes
                                  );
    if (!NT_SUCCESS( Status )) {
        DbgPrint( "Unable to open %Z directory object (%X) [OK]\n",
                 &DirectoryName, Status );
        }

    DbgPrint( "Exiting Object Manager User Mode Child Test Program with Status = %X\n", Status );
}