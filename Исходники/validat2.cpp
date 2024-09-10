bool CryptoSystemValidate(PK_Decryptor &priv, PK_Encryptor &pub)
{
	LC_RNG rng(9375);
	const byte *message = (byte *)"test message";
	const int messageLen = 12;
	SecByteBlock ciphertext(priv.CipherTextLength(messageLen));
	SecByteBlock plaintext(priv.MaxPlainTextLength(ciphertext.size));
	bool pass = true, fail;

	pub.Encrypt(rng, message, messageLen, ciphertext);
	fail = (messageLen!=priv.Decrypt(ciphertext, priv.CipherTextLength(messageLen), plaintext));
	fail = fail || memcmp(message, plaintext, messageLen);
	pass = pass && !fail;

	cout << (fail ? "FAILED    " : "passed    ");
	cout << "encryption and decryption\n";

	return pass;
}