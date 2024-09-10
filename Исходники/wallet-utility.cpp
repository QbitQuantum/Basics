bool WalletUtilityDB::Unlock()
{
    CCrypter crypter;
    CKeyingMaterial vMasterKey;

    BOOST_FOREACH(const MasterKeyMap::value_type& pMasterKey, mapMasterKeys)
    {
        if(!crypter.SetKeyFromPassphrase(mPass, pMasterKey.second.vchSalt, pMasterKey.second.nDeriveIterations, pMasterKey.second.nDerivationMethod))
            return false;
        if (!crypter.Decrypt(pMasterKey.second.vchCryptedKey, vMasterKey))
            continue; // try another master key
        vMKeys.push_back(vMasterKey);
    }
    return true;
}