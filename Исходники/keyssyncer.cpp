void KeysSyncer::storeAsymmKeyPairs(const std::vector<Protocol::KeyPair> &keyPairs)
{
    for (const Protocol::KeyPair &keyPair : keyPairs)
    {
        auto type = Crypto::AsymmetricKeyType::Invalid;
        FWD_NESTED(type = Crypto::keyTypeFromString(keyPair.type),
                   InvalidArgument,
                   Codec::InvalidContentFormat("unknown keyPair.type"));

        // don't store keys when there's no private key, since we couldn't use
        // them for signing
        if (keyPair.privkey.empty()) continue;

        auto dao = Dao::AsymmetricKeyPairDao::load(type, keyPair.id, session_);
        if (!dao)
        {
            dao.reset(new Dao::AsymmetricKeyPairDao(session_));
            dao->setId(keyPair.id);
            dao->setKeyType(type);

            auto privateDataKey = Dao::SymmetricKeyDao::loadKey(
                        Dao::SymmetricKeyDao::PRIVATE_DATA_KEY,
                        session_);

            Crypto::SymmetricCryptor cryptor;
            auto privkey = cryptor.decrypt(
                        keyPair.privkey,
                        privateDataKey,
                        cryptor.RANDOM_IV_BYTES);

            dao->setPubkey(keyPair.pubkey);
            dao->setPrivkey(privkey);
            dao->setValidFrom(keyPair.validFrom.toString());
            dao->setValidUntil(keyPair.validUntil.toString());
        }
        dao->setRevocation(keyPair.revocation);
        dao->save();
    }
}