NTSTATUS
GetRemoteNcpSecretKey (
    PUNICODE_STRING SystemName,
    CHAR *pchNWSecretKey
    )
{
    //
    //  this function returns the FPNW LSA Secret for the specified domain
    //

    NTSTATUS          ntstatus;
    OBJECT_ATTRIBUTES ObjAttributes;
    LSA_HANDLE        PolicyHandle = NULL;
    LSA_HANDLE        SecretHandle = NULL;
    UNICODE_STRING    SecretNameString;
    PUNICODE_STRING   punicodeCurrentValue;
    PUNICODE_STRING   punicodeOldValue;

    InitializeObjectAttributes( &ObjAttributes,
                                NULL,
                                0L,
                                NULL,
                                NULL );

    ntstatus = LsaOpenPolicy( SystemName,
                              &ObjAttributes,
                              POLICY_CREATE_SECRET,
                              &PolicyHandle );

    if ( !NT_SUCCESS( ntstatus ))
    {
        return( ntstatus );
    }

    RtlInitUnicodeString( &SecretNameString, NCP_LSA_SECRET_KEY );

    ntstatus = LsaOpenSecret( PolicyHandle,
                              &SecretNameString,
                              SECRET_QUERY_VALUE,
                              &SecretHandle );

    if ( !NT_SUCCESS( ntstatus ))
    {
        LsaClose( PolicyHandle );
        return( ntstatus );
    }

    //
    // Do not need the policy handle anymore.
    //

    LsaClose( PolicyHandle );

    ntstatus = LsaQuerySecret( SecretHandle,
                               &punicodeCurrentValue,
                               NULL,
                               &punicodeOldValue,
                               NULL );

    //
    // Do not need the secret handle anymore.
    //

    LsaClose( SecretHandle );

    if ( NT_SUCCESS(ntstatus) && ( punicodeCurrentValue->Buffer != NULL))
    {
        memcpy( pchNWSecretKey,
                punicodeCurrentValue->Buffer,
                min(punicodeCurrentValue->Length, USER_SESSION_KEY_LENGTH));
    }

    LsaFreeMemory( punicodeCurrentValue );
    LsaFreeMemory( punicodeOldValue );

    return( ntstatus );
}