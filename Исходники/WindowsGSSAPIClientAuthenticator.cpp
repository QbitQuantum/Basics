bool WindowsGSSAPIClientAuthenticator::setChallenge(const boost::optional<ByteArray>& challengeData) {
    /* Following http://tools.ietf.org/html/rfc4752, https://msdn.microsoft.com/en-us/library/windows/desktop/aa380496%28v=vs.85%29.aspx */

    if (step_ == BuildingSecurityContext) {
        buildSecurityContext(challengeData);
    }
    else if (step_ == SecurityLayerNegotiation) {
        if (!challengeData) {
            SWIFT_LOG(debug) << "Empty message received from the server" << std::endl;
            error_ = true;
            return false;
        }

        SafeByteArray challenge;
        errorCode_ = decryptMessage(&contextHandle_, challengeData.get(), challenge);
        if (isError()) {
            return false;
        }

        if (challenge.size() != 4) {
            SWIFT_LOG(debug) << "Token received from the server of incorrect length: " << challenge.size() << std::endl;
            error_ = true;
            return false;
        }

        unsigned char* challengePointer = vecptr(challenge);

        unsigned char serverSecurityLayer = challengePointer[0];
        if (serverSecurityLayer == 0) {
            SWIFT_LOG(debug) << "Server supports unknown security layer, assuming no security layer" << std::endl;
            serverSecurityLayer = SECURITY_LAYER_NONE;
        }
        else if (serverSecurityLayer == SECURITY_LAYER_NONE) {
            SWIFT_LOG(debug) << "Server supports no security layer" << std::endl;
        }
        else {
            SWIFT_LOG(debug) << "Server supports security layer" << std::endl;
        }

        unsigned int serverMaximumBuffer = (challengePointer[1] << 16) |
                        (challengePointer[2] << 8) |
                        (challengePointer[3] << 0);

        if ((serverSecurityLayer == SECURITY_LAYER_NONE) && (serverMaximumBuffer != 0)) {
            SWIFT_LOG(debug) << "Server supports no security layer but has maximum buffer size" << serverMaximumBuffer << std::endl;
            error_ = true;
            return false;
        }

        SafeByteArray message(4);

        /* Commenting this out as streamSizes was not obtained before
        if (message.size() > streamSizes_.cbMaximumMessage) {
            error_ = true;
            return false;
        } */

        unsigned char* messagePointer = vecptr(message);
        messagePointer[0] = SECURITY_LAYER_NONE;

        /* The next 3 bytes indicate the client's maximum size buffer which is set to 0 as we do not support a security layer */
        messagePointer[1] = 0;
        messagePointer[2] = 0;
        messagePointer[3] = 0;

        /* The authorization identity is omitted as it is the same as the authentication identity */

        errorCode_ = encryptMessage(&contextHandle_, sizes_, message, response_);
        if (isError()) {
            return false;
        }

        step_ = ServerAuthenticated;
    }

    if (isError()) {
        return false;
    }

    return true;
}