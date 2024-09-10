NvPairingManager::PairState
NvPairingManager::pair(QString appVersion, QString pin)
{
    int serverMajorVersion = NvHTTP::parseQuad(appVersion).at(0);
    qInfo() << "Pairing with server generation:" << serverMajorVersion;

    QCryptographicHash::Algorithm hashAlgo;
    int hashLength;
    if (serverMajorVersion >= 7)
    {
        // Gen 7+ uses SHA-256 hashing
        hashAlgo = QCryptographicHash::Sha256;
        hashLength = 32;
    }
    else
    {
        // Prior to Gen 7 uses SHA-1 hashing
        hashAlgo = QCryptographicHash::Sha1;
        hashLength = 20;
    }

    QByteArray salt = generateRandomBytes(16);
    QByteArray saltedPin = saltPin(salt, pin);

    AES_KEY encKey, decKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(QCryptographicHash::hash(saltedPin, hashAlgo).data()), 128, &decKey);
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(QCryptographicHash::hash(saltedPin, hashAlgo).data()), 128, &encKey);

    QString getCert = m_Http.openConnectionToString(m_Http.m_BaseUrlHttp,
                                                    "pair",
                                                    "devicename=roth&updateState=1&phrase=getservercert&salt=" +
                                                    salt.toHex() + "&clientcert=" + IdentityManager::get()->getCertificate().toHex(),
                                                    false);
    NvHTTP::verifyResponseStatus(getCert);
    if (NvHTTP::getXmlString(getCert, "paired") != "1")
    {
        qCritical() << "Failed pairing at stage #1";
        return PairState::FAILED;
    }

    QByteArray serverCert = NvHTTP::getXmlStringFromHex(getCert, "plaincert");
    if (serverCert == nullptr)
    {
        qCritical() << "Server likely already pairing";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::ALREADY_IN_PROGRESS;
    }

    QByteArray randomChallenge = generateRandomBytes(16);
    QByteArray encryptedChallenge = encrypt(randomChallenge, &encKey);
    QString challengeXml = m_Http.openConnectionToString(m_Http.m_BaseUrlHttp,
                                                         "pair",
                                                         "devicename=roth&updateState=1&clientchallenge=" +
                                                         encryptedChallenge.toHex(),
                                                         true);
    NvHTTP::verifyResponseStatus(challengeXml);
    if (NvHTTP::getXmlString(challengeXml, "paired") != "1")
    {
        qCritical() << "Failed pairing at stage #2";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::FAILED;
    }

    QByteArray challengeResponseData = decrypt(m_Http.getXmlStringFromHex(challengeXml, "challengeresponse"), &decKey);
    QByteArray clientSecretData = generateRandomBytes(16);
    QByteArray challengeResponse;
    QByteArray serverResponse(challengeResponseData.data(), hashLength);

#if (OPENSSL_VERSION_NUMBER < 0x10002000L)
    ASN1_BIT_STRING *asnSignature = m_Cert->signature;
#elif (OPENSSL_VERSION_NUMBER < 0x10100000L)
    ASN1_BIT_STRING *asnSignature;
    X509_get0_signature(&asnSignature, NULL, m_Cert);
#else
    const ASN1_BIT_STRING *asnSignature;
    X509_get0_signature(&asnSignature, NULL, m_Cert);
#endif

    challengeResponse.append(challengeResponseData.data() + hashLength, 16);
    challengeResponse.append(reinterpret_cast<char*>(asnSignature->data), asnSignature->length);
    challengeResponse.append(clientSecretData);

    QByteArray encryptedChallengeResponseHash = encrypt(QCryptographicHash::hash(challengeResponse, hashAlgo), &encKey);
    QString respXml = m_Http.openConnectionToString(m_Http.m_BaseUrlHttp,
                                                    "pair",
                                                    "devicename=roth&updateState=1&serverchallengeresp=" +
                                                    encryptedChallengeResponseHash.toHex(),
                                                    true);
    NvHTTP::verifyResponseStatus(respXml);
    if (NvHTTP::getXmlString(respXml, "paired") != "1")
    {
        qCritical() << "Failed pairing at stage #3";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::FAILED;
    }

    QByteArray pairingSecret = NvHTTP::getXmlStringFromHex(respXml, "pairingsecret");
    QByteArray serverSecret = QByteArray(pairingSecret.data(), 16);
    QByteArray serverSignature = QByteArray(&pairingSecret.data()[16], 256);

    if (!verifySignature(serverSecret,
                         serverSignature,
                         serverCert))
    {
        qCritical() << "MITM detected";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::FAILED;
    }

    QByteArray expectedResponseData;
    expectedResponseData.append(randomChallenge);
    expectedResponseData.append(getSignatureFromPemCert(serverCert));
    expectedResponseData.append(serverSecret);
    if (QCryptographicHash::hash(expectedResponseData, hashAlgo) != serverResponse)
    {
        qCritical() << "Incorrect PIN";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::PIN_WRONG;
    }

    QByteArray clientPairingSecret;
    clientPairingSecret.append(clientSecretData);
    clientPairingSecret.append(signMessage(clientSecretData));

    QString secretRespXml = m_Http.openConnectionToString(m_Http.m_BaseUrlHttp,
                                                          "pair",
                                                          "devicename=roth&updateState=1&clientpairingsecret=" +
                                                          clientPairingSecret.toHex(),
                                                          true);
    NvHTTP::verifyResponseStatus(secretRespXml);
    if (NvHTTP::getXmlString(secretRespXml, "paired") != "1")
    {
        qCritical() << "Failed pairing at stage #4";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::FAILED;
    }

    QString pairChallengeXml = m_Http.openConnectionToString(m_Http.m_BaseUrlHttps,
                                                             "pair",
                                                             "devicename=roth&updateState=1&phrase=pairchallenge",
                                                             true);
    NvHTTP::verifyResponseStatus(pairChallengeXml);
    if (NvHTTP::getXmlString(pairChallengeXml, "paired") != "1")
    {
        qCritical() << "Failed pairing at stage #5";
        m_Http.openConnectionToString(m_Http.m_BaseUrlHttp, "unpair", nullptr, true);
        return PairState::FAILED;
    }

    return PairState::PAIRED;
}