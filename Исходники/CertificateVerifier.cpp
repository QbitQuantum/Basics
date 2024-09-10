   bool 
   CertificateVerifier::VerifyCertificate_( PCCERT_CONTEXT certificate, LPWSTR server_name,int &windows_error_code) const
   {
      windows_error_code = 0;

      LPSTR usage_identifier[] = { szOID_PKIX_KP_SERVER_AUTH, szOID_SERVER_GATED_CRYPTO, szOID_SGC_NETSCAPE };

      CERT_CHAIN_PARA params = { sizeof( params ) };
      params.RequestedUsage.dwType = USAGE_MATCH_TYPE_OR;
      params.RequestedUsage.Usage.cUsageIdentifier = _countof( usage_identifier );
      params.RequestedUsage.Usage.rgpszUsageIdentifier = usage_identifier;

      PCCERT_CHAIN_CONTEXT chain_context = 0;

      if (!CertGetCertificateChain(NULL, 
                                   certificate,  
                                   NULL,
                                   NULL,
                                   &params,
                                   CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT,
                                   NULL,
                                   &chain_context))
      {
         windows_error_code = GetLastError();
         return false;
      }

      SSL_EXTRA_CERT_CHAIN_POLICY_PARA sslPolicy = { sizeof( sslPolicy ) };
      sslPolicy.dwAuthType = AUTHTYPE_SERVER;
      sslPolicy.pwszServerName = server_name;

      CERT_CHAIN_POLICY_PARA policy = { sizeof( policy ) };
      policy.pvExtraPolicyPara = &sslPolicy;

      CERT_CHAIN_POLICY_STATUS status = { sizeof( status ) };

      BOOL policy_checked = CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL,
                                                             chain_context,
                                                             &policy,
                                                             &status );

      CertFreeCertificateChain( chain_context );

      windows_error_code = status.dwError;
      bool certificate_ok = policy_checked && status.dwError == 0;
      return certificate_ok;
   }