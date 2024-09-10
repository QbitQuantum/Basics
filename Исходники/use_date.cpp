//---------------------------------------------------------------------
// [概要]
//   VBの日付をDOSの日付に変換
// [引数]
//   vbDate	日付型(Date型)の日付
// [戻り値]
//   DOSDATETIME型(u_longのビットフィールド)に変換した値
// [機能説明]
//   VBのDate型を引数で受け取る例
//   VBでの定義
//     Declare Function VbDate2DosDate(ByVal vbDate As Date) As Long
//---------------------------------------------------------------------
__declspec(dllexport) long __stdcall VbDate2DosDate(DATE vbDate)
{
	UDATE udate;
	u_long dwFlags = 0;

	memset(&udate, 0, sizeof(udate));

	// VBの日付型(Date)をUDATE構造体に変換する
	HRESULT hres = VarUdateFromDate(vbDate, dwFlags, &udate);
	if (hres != S_OK) {
		return 0xffffffff;
	}

	return ((udate.st.wYear - 1980) << 25) |
		(udate.st.wMonth << 21) |
		(udate.st.wDay << 16) |
		(udate.st.wHour << 11) |
		(udate.st.wMinute << 5) |
		(udate.st.wSecond / 2);
}