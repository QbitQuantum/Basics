CaesarCipher operator*(const CaesarCipher &c1, const CaesarCipher &c2)
{
	assert(((c2.key != 0 && c2.ciphertext.compare("") == 0 && c2.plaintext.compare("") == 0) || (c1.ciphertext.compare(c2.plaintext) == 0)) && "Cipher composition failed, text doesn't match.");
	CaesarCipher result;

	result.init(c1.plaintext, c2.ciphertext, ((c1.key + c2.key) % 26));
	if (c2.ciphertext.compare("") == 0)
			result.encrypt();
	return result;
}