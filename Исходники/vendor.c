NET_API_STATUS NET_API_FUNCTION
NetrRplVendorAdd(
    IN      RPL_HANDLE                  ServerHandle,
    IN      DWORD                       Level,
    OUT     LPRPL_VENDOR_INFO_STRUCT    VendorInfoStruct,
    OUT     LPDWORD                     pErrorParameter      OPTIONAL
    )
{
    LPRPL_VENDOR_INFO_1     Info;
    LPVOID                  Buffer;
    DWORD                   Error;
    DWORD                   ErrorParameter;
    PRPL_SESSION            pSession = &RG_ApiSession;

    ErrorParameter = INVALID_ERROR_PARAMETER;
    Buffer = Info = VendorInfoStruct->VendorInfo1;

    switch( Level) {
    case 1:
        if ( Info->Flags != 0) {
            ErrorParameter = VENDOR_Flags;
            break;
        }
        if ( RPL_STRING_TOO_LONG( Info->VendorComment)) {
            ErrorParameter = VENDOR_VendorComment;
            break;
        }
        if ( !ValidHexName( Info->VendorName, RPL_VENDOR_NAME_LENGTH, TRUE)) {
            ErrorParameter = VENDOR_VendorName;
            break;
        }
        _wcsupr( Info->VendorName);
        break;
    default:
        return( ERROR_INVALID_LEVEL);
        break;
    }

    if ( ErrorParameter != INVALID_ERROR_PARAMETER) {
        if ( ARGUMENT_PRESENT( pErrorParameter)) {
            *pErrorParameter = ErrorParameter;
        }
        return( ERROR_INVALID_PARAMETER);
    }

    EnterCriticalSection( &RG_ProtectDatabase);
    Call( JetBeginTransaction( pSession->SesId));

    //
    //  Verify that VendorName is available in the database.
    //
    if ( RplFind( pSession, VENDOR_TABLE_TAG, Info->VendorName)) {
        Error = NERR_RplVendorNameUnavailable;
        goto cleanup;
    }

    CallJ( JetPrepareUpdate( pSession->SesId, pSession->VendorTableId, JET_prepInsert));

    Error = VendorSetInfo( pSession, Level, Buffer, &ErrorParameter);
    if ( Error == ERROR_SUCCESS) {
        ErrorParameter = 0;
        CallJ( JetUpdate( pSession->SesId, pSession->VendorTableId, NULL, 0, NULL));
    }

cleanup:
    if ( Error == NO_ERROR) {
        Call( JetCommitTransaction( pSession->SesId, JET_bitCommitFlush));
    } else {
        Call( JetRollback( pSession->SesId, JET_bitRollbackAll));
    }
    LeaveCriticalSection( &RG_ProtectDatabase);

    if ( Error != ERROR_SUCCESS) {
         if ( ARGUMENT_PRESENT( pErrorParameter)) {
             *pErrorParameter = ErrorParameter;
         }
    }
    return( Error);
}