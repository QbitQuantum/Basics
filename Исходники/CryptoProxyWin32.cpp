CryptoHash::CryptoHash(HCRYPTPROV cryptProv, ALG_ID algId, const ByteVector& data)
         :handle(NULL)
{
    TOE(CryptCreateHash(cryptProv, algId, 0, 0, &handle), "CryptCreateHash");
    try
    {
        update(data);
    }
    catch (exception&)
    {
        CryptDestroyHash(handle);
        throw;
    }
}