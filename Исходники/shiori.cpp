/* ----------------------------------------------------------------------------
 * 栞 Method / request
 */
SHIORI_API HGLOBAL __cdecl request(HGLOBAL hGlobal_request, long& len)
{
	AutoGrobalFree autoFree(hGlobal_request);
   ATLTRACE2(_T("[SHIORI::request]\n"));
	ByteArray res;
	bool rc = api->Request((const BYTE*) hGlobal_request, len, res);
	if (!rc) {
		CreateBatRequestResponse(res ,"SHIOLINK2 API return false");
	}

	// 応答情報の作成
	HGLOBAL hRES =GlobalAlloc(GMEM_FIXED ,res.GetCount());
	CopyMemory(hRES ,res.GetData() ,res.GetCount());
	len =(long)res.GetCount();
	return hRES;
}