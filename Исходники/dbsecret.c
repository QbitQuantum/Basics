NTSTATUS
LsarSetSecret(
    IN LSAPR_HANDLE SecretHandle,
    IN OPTIONAL PLSAPR_CR_CIPHER_VALUE CipherCurrentValue,
    IN OPTIONAL PLSAPR_CR_CIPHER_VALUE CipherOldValue
    )

/*++

Routine Description:

    This function is the LSA server RPC worker routine for the LsaSetSecret
    API.

    The LsaSetSecret API optionally sets one or both values associated with
    a Secret object.  These values are known as the Current Value and
    Old Value of the Secret object and these values have a meaning known to
    the creator of the object.

    This worker routine receives the Secret values in encrypted form from
    the client.  A two-way encryption algorithm using the Session Key will
    havge been applied.  The values received will first be decrypted using
    this same key and then two-way encrypted using the LSA Database Private
    Encryption Key.  The resulting re-encrypted values will then be stored
    as attributes of the Secret object.

Arguments:

    SecretHandle - Handle from an LsaOpenSecret or LsaCreateSecret call.

    CipherCurrentValue - Optional pointer to an encrypted value structure
        containing the Current Value (if any) to be set for the Secret
        Object (if any).  This value is two-way encrypted with the Session
        Key.  If NULL is specified, the existing Current Value will be left
        assigned to the object will be left unchanged.

    CipherOldValue - Optional pointer to an encrypted value structure
        containing the "old value" (if any) to be set for the Secret
        Object (if any).  If NULL is specified, the existing Old Value will be
        assigned to the object will be left unchanged.

Return Value:

    NTSTATUS - Standard Nt Result Code

        STATUS_ACCESS_DENIED - Caller does not have the appropriate access
            to complete the operation.

        STATUS_INVALID_HANDLE - Handle is invalid.
--*/

{
    NTSTATUS Status;
    LSAP_DB_HANDLE Handle = (LSAP_DB_HANDLE) SecretHandle;

    PLSAP_CR_CLEAR_VALUE ClearCurrentValue = NULL;
    PLSAP_CR_CLEAR_VALUE ClearOldValue = NULL;
    PLSAP_CR_CIPHER_VALUE DbCipherCurrentValue = NULL;
    ULONG DbCipherCurrentValueLength;
    PLSAP_CR_CIPHER_VALUE DbCipherOldValue = NULL;
    ULONG DbCipherOldValueLength;
    PLSAP_CR_CIPHER_KEY SessionKey = NULL;
    LARGE_INTEGER UpdatedTime;
    BOOLEAN ObjectReferenced = FALSE;
    LSAP_DB_HANDLE InternalHandle = (LSAP_DB_HANDLE) SecretHandle;
    ULONG ReferenceOptions = LSAP_DB_ACQUIRE_LOCK | LSAP_DB_START_TRANSACTION;
    ULONG DereferenceOptions = LSAP_DB_RELEASE_LOCK | LSAP_DB_FINISH_TRANSACTION;
    BOOLEAN GlobalSecret;

    //
    // Check for Local Secret set request.  If the Secret name does
    // not begin with the Global Secret Prefix, the Secret is local.  In
    // this case, update of the secret is allowed on BDC's as well as
    // PDC's and Workstations.  Creation of Global Secrets is not
    // allowed on BDC's except for trusted callers such as a Replicator.
    //

    Status = LsapDbGetScopeSecret(
                 (PLSAPR_UNICODE_STRING) &InternalHandle->LogicalNameU,
                 &GlobalSecret
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    if (!GlobalSecret) {

        ReferenceOptions |= LSAP_DB_OMIT_BACKUP_CONTROLLER_CHECK;
        DereferenceOptions |= LSAP_DB_OMIT_REPLICATOR_NOTIFICATION;
    }

    //
    // If the client is non-trusted, obtain the Session Key used by the
    // client to two-way encrypt the Current Value and/or Old Values.
    //

    if (!InternalHandle->Trusted) {

        Status = LsapCrServerGetSessionKey( SecretHandle, &SessionKey);

        if (!NT_SUCCESS(Status)) {

            goto SetSecretError;
        }
    }

    //
    // Acquire the Lsa Database lock.  Verify that the Secret Object handle is
    // valid, is of the expected type and has all of the desired accesses
    // granted.  Reference the handle and open a database transaction.
    //

    Status = LsapDbReferenceObject(
                 SecretHandle,
                 SECRET_SET_VALUE,
                 SecretObject,
                 ReferenceOptions
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    ObjectReferenced = TRUE;

    //
    // If a Current Value is specified for the Secret Object, and the
    // client is non-trusted, decrypt the value using the Session Key and
    // encrypt it using the LSA Database System Key.  Then (for all
    // clients) encrypt the resulting value with the internal LSA Database
    // encryption key and write resulting Value structure (header followed by
    // buffer to the Policy Database as the Current Value attribute of the
    // Secret object.  If no Current Value is specified, or a NULL
    // string is specified, the existing Current Value will be deleted.
    //

    if (ARGUMENT_PRESENT(CipherCurrentValue)) {

        if (!InternalHandle->Trusted) {

            Status = LsapCrDecryptValue(
                         (PLSAP_CR_CIPHER_VALUE) CipherCurrentValue,
                         SessionKey,
                         &ClearCurrentValue
                         );

            if (!NT_SUCCESS(Status)) {

                goto SetSecretError;
            }

        } else {

            ClearCurrentValue = (PLSAP_CR_CLEAR_VALUE) CipherCurrentValue;
        }

        Status = LsapCrEncryptValue(
                     ClearCurrentValue,
                     LsapDbCipherKey,
                     &DbCipherCurrentValue
                     );

        if (!NT_SUCCESS(Status)) {

            goto SetSecretError;
        }

        DbCipherCurrentValueLength = DbCipherCurrentValue->Length
            + (ULONG) sizeof(LSAP_CR_CIPHER_VALUE);

    } else {

        DbCipherCurrentValue = NULL;
        DbCipherCurrentValueLength = 0;
    }

    Status = LsapDbWriteAttributeObject(
                 SecretHandle,
                 &LsapDbNames[CurrVal],
                 DbCipherCurrentValue,
                 DbCipherCurrentValueLength
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    //
    // Store the time at which the Current Secret value was last updated.
    //

    Status = NtQuerySystemTime(&UpdatedTime);

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    Status = LsapDbWriteAttributeObject(
                 SecretHandle,
                 &LsapDbNames[CupdTime],
                 &UpdatedTime,
                 sizeof (LARGE_INTEGER)
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    //
    // If an Old Value is specified for the Secret Object, and the
    // client is non-trusted, decrypt the value using the Session Key and
    // encrypt it using the LSA Database System Key.  Then (for all
    // clients) encrypt the resulting value with the internal LSA Database
    // encryption key and write resulting Value structure (header followed by
    // buffer to the Policy Database as the Old Value attribute of the
    // Secret object.  If no Old Value is specified, or a NULL
    // string is specified, the existing Old Value will be deleted.
    //

    if (ARGUMENT_PRESENT(CipherOldValue)) {

        if (!InternalHandle->Trusted) {

            Status = LsapCrDecryptValue(
                         (PLSAP_CR_CIPHER_VALUE) CipherOldValue,
                         SessionKey,
                         &ClearOldValue
                         );

            if (!NT_SUCCESS(Status)) {

                goto SetSecretError;
            }

        } else {

            ClearOldValue = (PLSAP_CR_CLEAR_VALUE) CipherOldValue;
        }

        Status = LsapCrEncryptValue(
                     ClearOldValue,
                     LsapDbCipherKey,
                     &DbCipherOldValue
                     );

        if (!NT_SUCCESS(Status)) {

            goto SetSecretError;
        }

        DbCipherOldValueLength =
            DbCipherOldValue->Length + (ULONG) sizeof(LSAP_CR_CIPHER_VALUE);

    } else {

        DbCipherOldValue = NULL;
        DbCipherOldValueLength = 0;
    }

    Status = LsapDbWriteAttributeObject(
                 SecretHandle,
                 &LsapDbNames[OldVal],
                 DbCipherOldValue,
                 DbCipherOldValueLength
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

    //
    // Store the time at which the Old Secret value was last updated.
    //

    Status = LsapDbWriteAttributeObject(
                 SecretHandle,
                 &LsapDbNames[OupdTime],
                 &UpdatedTime,
                 sizeof (LARGE_INTEGER)
                 );

    if (!NT_SUCCESS(Status)) {

        goto SetSecretError;
    }

SetSecretFinish:

    //
    // If necessary, free memory allocated for the Session Key.
    //

    if (SessionKey != NULL) {

        MIDL_user_free(SessionKey);
        SessionKey = NULL;
    }

    //
    // If necessary, free memory allocated for Decrypted Current Value.
    // Note that for trusted clients, the decryption is the identity
    // mapping, so do not do the free in this case.
    //

    if ((ClearCurrentValue != NULL) && !InternalHandle->Trusted) {

        LsapCrFreeMemoryValue( ClearCurrentValue );
        ClearCurrentValue = NULL;
    }

    //
    // If necessary, free memory allocated for Decrypted Old Value.
    // Note that for trusted clients, the decryption is the identity
    // mapping, so do not do the free in this case.
    //

    if ((ClearOldValue != NULL) && !InternalHandle->Trusted) {

        LsapCrFreeMemoryValue( ClearOldValue );
        ClearOldValue = NULL;
    }

    //
    // If necessary, free memory allocated for the Current Value
    // encrypted for storage in the LSA Database.
    //

    if (DbCipherCurrentValue != NULL) {

        LsapCrFreeMemoryValue( DbCipherCurrentValue );
        DbCipherCurrentValue = NULL;
    }

    //
    // If necessary, free memory allocated for the Old Value
    // encrypted for storage in the LSA Database.
    //

    if (DbCipherOldValue != NULL) {

        LsapCrFreeMemoryValue( DbCipherOldValue );
        DbCipherOldValue = NULL;
    }

    //
    // If necessary, dereference the Secret object, close the database
    // transaction, notify the LSA Database Replicator of the change,
    // release the LSA Database lock and return.
    //

    if (ObjectReferenced) {

        Status = LsapDbDereferenceObject(
                     &SecretHandle,
                     SecretObject,
                     DereferenceOptions,
                     SecurityDbChange,
                     Status
                     );
    }

    return(Status);

SetSecretError:

    goto SetSecretFinish;
}