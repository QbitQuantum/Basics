BOOLEAN
SepAdtInitializePrivilegeAuditing(
    VOID
    )

/*++

Routine Description:

    Checks to see if there is an entry in the registry telling us to do full privilege auditing
    (which currently means audit everything we normall audit, plus backup and restore privileges).

Arguments:

    None

Return Value:

    BOOLEAN - TRUE if Auditing has been initialized correctly, else FALSE.

--*/

{
    HANDLE KeyHandle;
    NTSTATUS Status;
    NTSTATUS TmpStatus;
    OBJECT_ATTRIBUTES Obja;
    ULONG ResultLength;
    UNICODE_STRING KeyName;
    UNICODE_STRING ValueName;
    CHAR KeyInfo[sizeof(KEY_VALUE_PARTIAL_INFORMATION) + sizeof(BOOLEAN)];
    PKEY_VALUE_PARTIAL_INFORMATION pKeyInfo;
    BOOLEAN Verbose;

    PAGED_CODE();

    //
    // Query the registry to set up the privilege auditing filter.
    //

    RtlInitUnicodeString( &KeyName, L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Lsa");

    InitializeObjectAttributes( &Obja,
                                &KeyName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL
                                );

    Status = NtOpenKey(
                 &KeyHandle,
                 KEY_QUERY_VALUE | KEY_SET_VALUE,
                 &Obja
                 );


    if (!NT_SUCCESS( Status )) {

        if (Status == STATUS_OBJECT_NAME_NOT_FOUND) {

            return ( SepInitializePrivilegeFilter( FALSE ));

        } else {

            return( FALSE );
        }
    }

    RtlInitUnicodeString( &ValueName, FULL_PRIVILEGE_AUDITING );

    Status = NtQueryValueKey(
                 KeyHandle,
                 &ValueName,
                 KeyValuePartialInformation,
                 KeyInfo,
                 sizeof(KeyInfo),
                 &ResultLength
                 );

    TmpStatus = NtClose(KeyHandle);
    ASSERT(NT_SUCCESS(TmpStatus));

    if (!NT_SUCCESS( Status )) {

        Verbose = FALSE;

    } else {

        pKeyInfo = (PKEY_VALUE_PARTIAL_INFORMATION)KeyInfo;
        Verbose = (BOOLEAN) *(pKeyInfo->Data);
    }

    return ( SepInitializePrivilegeFilter( Verbose ));
}