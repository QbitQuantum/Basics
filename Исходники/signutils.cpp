SISSignatureCertificateChain* makeChain(SISField* controller, const char* certData, const char* keyData, const char* passphrase, SigType type) {
	EVP_PKEY* publicKey = NULL;
	SISCertificateChain* chain = makeChain(certData, &publicKey);
	if (!publicKey) {
		fprintf(stderr, "No public key found!\n");
		throw SignBadCert;
	}
	SISSignature* signature = makeSignature(controller, keyData, passphrase, type, publicKey);
	EVP_PKEY_free(publicKey);
	SISArray* signatures = new SISArray(SISFieldType::SISSignature);
	signatures->AddElement(signature);
	return new SISSignatureCertificateChain(signatures, chain);
}