void SslCredential::loadPrivCertStore()
{
    //  Get a handle to the system store or pkcs#12 file
    qpid::sys::ssl::SslOptions& opts = qpid::sys::ssl::SslOptions::global;
    if (opts.certFilename.empty()) {
        // opening a system store, names are not case sensitive
        std::string store = opts.certStore.empty() ? "my" : opts.certStore;
        std::transform(store.begin(), store.end(), store.begin(), ::tolower);
        // map confusing GUI name to actual registry store name
        if (store == "personal")
            store = "my";
        certStore = ::CertOpenStore(CERT_STORE_PROV_SYSTEM_A, 0, NULL,
                          CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG |
                          CERT_SYSTEM_STORE_CURRENT_USER, store.c_str());
        if (!certStore) {
            HRESULT status = GetLastError();
            loadError.set(Msg() << "Could not open system certificate store: " << store, status);
            return;
        }
        QPID_LOG(debug, "SslConnector using certifcates from system store: " << store);
    } else {
        // opening the store from file and populating it with a private key
        HANDLE certFileHandle = NULL;
        certFileHandle = CreateFile(opts.certFilename.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == certFileHandle) {
            HRESULT status = GetLastError();
            loadError.set(Msg() << "Failed to open the file holding the private key: " << opts.certFilename, status);
            return;
        }
        std::vector<BYTE> certEncoded;
        DWORD certEncodedSize = 0L;
        const DWORD fileSize = GetFileSize(certFileHandle, NULL);
        if (INVALID_FILE_SIZE != fileSize) {
            certEncoded.resize(fileSize);
            bool result = false;
            result = ReadFile(certFileHandle, &certEncoded[0],
                fileSize,
                &certEncodedSize,
                NULL);
            if (!result) {
                // the read failed, return the error as an HRESULT
                HRESULT status = GetLastError();
                CloseHandle(certFileHandle);
                loadError.set(Msg() << "Reading the private key from file failed " << opts.certFilename, status);
                return;
            }
        }
        else {
            HRESULT status = GetLastError();
            loadError.set(Msg() << "Unable to read the certificate file " << opts.certFilename, status);
            return;
        }
        CloseHandle(certFileHandle);

        CRYPT_DATA_BLOB blobData;
        blobData.cbData = certEncodedSize;
        blobData.pbData = &certEncoded[0];

        // get passwd from file and convert to null terminated wchar_t (Windows UCS2)
        std::string passwd = getPasswd(opts.certPasswordFile);
        if (loadError.pending())
            return;
        int pwlen = passwd.length();
        std::vector<wchar_t> pwUCS2(pwlen + 1, L'\0');
        int nwc = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, passwd.data(), pwlen, &pwUCS2[0], pwlen);
        if (!nwc) {
            HRESULT status = GetLastError();
            loadError.set("Error converting password from UTF8", status);
            return;
        }

        certStore = PFXImportCertStore(&blobData, &pwUCS2[0], 0);
        if (certStore == NULL) {
            HRESULT status = GetLastError();
            loadError.set("Failed to open the certificate store", status);
            return;
        }
        QPID_LOG(debug, "SslConnector using certificate from pkcs#12 file: " << opts.certFilename);
    }
}