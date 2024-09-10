void Sha1Sum::_compute()
{
    BOOL bResult = FALSE;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile;
    BYTE buffer[BUFSIZE];
    DWORD cbRead = 0;
    BYTE rgbHash[SHA1LEN];    
    wchar_t digits[] = L"0123456789abcdef";
    
	m_sum.erase();
	hFile = CreateFile(m_file.c_str(), GENERIC_READ,
        FILE_SHARE_READ,  NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return;
    
    if (!CryptAcquireContext(&hProv, NULL,  NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        CloseHandle(hFile);
        return;
    }

    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
    {
        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);
        return;
    }

    while (bResult = ReadFile(hFile, buffer, BUFSIZE, &cbRead, NULL))
    {
        if (0 == cbRead)        
            break;        

        if (!CryptHashData(hHash, buffer, cbRead, 0))
        {
            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            CloseHandle(hFile);
            return;
        }
    }

    if (!bResult)
    {
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CloseHandle(hFile);     
    }

    cbRead = SHA1LEN;
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbRead, 0))
    {
        for (DWORD i = 0; i < cbRead; i++)
        {
			wchar_t c[16];
			wsprintf(c, L"%c%c", digits[rgbHash[i] >> 4], digits[rgbHash[i] & 0xf]);
			m_sum += c;
        }
    }
    
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);
}