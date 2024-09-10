HRESULT WriteReadShader(ID3DBlob **ppSBlob, const wchar_t *const sTargetFileName)
{
	HRESULT hr;

	FILE *pFile;

#ifdef AUTSHADERS_SAVE_TO_FILE
	_wfopen_s(&pFile, sTargetFileName, L"wb");
	fwrite((*ppSBlob)->GetBufferPointer(), (*ppSBlob)->GetBufferSize(), 1, pFile);
	fclose(pFile);
#endif
	
	int nSize = 0;
	_wfopen_s(&pFile, sTargetFileName, L"rb");

	fseek(pFile, 0, SEEK_END);
	nSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	
	*ppSBlob = NULL;
	V_RETURN(D3DCreateBlob(nSize, ppSBlob));

	fread_s((*ppSBlob)->GetBufferPointer(), nSize, nSize, 1, pFile);
	
	fclose(pFile);

	return S_OK;
}