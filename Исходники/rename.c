int
VmDirPerformRename(
   PVDIR_OPERATION pOperation
   )
{
    ModifyReq *        modReq = &(pOperation->request.modifyReq);
    int                retVal = LDAP_SUCCESS;
    PVDIR_LDAP_RESULT  pResult = &(pOperation->ldapResult);
    ber_len_t          size = 0;
    PSTR               pszLocalErrorMsg = NULL;

    if (!_VmDirIsRenameSupported())
    {
        pResult->errCode = retVal = LDAP_UNWILLING_TO_PERFORM;
        BAIL_ON_VMDIR_ERROR_WITH_MSG( retVal, pszLocalErrorMsg, "Operation is not enabled on this server or is not supported at this domain fuctional level.");
    }

    // Get entry DN. 'm' => reqDn.bv_val points to DN within (in-place) ber
    if ( ber_scanf( pOperation->ber, "{mmb", &modReq->dn, &modReq->newrdn, &modReq->bDeleteOldRdn) == LBER_ERROR )
    {
        VMDIR_LOG_ERROR( LDAP_DEBUG_ARGS, "VmDirPerformRename: ber_scanf failed" );
        pResult->errCode = LDAP_PROTOCOL_ERROR;
        retVal = LDAP_NOTICE_OF_DISCONNECT;
        BAIL_ON_VMDIR_ERROR_WITH_MSG(   retVal, (pszLocalErrorMsg),
                                      "Decoding error while parsing the target DN");
    }

    if (ber_peek_tag(pOperation->ber, &size) == LDAP_TAG_NEWSUPERIOR)
    {
        if ( ber_scanf(pOperation->ber, "m", &modReq->newSuperior ) == LBER_ERROR ) {
        pResult->errCode = LDAP_PROTOCOL_ERROR;
        retVal = LDAP_NOTICE_OF_DISCONNECT; BAIL_ON_VMDIR_ERROR_WITH_MSG( retVal, (pszLocalErrorMsg), "Decoding error while parsing newSuperior");

        }
    }

   if ( ber_scanf( pOperation->ber, "}") == LBER_ERROR )
   {
      VMDIR_LOG_ERROR( LDAP_DEBUG_ARGS, "PerformRename: ber_scanf failed" );
      pResult->errCode = LDAP_PROTOCOL_ERROR;
      retVal = LDAP_NOTICE_OF_DISCONNECT;
      BAIL_ON_VMDIR_ERROR_WITH_MSG(   retVal, (pszLocalErrorMsg), "Decoding error while parsing the end of message.");
   }

   retVal = pResult->errCode = VmDirMLModify( pOperation );
   BAIL_ON_VMDIR_ERROR(retVal);

cleanup:
    if (retVal != LDAP_NOTICE_OF_DISCONNECT)
    {
        VmDirSendLdapResult( pOperation );
    }
    VMDIR_SAFE_FREE_MEMORY(pszLocalErrorMsg);
    return retVal;

error:
    VMDIR_APPEND_ERROR_MSG(pResult->pszErrMsg, pszLocalErrorMsg);
    goto cleanup;
}