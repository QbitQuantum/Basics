void CFB_ModePolicy::TransformRegister()
{
	CRYPTOPP_ASSERT(m_cipher->IsForwardTransformation());	// CFB mode needs the "encrypt" direction of the underlying block cipher, even to decrypt
	m_cipher->ProcessBlock(m_register, m_temp);
	unsigned int updateSize = BlockSize()-m_feedbackSize;
	memmove_s(m_register, m_register.size(), m_register+m_feedbackSize, updateSize);
	memcpy_s(m_register+updateSize, m_register.size()-updateSize, m_temp, m_feedbackSize);
}