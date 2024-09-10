NTSTATUS
NTAPI
INIT_FUNCTION
IopReassignSystemRoot(IN PLOADER_PARAMETER_BLOCK LoaderBlock,
                      OUT PANSI_STRING NtBootPath)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;
    CHAR Buffer[256], AnsiBuffer[256];
    WCHAR ArcNameBuffer[64];
    ANSI_STRING TargetString, ArcString, TempString;
    UNICODE_STRING LinkName, TargetName, ArcName;
    HANDLE LinkHandle;

    /* Create the Unicode name for the current ARC boot device */
    sprintf(Buffer, "\\ArcName\\%s", LoaderBlock->ArcBootDeviceName);
    RtlInitAnsiString(&TargetString, Buffer);
    Status = RtlAnsiStringToUnicodeString(&TargetName, &TargetString, TRUE);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Initialize the attributes and open the link */
    InitializeObjectAttributes(&ObjectAttributes,
                               &TargetName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenSymbolicLinkObject(&LinkHandle,
                                      SYMBOLIC_LINK_ALL_ACCESS,
                                      &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        /* We failed, free the string */
        RtlFreeUnicodeString(&TargetName);
        return FALSE;
    }

    /* Query the current \\SystemRoot */
    ArcName.Buffer = ArcNameBuffer;
    ArcName.Length = 0;
    ArcName.MaximumLength = sizeof(ArcNameBuffer);
    Status = NtQuerySymbolicLinkObject(LinkHandle, &ArcName, NULL);
    if (!NT_SUCCESS(Status))
    {
        /* We failed, free the string */
        RtlFreeUnicodeString(&TargetName);
        return FALSE;
    }

    /* Convert it to Ansi */
    ArcString.Buffer = AnsiBuffer;
    ArcString.Length = 0;
    ArcString.MaximumLength = sizeof(AnsiBuffer);
    Status = RtlUnicodeStringToAnsiString(&ArcString, &ArcName, FALSE);
    AnsiBuffer[ArcString.Length] = ANSI_NULL;

    /* Close the link handle and free the name */
    ObCloseHandle(LinkHandle, KernelMode);
    RtlFreeUnicodeString(&TargetName);

    /* Setup the system root name again */
    RtlInitAnsiString(&TempString, "\\SystemRoot");
    Status = RtlAnsiStringToUnicodeString(&LinkName, &TempString, TRUE);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Open the symbolic link for it */
    InitializeObjectAttributes(&ObjectAttributes,
                               &LinkName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenSymbolicLinkObject(&LinkHandle,
                                      SYMBOLIC_LINK_ALL_ACCESS,
                                      &ObjectAttributes);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Destroy it */
    NtMakeTemporaryObject(LinkHandle);
    ObCloseHandle(LinkHandle, KernelMode);

    /* Now create the new name for it */
    sprintf(Buffer, "%s%s", ArcString.Buffer, LoaderBlock->NtBootPathName);

    /* Copy it into the passed parameter and null-terminate it */
    RtlCopyString(NtBootPath, &ArcString);
    Buffer[strlen(Buffer) - 1] = ANSI_NULL;

    /* Setup the Unicode-name for the new symbolic link value */
    RtlInitAnsiString(&TargetString, Buffer);
    InitializeObjectAttributes(&ObjectAttributes,
                               &LinkName,
                               OBJ_CASE_INSENSITIVE | OBJ_PERMANENT,
                               NULL,
                               NULL);
    Status = RtlAnsiStringToUnicodeString(&ArcName, &TargetString, TRUE);
    if (!NT_SUCCESS(Status)) return FALSE;

    /* Create it */
    Status = NtCreateSymbolicLinkObject(&LinkHandle,
                                        SYMBOLIC_LINK_ALL_ACCESS,
                                        &ObjectAttributes,
                                        &ArcName);

    /* Free all the strings and close the handle and return success */
    RtlFreeUnicodeString(&ArcName);
    RtlFreeUnicodeString(&LinkName);
    ObCloseHandle(LinkHandle, KernelMode);
    return TRUE;
}