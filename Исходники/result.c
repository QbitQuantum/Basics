void
VmDirSendLdapResult(
   VDIR_OPERATION * op
   )
{
   BerElementBuffer berbuf;
   BerElement *     ber = (BerElement *) &berbuf;
   ber_int_t        msgId = 0;
   ber_tag_t        resCode = 0;
   size_t           iNumSearchEntrySent = 0;
   PCSTR            pszSocketInfo = NULL;

   (void) memset( (char *)&berbuf, '\0', sizeof( BerElementBuffer ));

   resCode = GetResultTag( op->reqCode );
   msgId = (resCode != LBER_SEQUENCE) ? op->msgId : 0;

   if ( resCode == LDAP_RES_SEARCH_RESULT )
   {
       iNumSearchEntrySent = op->request.searchReq.iNumEntrySent;
   }

   ber_init2( ber, NULL, LBER_USE_DER );

   if (op->conn)
   {
      pszSocketInfo = op->conn->szClientIP;
   }

   if (op->ldapResult.errCode &&
       op->ldapResult.errCode != LDAP_SASL_BIND_IN_PROGRESS)
   {
       VMDIR_LOG_ERROR(
          VMDIR_LOG_MASK_ALL,
          "VmDirSendLdapResult: Request (%d), Error (%d), Message (%s), (%u) socket (%s)",
          op->reqCode,
          op->ldapResult.errCode,
          VDIR_SAFE_STRING(op->ldapResult.pszErrMsg),
          iNumSearchEntrySent,
          VDIR_SAFE_STRING(pszSocketInfo));
   }
   else if ( op->reqCode == LDAP_REQ_SEARCH )
   {
       VMDIR_LOG_INFO(
          LDAP_DEBUG_ARGS,
          "VmDirSendLdapResult: Request (%d), Error (%d), Message (%s), (%u) socket (%s)",
          op->reqCode,
          op->ldapResult.errCode,
          VDIR_SAFE_STRING(op->ldapResult.pszErrMsg),
          iNumSearchEntrySent,
          VDIR_SAFE_STRING(pszSocketInfo));
   }

   if (ber_printf( ber, "{it{essN}", msgId, resCode, op->ldapResult.errCode, "",
                       VDIR_SAFE_STRING(op->ldapResult.pszErrMsg)) == -1)
   {
      VMDIR_LOG_ERROR( VMDIR_LOG_MASK_ALL, "SendLdapResult: ber_printf (to print msgId ...) failed" );
      goto done;
   }

   // If Search, Replication, and one or more entries were sent back => Send back Sync Done Control
   if ( op->reqCode == LDAP_REQ_SEARCH && op->syncReqCtrl != NULL && op->syncDoneCtrl != NULL)
   {
       if (WriteSyncDoneControl( op, ber ) != LDAP_SUCCESS)
       {
           goto done;
       }
   }

   if ( op->reqCode == LDAP_REQ_SEARCH && op->showPagedResultsCtrl != NULL)
   {
       if (WritePagedSearchDoneControl( op, ber ) != LDAP_SUCCESS)
       {
           goto done;
       }
   }

   if (ber_printf( ber, "N}" ) == -1)
   {
      VMDIR_LOG_ERROR( VMDIR_LOG_MASK_ALL, "SendLdapResult: ber_printf (to print msgId ...) failed" );
      goto done;
   }

   if (WriteBerOnSocket( op->conn, ber ) != 0)
   {
      VMDIR_LOG_ERROR( VMDIR_LOG_MASK_ALL, "SendLdapResult: WriteBerOnSocket failed" );
      goto done;
   }

done:
   ber_free_buf( ber );

}