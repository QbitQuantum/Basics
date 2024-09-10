void CredentialKeys_Free(handle_t _MidlEsHandle, PKIWI_CREDENTIAL_KEYS * _pType)
{
	NdrMesTypeFree2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &mscredentialkeys_StubDesc, (PFORMAT_STRING) &ms_credentialkeys__MIDL_TypeFormatString.Format[2], _pType);
}