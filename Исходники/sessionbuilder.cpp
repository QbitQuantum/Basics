KeyExchangeMessage SessionBuilder::processInitiate(QSharedPointer<KeyExchangeMessage> message)
{
    int            flags         = KeyExchangeMessage::RESPONSE_FLAG;
    SessionRecord *sessionRecord = sessionStore->loadSession(recipientId, deviceId);

    if (message->getVersion() >= 3 &&
        !Curve::verifySignature(message->getIdentityKey().getPublicKey(),
                                message->getBaseKey().serialize(),
                                message->getBaseKeySignature()))
    {
        throw InvalidKeyException("Bad signature!");
    }

    SymmetricAxolotlParameters parameters;

    if (!sessionRecord->getSessionState()->hasPendingKeyExchange()) {
        parameters.setOurIdentityKey(identityKeyStore->getIdentityKeyPair());
        parameters.setOurBaseKey(Curve::generateKeyPair());
        parameters.setOurRatchetKey(Curve::generateKeyPair());
    } else {
        parameters.setOurIdentityKey(sessionRecord->getSessionState()->getPendingKeyExchangeIdentityKey());
        parameters.setOurBaseKey(sessionRecord->getSessionState()->getPendingKeyExchangeBaseKey());
        parameters.setOurRatchetKey(sessionRecord->getSessionState()->getPendingKeyExchangeRatchetKey());
        flags |= KeyExchangeMessage::SIMULTAENOUS_INITIATE_FLAG;
    }

    parameters.setTheirBaseKey(message->getBaseKey());
    parameters.setTheirRatchetKey(message->getRatchetKey());
    parameters.setTheirIdentityKey(message->getIdentityKey());

    if (!sessionRecord->isFresh()) sessionRecord->archiveCurrentState();

    RatchetingSession::initializeSession(sessionRecord->getSessionState(),
                                         qMin(message->getMaxVersion(), CURRENT_VERSION),
                                         parameters);

    sessionStore->storeSession(recipientId, deviceId, sessionRecord);
    identityKeyStore->saveIdentity(recipientId, message->getIdentityKey());

    QByteArray baseKeySignature = Curve::calculateSignature(parameters.getOurIdentityKey().getPrivateKey(),
                                                            parameters.getOurBaseKey().getPublicKey().serialize());

    return KeyExchangeMessage(sessionRecord->getSessionState()->getSessionVersion(),
                              message->getSequence(), flags,
                              parameters.getOurBaseKey().getPublicKey(),
                              baseKeySignature, parameters.getOurRatchetKey().getPublicKey(),
                              parameters.getOurIdentityKey().getPublicKey());
}