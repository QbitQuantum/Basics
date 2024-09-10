static BOOL CRYPT_ReadBlobFromFile(HANDLE file, PCERT_BLOB blob)
{
    BOOL ret = TRUE;

    blob->cbData = GetFileSize(file, NULL);
    if (blob->cbData)
    {
        blob->pbData = CryptMemAlloc(blob->cbData);
        if (blob->pbData)
        {
            DWORD read;

            ret = ReadFile(file, blob->pbData, blob->cbData, &read, NULL) && read == blob->cbData;
            if (!ret) CryptMemFree(blob->pbData);
        }
    }
    return ret;
}