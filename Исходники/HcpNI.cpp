void* HcpNI::Memset(void* pDest, const hcp_Int Value, const hcp_Size_t Length, void* pContext) {
	void* result = NULL;

	if (pContext != NULL) {
		auto hni = static_cast<HcpNI*>(pContext);
		result = hni->Memset(pDest, Value, Length);
	}

	return result;
}