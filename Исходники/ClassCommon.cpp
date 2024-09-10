STDMETHODIMP CClassCommon::get_sm2keys(BSTR* pVal)
{
	// TODO: 在此添加实现代码
	long keys_len;
	char * keys_value = NULL;

	long pb64_len;
	char * pb64_data = NULL;

	keys_len = sizeof(OPST_PCI_ECCrefPublicKey) + sizeof(OPST_PCI_ECCrefPrivateKey);
	keys_value = (char *)malloc(keys_len);

	memcpy(keys_value,&m_stPublicKey, sizeof(OPST_PCI_ECCrefPublicKey));
	memcpy(keys_value + sizeof(OPST_PCI_ECCrefPublicKey),&m_stPrivateKey, sizeof(OPST_PCI_ECCrefPrivateKey));

	pb64_len = modp_b64_encode_len(keys_len);
	pb64_data = (char *)malloc(pb64_len);

	pb64_len = modp_b64_encode(pb64_data, (char *)keys_value,keys_len);

	::FILE_LOG_STRING(file_log_name, "modp_b64_encode");
	::FILE_LOG_NUMBER(file_log_name, pb64_len);
	::FILE_LOG_STRING(file_log_name, pb64_data);

	//long lLen = MultiByteToWideChar(CP_ACP,0,(LPCSTR)pb64_data,pb64_len,(LPWSTR)pVal,pb64_len * 2);
	BSTR wc_data = SysAllocStringByteLen(NULL, pb64_len * 2); 

	MultiByteToWideChar(CP_ACP,0,(LPCSTR)pb64_data,pb64_len,(LPWSTR)wc_data,pb64_len);

	*pVal = wc_data; // 设置返回值指针。注：不释放内存 

	free(keys_value);
	free(pb64_data);

	return S_OK;
}