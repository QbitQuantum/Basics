DWORD VerifyCertificate(PCCERT_CONTEXT pCert,DWORD *CheckResult)
{
    CERT_CHAIN_PARA ChainPara;
    PCCERT_CHAIN_CONTEXT Chain=NULL;
	
    ChainPara.cbSize=sizeof(ChainPara);
    ChainPara.RequestedUsage.dwType=USAGE_MATCH_TYPE_AND;
    ChainPara.RequestedUsage.Usage.cUsageIdentifier=0;
    ChainPara.RequestedUsage.Usage.rgpszUsageIdentifier=NULL;
    //ChainPara.RequestedIssuancePolicy=NULL;
    //ChainPara.fCheckRevocationFreshnessTime=FALSE;
    //ChainPara.dwUrlRetrievalTimeout=0;
	
    if(!CertGetCertificateChain(
								NULL,
								pCert,
								NULL,
								NULL,//?
								&ChainPara,
								CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT,
								NULL,
								&Chain))
        return CSP_GetLastError();
    *CheckResult=Chain->TrustStatus.dwErrorStatus;
    if(Chain)
        CertFreeCertificateChain(Chain);
    return 0;
}