/** @return 0 on success, -1 otherwise. */
int CryptoAuth_decrypt(struct CryptoAuth_Session* sessionPub, struct Message* msg)
{
    struct CryptoAuth_Session_pvt* session =
        Identity_check((struct CryptoAuth_Session_pvt*) sessionPub);
    union CryptoHeader* header = (union CryptoHeader*) msg->bytes;

    if (msg->length < 20) {
        cryptoAuthDebug0(session, "DROP runt");
        return -1;
    }
    Assert_true(msg->padding >= 12 || "need at least 12 bytes of padding in incoming message");
    Assert_true(!((uintptr_t)msg->bytes % 4) || !"alignment fault");
    Assert_true(!(msg->capacity % 4) || !"length fault");

    Message_shift(msg, -4, NULL);

    uint32_t nonce = Endian_bigEndianToHost32(header->nonce);

    if (!session->established) {
        if (nonce > 3) {
            if (session->nextNonce < 3) {
                // This is impossible because we have not exchanged hello and key messages.
                cryptoAuthDebug0(session, "DROP Received a run message to an un-setup session");
                return -1;
            }
            cryptoAuthDebug(session, "Trying final handshake step, nonce=%u\n", nonce);
            uint8_t secret[32];
            Assert_ifParanoid(!Bits_isZero(session->ourTempPrivKey, 32));
            Assert_ifParanoid(!Bits_isZero(session->herTempPubKey, 32));
            getSharedSecret(secret,
                            session->ourTempPrivKey,
                            session->herTempPubKey,
                            NULL,
                            session->context->logger);

            if (decryptMessage(session, nonce, msg, secret)) {
                cryptoAuthDebug0(session, "Final handshake step succeeded");
                Bits_memcpyConst(session->sharedSecret, secret, 32);

                // Now we're in run mode, no more handshake packets will be accepted
                Bits_memset(session->ourTempPrivKey, 0, 32);
                Bits_memset(session->ourTempPubKey, 0, 32);
                Bits_memset(session->herTempPubKey, 0, 32);
                session->established = true;
                session->nextNonce += 3;
                updateTime(session, msg);
                return 0;
            }
            cryptoAuthDebug0(session, "DROP Final handshake step failed");
            return -1;
        }

        Message_shift(msg, 4, NULL);
        return decryptHandshake(session, nonce, msg, header);

    } else if (nonce > 3) {
        Assert_ifParanoid(!Bits_isZero(session->sharedSecret, 32));
        if (decryptMessage(session, nonce, msg, session->sharedSecret)) {
            updateTime(session, msg);
            return 0;
        } else {
            cryptoAuthDebug0(session, "DROP Failed to decrypt message");
            return -1;
        }
    } else if (nonce < 2) {
        cryptoAuthDebug(session, "hello packet during established session nonce=[%d]", nonce);
        Message_shift(msg, 4, NULL);
        return decryptHandshake(session, nonce, msg, header);
    } else {
        // setup keys are already zeroed, not much we can do here.
        cryptoAuthDebug(session, "DROP key packet during established session nonce=[%d]", nonce);
        return -1;
    }
    Assert_true(0);
}