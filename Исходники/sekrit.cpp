bool Sekrit::IsKeyValid() const
{
	if(!m_impl->keyHasBeenSet)
		return false;

	Plaintext plaintext = DoDecrypt();
	bool IsValid = VerifyHash(plaintext, m_impl->header.iv);
	return IsValid;
}