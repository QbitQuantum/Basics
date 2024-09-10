// 从图片地址取图片名
CString GetImageName(const CString& img)
{
	LPTSTR pos = StrRChr(img, NULL, _T('/'));
	CString imgName = (pos == NULL ? img : pos + 1);
	int right = imgName.Find(_T("?"));
	return right == -1 ? imgName : imgName.Left(right);
}