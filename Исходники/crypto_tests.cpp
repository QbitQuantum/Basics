static void TestDecrypt(const CCrypter& crypt, const std::vector<unsigned char>& vchCiphertext, \
                        const std::vector<unsigned char>& vchPlaintext = std::vector<unsigned char>())
{
    CKeyingMaterial vchDecrypted1;
    CKeyingMaterial vchDecrypted2;
    int result1, result2;
    result1 = crypt.Decrypt(vchCiphertext, vchDecrypted1);
    result2 = OldDecrypt(vchCiphertext, vchDecrypted2, crypt.vchKey.data(), crypt.vchIV.data());
    BOOST_CHECK(result1 == result2);

    // These two should be equal. However, OpenSSL 1.0.1j introduced a change
    // that would zero all padding except for the last byte for failed decrypts.
    // This behavior was reverted for 1.0.1k.
    if (vchDecrypted1 != vchDecrypted2 && vchDecrypted1.size() >= AES_BLOCK_SIZE && SSLeay() == 0x100010afL)
    {
        for(CKeyingMaterial::iterator it = vchDecrypted1.end() - AES_BLOCK_SIZE; it != vchDecrypted1.end() - 1; it++)
            *it = 0;
    }

    BOOST_CHECK_MESSAGE(vchDecrypted1 == vchDecrypted2, HexStr(vchDecrypted1.begin(), vchDecrypted1.end()) + " != " + HexStr(vchDecrypted2.begin(), vchDecrypted2.end()));

    if (vchPlaintext.size())
        BOOST_CHECK(CKeyingMaterial(vchPlaintext.begin(), vchPlaintext.end()) == vchDecrypted2);
}