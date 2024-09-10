    RCF::ByteBuffer Win32Certificate::exportToPfx()
    {
        PCCERT_CONTEXT pContext = getWin32Context();

        // Create in-memory store
        HCERTSTORE  hMemoryStore;

        hMemoryStore = CertOpenStore(
            CERT_STORE_PROV_MEMORY,    // Memory store
            0,                         // Encoding type, not used with a memory store
            NULL,                      // Use the default provider
            0,                         // No flags
            NULL);                     // Not needed

        DWORD dwErr = GetLastError();

        RCF_VERIFY(
            hMemoryStore, 
            Exception(_RcfError_ApiError("CertOpenStore()"), dwErr));

        // Add the certificate.
        BOOL ok = CertAddCertificateContextToStore(
            hMemoryStore,                // Store handle
            pContext,                   // Pointer to a certificate
            CERT_STORE_ADD_USE_EXISTING,
            NULL);

        dwErr = GetLastError();

        RCF_VERIFY(
            ok, 
            Exception(_RcfError_ApiError("CertAddCertificateContextToStore()"), dwErr));

        // Export in-memory store.
        CRYPT_DATA_BLOB pfxBlob = {};
        BOOL exportOk = PFXExportCertStore(hMemoryStore, &pfxBlob, L"", 0/*EXPORT_PRIVATE_KEYS*/);

        dwErr = GetLastError();

        RCF_VERIFY(
            exportOk, 
            Exception(_RcfError_ApiError("PFXExportCertStore()"), dwErr));

        RCF::ByteBuffer pfxBuffer(pfxBlob.cbData);
        pfxBlob.pbData = (BYTE *) pfxBuffer.getPtr();

        exportOk = PFXExportCertStore(hMemoryStore, &pfxBlob, L"", 0/*EXPORT_PRIVATE_KEYS*/);
        
        dwErr = GetLastError();

        RCF_VERIFY(
            exportOk, 
            Exception(_RcfError_ApiError("PFXExportCertStore()"), dwErr));

        CertCloseStore(hMemoryStore, 0);

        return pfxBuffer;
    }