const svn_string_t * SVNAuthData::decrypt_data(const svn_string_t *crypted, apr_pool_t *pool)
{
    crypted = svn_base64_decode_string(crypted, pool);

    DATA_BLOB blobin;
    DATA_BLOB blobout;
    LPWSTR descr;
    const svn_string_t * orig = NULL;

    blobin.cbData = (DWORD)crypted->len;
    blobin.pbData = (BYTE *)crypted->data;
    if (CryptUnprotectData(&blobin, &descr, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &blobout))
    {
        if (0 == lstrcmpW(descr, description))
            orig = svn_string_ncreate((const char *)blobout.pbData, blobout.cbData, pool);
        LocalFree(blobout.pbData);
        LocalFree(descr);
    }
    return orig;
}