PLSA_UNICODE_STRING CDialupass::GetLsaData(LPSTR KeyName)
{
	LSA_OBJECT_ATTRIBUTES LsaObjectAttribs;
	LSA_HANDLE LsaHandle;
	LSA_UNICODE_STRING LsaKeyName;
	NTSTATUS nts;
	PLSA_UNICODE_STRING OutData;

	ZeroMemory(&LsaObjectAttribs,sizeof(LsaObjectAttribs));
	nts=LsaOpenPolicy(NULL,&LsaObjectAttribs,POLICY_GET_PRIVATE_INFORMATION,&LsaHandle);
	if(nts!=0)return NULL;
	AnsiStringToLsaStr(KeyName, &LsaKeyName);
	nts=LsaRetrievePrivateData(LsaHandle, &LsaKeyName,&OutData);
	if(nts!=0)return NULL;
	nts=LsaClose(LsaHandle);
	if(nts!=0)return NULL;
	return OutData;
}