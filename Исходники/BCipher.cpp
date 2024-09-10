STDMETHODIMP CBCipher::get_BlockSize(short *pVal)
{
	if(!m_ctx.cipher)return SetErrorInfo(s_strAlgoError);

	*pVal = EVP_CIPHER_CTX_block_size(&m_ctx);

	return S_OK;
}