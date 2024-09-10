/*! \brief  Verify signature on data.

    \param    data              input, signed data.
    \param    signature         input, signature.
    \param    userCtx           input, user context.

    \returns  Boolean indicating whether signature is valid or not.
*/
bool OsmsOpenIPMPMessenger::VerifySignature(const std::string& data, DigitalSignature*
    signature, UserContext* userCtx) {
	HashContext hashData;
	cryptoManager->init(&hashData, "SHA1");
	hashData.hashUpdate((unsigned char*)data.data(), data.size());
	hashData.hashFinal();

	return (hashData.verifySignature(signature->get_SignatureValue_octets()->octets,
    signature->get_SignatureValue_octets()->len, userCtx->getCaCertChain()));
}