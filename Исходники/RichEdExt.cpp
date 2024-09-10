//---------------------------------------------------------------------------
HRESULT __stdcall TRichEditOleCallback::GetNewStorage(LPSTORAGE *lplpstg)
{
 ILockBytes* pLockBytes;

 if(CreateILockBytesOnHGlobal(0, true, &pLockBytes))return E_OUTOFMEMORY;
 StgCreateDocfileOnILockBytes(pLockBytes, STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 0, lplpstg);
 pLockBytes->Release();
 return 0;
}