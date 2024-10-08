String WebCore::signedPublicKeyAndChallengeString(unsigned index, const String& challenge, const KURL& url)
{
    String keyString;

    HCRYPTPROV hContext = 0;
    HCRYPTKEY hKey = 0;
    PCERT_PUBLIC_KEY_INFO pPubInfo = 0;

    // Try to delete it if it exists already
    CryptAcquireContextW(&hContext, L"keygen_container", MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_DELETEKEYSET);

    do {
        if (!CryptAcquireContextW(&hContext, L"keygen_container", MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
            break;

        DWORD dwPubInfoLength = 0;
        if (!CryptGenKey(hContext, AT_KEYEXCHANGE, 0, &hKey) || !CryptExportPublicKeyInfo(hContext, AT_KEYEXCHANGE, X509_ASN_ENCODING, 0, &dwPubInfoLength))
            break;

        // Use malloc instead of new, because malloc guarantees to return a pointer aligned for all data types.
        pPubInfo = reinterpret_cast<PCERT_PUBLIC_KEY_INFO>(fastMalloc(dwPubInfoLength));

        if (!CryptExportPublicKeyInfo(hContext, AT_KEYEXCHANGE, X509_ASN_ENCODING, pPubInfo, &dwPubInfoLength))
            break;

        CERT_KEYGEN_REQUEST_INFO requestInfo = { 0 };
        requestInfo.dwVersion = CERT_KEYGEN_REQUEST_V1;
        requestInfo.pwszChallengeString = L"";
        requestInfo.SubjectPublicKeyInfo = *pPubInfo;

        String localChallenge = challenge;

        // Windows API won't write to our buffer, although it's not declared with const.
        requestInfo.pwszChallengeString = const_cast<wchar_t*>(localChallenge.charactersWithNullTermination());

        CRYPT_ALGORITHM_IDENTIFIER signAlgo = { 0 };
        signAlgo.pszObjId = szOID_RSA_SHA1RSA;

        DWORD dwEncodedLength;
        if (!CryptSignAndEncodeCertificate(hContext, AT_KEYEXCHANGE, X509_ASN_ENCODING, X509_KEYGEN_REQUEST_TO_BE_SIGNED, &requestInfo, &signAlgo, 0, 0, &dwEncodedLength))
            break;

        Vector<char> binary(dwEncodedLength);
        if (!CryptSignAndEncodeCertificate(hContext, AT_KEYEXCHANGE, X509_ASN_ENCODING, X509_KEYGEN_REQUEST_TO_BE_SIGNED, &requestInfo, &signAlgo, 0, reinterpret_cast<LPBYTE>(binary.data()), &dwEncodedLength))
            break;

        keyString = base64Encode(binary);
    } while(0);

    if (pPubInfo)
        fastFree(pPubInfo);

    if (hKey)
        CryptDestroyKey(hKey);

    if (hContext)
        CryptReleaseContext(hContext, 0);

    return keyString;
}