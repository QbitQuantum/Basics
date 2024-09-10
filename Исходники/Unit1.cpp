//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	String mac;

	ULONG				nOutBufLen;
	DWORD				ret;
	BYTE*				pBuff;
	PIP_ADAPTER_INFO	pAdapterInfo;

	nOutBufLen = 0;
	::GetAdaptersInfo(NULL,&nOutBufLen);			//必要バッファサイズ取得

	pBuff = new BYTE[nOutBufLen];
	pAdapterInfo = (PIP_ADAPTER_INFO) pBuff;

	ret = ::GetAdaptersInfo(pAdapterInfo,&nOutBufLen);
	if(ret == ERROR_SUCCESS)
	{
		while(1) {
			//MACアドレスを表示
			mac.sprintf(L"%02X-%02X-%02X-%02X-%02X-%02X"
					,pAdapterInfo->Address[0]
					,pAdapterInfo->Address[1]
					,pAdapterInfo->Address[2]
					,pAdapterInfo->Address[3]
					,pAdapterInfo->Address[4]
					,pAdapterInfo->Address[5]);

			Memo1->Lines->Add(pAdapterInfo->Type);
			Memo1->Lines->Add(mac);

			pAdapterInfo = pAdapterInfo->Next;
			if(pAdapterInfo == NULL) break;
		}

	}
	delete	pBuff;

}