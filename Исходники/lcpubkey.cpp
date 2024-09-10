bool PrivateKey::decrypt(std::string &dataInOut) const
{
    std::string plainText;
    if (!_impl->decrypt<CryptoPP::StringSource, CryptoPP::StringSink>(dataInOut, plainText))
        return false;
    dataInOut.swap(plainText);
    return true;
}