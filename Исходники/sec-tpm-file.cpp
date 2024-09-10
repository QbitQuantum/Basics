void
SecTpmFile::generateKeyPairInTpm(const Name& keyName, const KeyParams& params)
{
  string keyURI = keyName.toUri();

  if (doesKeyExistInTpm(keyName, KeyClass::PUBLIC))
    BOOST_THROW_EXCEPTION(Error("public key exists"));
  if (doesKeyExistInTpm(keyName, KeyClass::PRIVATE))
    BOOST_THROW_EXCEPTION(Error("private key exists"));

  string keyFileName = m_impl->maintainMapping(keyURI);

  try {
    switch (params.getKeyType()) {
      case KeyType::RSA: {
        using namespace CryptoPP;

        const RsaKeyParams& rsaParams = static_cast<const RsaKeyParams&>(params);
        AutoSeededRandomPool rng;
        InvertibleRSAFunction privateKey;
        privateKey.Initialize(rng, rsaParams.getKeySize());

        string privateKeyFileName = keyFileName + ".pri";
        Base64Encoder privateKeySink(new FileSink(privateKeyFileName.c_str()));
        privateKey.DEREncode(privateKeySink);
        privateKeySink.MessageEnd();

        RSAFunction publicKey(privateKey);
        string publicKeyFileName = keyFileName + ".pub";
        Base64Encoder publicKeySink(new FileSink(publicKeyFileName.c_str()));
        publicKey.DEREncode(publicKeySink);
        publicKeySink.MessageEnd();

        // set file permission
        chmod(privateKeyFileName.c_str(), 0000400);
        chmod(publicKeyFileName.c_str(), 0000444);
        return;
      }

      case KeyType::EC: {
        using namespace CryptoPP;

        const EcdsaKeyParams& ecdsaParams = static_cast<const EcdsaKeyParams&>(params);

        CryptoPP::OID curveName;
        switch (ecdsaParams.getKeySize()) {
        case 256:
          curveName = ASN1::secp256r1();
          break;
        case 384:
          curveName = ASN1::secp384r1();
          break;
        default:
          curveName = ASN1::secp256r1();
          break;
        }

        AutoSeededRandomPool rng;

        ECDSA<ECP, SHA256>::PrivateKey privateKey;
        DL_GroupParameters_EC<ECP> cryptoParams(curveName);
        cryptoParams.SetEncodeAsOID(true);
        privateKey.Initialize(rng, cryptoParams);

        ECDSA<ECP, SHA256>::PublicKey publicKey;
        privateKey.MakePublicKey(publicKey);
        publicKey.AccessGroupParameters().SetEncodeAsOID(true);

        string privateKeyFileName = keyFileName + ".pri";
        Base64Encoder privateKeySink(new FileSink(privateKeyFileName.c_str()));
        privateKey.DEREncode(privateKeySink);
        privateKeySink.MessageEnd();

        string publicKeyFileName = keyFileName + ".pub";
        Base64Encoder publicKeySink(new FileSink(publicKeyFileName.c_str()));
        publicKey.Save(publicKeySink);
        publicKeySink.MessageEnd();

        // set file permission
        chmod(privateKeyFileName.c_str(), 0000400);
        chmod(publicKeyFileName.c_str(), 0000444);
        return;
      }

      default:
        BOOST_THROW_EXCEPTION(Error("Unsupported key type"));
    }
  }
  catch (const KeyParams::Error& e) {
    BOOST_THROW_EXCEPTION(Error(e.what()));
  }
  catch (const CryptoPP::Exception& e) {
    BOOST_THROW_EXCEPTION(Error(e.what()));
  }
}