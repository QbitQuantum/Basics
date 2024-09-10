my_bool ma_tls_connect(MARIADB_TLS *ctls)
{
  my_bool blocking;
  MYSQL *mysql;
  SCHANNEL_CRED Cred;
  MARIADB_PVIO *pvio;
  my_bool rc= 1;
  SC_CTX *sctx;
  SECURITY_STATUS sRet;
  PCCERT_CONTEXT pRemoteCertContext = NULL,
                 pLocalCertContext= NULL;
  ALG_ID AlgId[MAX_ALG_ID]= {0};
  
  if (!ctls || !ctls->pvio)
    return 1;;
  
  pvio= ctls->pvio;
  sctx= (SC_CTX *)ctls->ssl;

  /* Set socket to blocking if not already set */
  if (!(blocking= pvio->methods->is_blocking(pvio)))
    pvio->methods->blocking(pvio, TRUE, 0);

  mysql= pvio->mysql;
 
  if (ma_tls_set_client_certs(ctls))
    goto end;

  ZeroMemory(&Cred, sizeof(SCHANNEL_CRED));

  /* Set cipher */
  if (mysql->options.ssl_cipher)
  {
    WORD validTokens = 0;
    char *token = strtok(mysql->options.ssl_cipher, ":");
    while (token)
    {
      struct st_cipher_suite *valid;
      for (valid = valid_ciphers; valid && valid->aid; valid++)
      {
        if (!strcmp(token, valid->cipher))
        {
          AlgId[validTokens++] = valid->aid;
          break;
        }
      }
      token = strtok(NULL, ":");
    }
  }
  Cred.palgSupportedAlgs = (ALG_ID *)&AlgId;
  
  Cred.dwVersion= SCHANNEL_CRED_VERSION;
  if (mysql->options.extension)
    Cred.dwMinimumCipherStrength = MAX(128, mysql->options.extension->tls_cipher_strength);
  else
    Cred.dwMinimumCipherStrength = 128;
  Cred.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK | SCH_SEND_ROOT_CERT |
    SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION;
  if (sctx->client_cert_ctx)
  {
    Cred.cCreds = 1;
    Cred.paCred = &sctx->client_cert_ctx;
  }
  if (mysql->options.extension && mysql->options.extension->tls_version)
  {
    Cred.grbitEnabledProtocols= 0;
    if (strstr("TLSv1.0", mysql->options.extension->tls_version))
      Cred.grbitEnabledProtocols|= SP_PROT_TLS1_0;
    if (strstr("TLSv1.1", mysql->options.extension->tls_version))
      Cred.grbitEnabledProtocols|= SP_PROT_TLS1_1;
    if (strstr("TLSv1.2", mysql->options.extension->tls_version))
      Cred.grbitEnabledProtocols|= SP_PROT_TLS1_2;
  }
  else
    Cred.grbitEnabledProtocols = SP_PROT_TLS1_0 |
                                 SP_PROT_TLS1_1 |
                                 SP_PROT_TLS1_2;

  if ((sRet= AcquireCredentialsHandleA(NULL, UNISP_NAME_A, SECPKG_CRED_OUTBOUND,
                                       NULL, &Cred, NULL, NULL, &sctx->CredHdl, NULL)) != SEC_E_OK)
  {
    ma_schannel_set_sec_error(pvio, sRet);
    goto end;
  }
  sctx->FreeCredHdl= 1;

  if (ma_schannel_client_handshake(ctls) != SEC_E_OK)
    goto end;

  sRet= QueryContextAttributes(&sctx->ctxt, SECPKG_ATTR_REMOTE_CERT_CONTEXT, (PVOID)&pRemoteCertContext);
  if (sRet != SEC_E_OK)
  {
    ma_schannel_set_sec_error(pvio, sRet);
    goto end;
  }
  
  if (!ma_schannel_verify_certs(sctx, 0))
    goto end;
 
  return 0;

end:
  if (pRemoteCertContext)
    CertFreeCertificateContext(pRemoteCertContext);
  if (rc && sctx->IoBufferSize)
    LocalFree(sctx->IoBuffer);
  sctx->IoBufferSize= 0;
  if (sctx->client_cert_ctx)
    CertFreeCertificateContext(sctx->client_cert_ctx);
  sctx->client_cert_ctx= 0;
  return 1;
}