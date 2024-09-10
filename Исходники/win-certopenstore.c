void doit(void)
{
    HCERTSTORE hStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, CERT_SYSTEM_STORE_CURRENT_USER , L"ROOT");
    assert(hStore != NULL);
    HCERTSTORE hSystemStore = CertOpenSystemStore(0, "ROOT");
    assert(hSystemStore != NULL);
    
    PCCERT_CONTEXT prevCtx = NULL;
    PCCERT_CONTEXT ctx = NULL;
    PCCERT_CONTEXT sysPrevCtx = NULL;
    PCCERT_CONTEXT sysCtx = NULL;

    while (1)
    {
        ctx = CertEnumCertificatesInStore(hStore, prevCtx);
        sysCtx = CertEnumCertificatesInStore(hSystemStore, sysPrevCtx);
        if (ctx == NULL || sysCtx == NULL)
            break;
        if (CertCompareIntegerBlob(&ctx->pCertInfo->SerialNumber,
                                   &sysCtx->pCertInfo->SerialNumber) != TRUE)
            assert(0);

        prevCtx = ctx;
        sysPrevCtx = sysCtx;
    }
    assert(ctx == NULL && sysCtx == NULL);

    CertCloseStore(hStore, 0);
    CertCloseStore(hSystemStore, 0);
}