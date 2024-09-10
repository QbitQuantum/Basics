static void test_crypt_ui_wiz_import(void)
{
    BOOL ret;
    CRYPTUI_WIZ_IMPORT_SRC_INFO info;
    HCERTSTORE store;
    PCCERT_CONTEXT cert;
    PCCRL_CONTEXT crl;
    DWORD count;

    if (!pCryptUIWizImport)
    {
        skip("No CryptUIWizImport\n");
        return;
    }

    /* Set CBT hook to disallow MessageBox and wizard creation in current
     * thread.
     */
    hook = SetWindowsHookExA(WH_CBT, cbt_hook_proc, 0, GetCurrentThreadId());

    /* Brings up UI.  Cancelling yields ret = 1. */
    if (0)
    {
        pCryptUIWizImport(0, 0, NULL, NULL, NULL);
    }
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, NULL, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    memset(&info, 0, sizeof(info));
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    info.dwSize = sizeof(info);
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    info.dwSubjectChoice = CRYPTUI_WIZ_IMPORT_SUBJECT_CERT_CONTEXT;
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CERT,
     0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    /* Check allowed vs. given type mismatches */
    info.u.pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
     v1CertWithValidPubKey, sizeof(v1CertWithValidPubKey));
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CRL,
     0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    CertFreeCertificateContext(info.u.pCertContext);
    info.dwSubjectChoice = CRYPTUI_WIZ_IMPORT_SUBJECT_CRL_CONTEXT;
    info.u.pCRLContext = CertCreateCRLContext(X509_ASN_ENCODING,
     signedCRL, sizeof(signedCRL));
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CERT,
     0, NULL, &info, NULL);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    CertFreeCRLContext(info.u.pCRLContext);
    /* Imports the following cert--self-signed, with no basic constraints set--
     * to the CA store.  Puts up a dialog at the end if it succeeds or fails.
     */
    info.dwSubjectChoice = CRYPTUI_WIZ_IMPORT_SUBJECT_CERT_CONTEXT;
    info.u.pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
     v1CertWithValidPubKey, sizeof(v1CertWithValidPubKey));
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        static const WCHAR CA[] = { 'C','A',0 };
        HCERTSTORE ca = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, 0,
         CERT_SYSTEM_STORE_CURRENT_USER, CA);

        if (ca)
        {
            ret = find_and_delete_cert_in_store(ca, info.u.pCertContext);
            ok(ret ||
             broken(!ret) /* Win9x/NT4 */,
             "expected to find v1CertWithValidPubKey in CA store\n");
            CertCloseStore(ca, 0);
        }
    }
    CertFreeCertificateContext(info.u.pCertContext);
    /* Imports the following cert--not self-signed, with a basic constraints2
     * extensions--to the "AddressBook" store.  Puts up a dialog at the end if
     * it succeeds or fails.
     */
    info.u.pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
     iTunesCert3, sizeof(iTunesCert3));
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        static const WCHAR AddressBook[] = { 'A','d','d','r','e','s','s',
         'B','o','o','k',0 };
        HCERTSTORE addressBook = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, 0,
         CERT_SYSTEM_STORE_CURRENT_USER, AddressBook);

        if (addressBook)
        {
            ret = find_and_delete_cert_in_store(addressBook,
             info.u.pCertContext);
            ok(ret ||
             broken(!ret),  /* Windows 2000 and earlier */
             "expected to find iTunesCert3 in AddressBook store\n");
            CertCloseStore(addressBook, 0);
        }
    }
    /* Displays the wizard, but disables the "Certificate store" edit and
     * the Browse button.  Confusingly, the "Place all certificates in the
     * following store" radio button is not disabled.
     */
    if (0)
    {
        ret = pCryptUIWizImport(CRYPTUI_WIZ_IMPORT_NO_CHANGE_DEST_STORE, 0,
         NULL, &info, NULL);
        ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    }
    store = CertOpenStore(CERT_STORE_PROV_MEMORY, X509_ASN_ENCODING, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    /* Displays the wizard, but sets the "Certificate store" edit to the
     * string "Determined by the program", and disables it and the Browse
     * button, as well as the "Automatically select the certificate store
     * based on the type of certificate" radio button.
     */
    if (0)
    {
        ret = pCryptUIWizImport(CRYPTUI_WIZ_IMPORT_NO_CHANGE_DEST_STORE, 0,
         NULL, &info, store);
        ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    }
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI |
     CRYPTUI_WIZ_IMPORT_NO_CHANGE_DEST_STORE, 0, NULL, &info, store);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    ret = find_and_delete_cert_in_store(store, info.u.pCertContext);
    ok(ret ||
     broken(!ret) /* Win9x/NT4 */,
     "expected to find iTunesCert3 in memory store\n");
    CertFreeCertificateContext(info.u.pCertContext);
    CertCloseStore(store, 0);

    info.u.pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
     iTunesCert1, sizeof(iTunesCert1));
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        static const WCHAR AddressBook[] = { 'A','d','d','r','e','s','s',
         'B','o','o','k',0 };
        HCERTSTORE addressBook = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, 0,
         CERT_SYSTEM_STORE_CURRENT_USER, AddressBook);

        if (addressBook)
        {
            ret = find_and_delete_cert_in_store(addressBook,
             info.u.pCertContext);
            ok(ret ||
             broken(!ret),  /* Windows 2000 and earlier */
             "expected to find iTunesCert1 in AddressBook store\n");
            CertCloseStore(addressBook, 0);
        }
    }
    CertFreeCertificateContext(info.u.pCertContext);

    info.u.pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
     iTunesCert2, sizeof(iTunesCert2));
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI, 0, NULL, &info, NULL);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        static const WCHAR CA[] = { 'C','A',0 };
        HCERTSTORE ca = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, 0,
         CERT_SYSTEM_STORE_CURRENT_USER, CA);

        if (ca)
        {
            ret = find_and_delete_cert_in_store(ca, info.u.pCertContext);
            ok(ret ||
             broken(!ret) /* Win9x/NT4 */,
             "expected to find iTunesCert2 in CA store\n");
            CertCloseStore(ca, 0);
        }
    }
    CertFreeCertificateContext(info.u.pCertContext);

    info.u.hCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    CertAddEncodedCertificateToStore(info.u.hCertStore, X509_ASN_ENCODING,
     v1CertWithValidPubKey, sizeof(v1CertWithValidPubKey),
     CERT_STORE_ADD_ALWAYS, NULL);
    CertAddEncodedCRLToStore(info.u.hCertStore, X509_ASN_ENCODING, signedCRL,
     sizeof(signedCRL), CERT_STORE_ADD_ALWAYS, NULL);
    info.dwSubjectChoice = CRYPTUI_WIZ_IMPORT_SUBJECT_CERT_STORE;
    /* The ALLOW flags aren't allowed with a store as the source if the source
     * contains types other than those allowed.
     */
    store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CERT,
     0, NULL, &info, store);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CRL,
     0, NULL, &info, store);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI |
     CRYPTUI_WIZ_IMPORT_NO_CHANGE_DEST_STORE |
     CRYPTUI_WIZ_IMPORT_ALLOW_CERT | CRYPTUI_WIZ_IMPORT_ALLOW_CRL, 0, NULL,
     &info, store);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        count = 0;
        cert = NULL;
        do {
            cert = CertEnumCertificatesInStore(store, cert);
            if (cert)
                count++;
        } while (cert);
        ok(count == 1, "expected 1 cert, got %d\n", count);
        count = 0;
        crl = NULL;
        do {
            crl = CertEnumCRLsInStore(store, crl);
            if (crl)
                count++;
        } while (crl);
        ok(count == 1, "expected 1 CRL, got %d\n", count);
    }
    CertCloseStore(store, 0);
    CertCloseStore(info.u.hCertStore, 0);

    /* If the ALLOW flags match the content of the store, the store can be
     * imported.
     */
    info.u.hCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    CertAddEncodedCertificateToStore(info.u.hCertStore, X509_ASN_ENCODING,
     v1CertWithValidPubKey, sizeof(v1CertWithValidPubKey),
     CERT_STORE_ADD_ALWAYS, NULL);
    store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CERT,
     0, NULL, &info, store);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        count = 0;
        cert = NULL;
        do {
            cert = CertEnumCertificatesInStore(store, cert);
            if (cert)
                count++;
        } while (cert);
        ok(count == 1, "expected 1 cert, got %d\n", count);
        count = 0;
        crl = NULL;
        do {
            crl = CertEnumCRLsInStore(store, crl);
            if (crl)
                count++;
        } while (crl);
        ok(count == 0, "expected 0 CRLs, got %d\n", count);
    }
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CRL,
     0, NULL, &info, store);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    CertCloseStore(store, 0);
    CertCloseStore(info.u.hCertStore, 0);

    /* Again, if the ALLOW flags match the content of the store, the store can
     * be imported.
     */
    info.u.hCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    CertAddEncodedCRLToStore(info.u.hCertStore, X509_ASN_ENCODING, signedCRL,
     sizeof(signedCRL), CERT_STORE_ADD_ALWAYS, NULL);
    store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CRL,
     0, NULL, &info, store);
    ok(ret, "CryptUIWizImport failed: %08x\n", GetLastError());
    if (ret)
    {
        count = 0;
        cert = NULL;
        do {
            cert = CertEnumCertificatesInStore(store, cert);
            if (cert)
                count++;
        } while (cert);
        ok(count == 0, "expected 0 certs, got %d\n", count);
        count = 0;
        crl = NULL;
        do {
            crl = CertEnumCRLsInStore(store, crl);
            if (crl)
                count++;
        } while (crl);
        ok(count == 1, "expected 1 CRL, got %d\n", count);
    }
    SetLastError(0xdeadbeef);
    ret = pCryptUIWizImport(CRYPTUI_WIZ_NO_UI | CRYPTUI_WIZ_IMPORT_ALLOW_CERT,
     0, NULL, &info, store);
    ok(!ret && GetLastError() == E_INVALIDARG,
     "expected E_INVALIDARG, got %08x\n", GetLastError());
    CertCloseStore(store, 0);
    CertCloseStore(info.u.hCertStore, 0);

    UnhookWindowsHookEx(hook);
}