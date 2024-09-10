// Decryption functions
bool BotanRSA::decrypt(PrivateKey* privateKey, const ByteString& encryptedData, ByteString& data, const std::string padding)
{
	// Check if the private key is the right type
	if (!privateKey->isOfType(BotanRSAPrivateKey::type))
	{
		ERROR_MSG("Invalid key type supplied");

		return false;
	}

	std::string lowerPadding;
	lowerPadding.resize(padding.size());
	std::transform(padding.begin(), padding.end(), lowerPadding.begin(), tolower);
	std::string eme;

	if (!lowerPadding.compare("rsa-pkcs"))
	{
		eme = "PKCS1v15";
	}
	else if (!lowerPadding.compare("rsa-pkcs-oaep"))
	{
		eme = "EME1(SHA-160)";
	}
	else if (!lowerPadding.compare("rsa-raw"))
	{
		eme = "Raw";
	}
	else
	{
		ERROR_MSG("Invalid padding mechanism supplied (%s)", padding.c_str());

		return false;
	}

	BotanRSAPrivateKey* pk = (BotanRSAPrivateKey*) privateKey;
	Botan::RSA_PrivateKey* botanKey = pk->getBotanKey();

	if (!botanKey)
	{
		ERROR_MSG("Could not get the Botan private key");

		return false;
	}

	Botan::PK_Decryptor_EME* decryptor = NULL;
	try
	{
		decryptor = new Botan::PK_Decryptor_EME(*botanKey, eme);
	}
	catch (...)
	{
		ERROR_MSG("Could not create the decryptor token");

		return false;
	}

	// Perform the decryption operation
	Botan::SecureVector<Botan::byte> decResult;
	try
	{
		decResult = decryptor->decrypt(encryptedData.const_byte_str(), encryptedData.size());
	}
	catch (...)
	{
		ERROR_MSG("Could not decrypt the data");

		delete decryptor;

		return false;
	}

	// Return the result
	if (!eme.compare("Raw"))
	{
		// We compensate that Botan removes leading zeros
		int modSize = pk->getN().size();
		int decSize = decResult.size();
		data.resize(modSize);
		memcpy(&data[0] + modSize - decSize, decResult.begin(), decSize);
	}
	else
	{
		data.resize(decResult.size());
		memcpy(&data[0], decResult.begin(), decResult.size());
	}

	delete decryptor;

	return true;
}