void TestGlobalMethods::TestReplaceFileExtension()
{
	CStdString sFile = _T("NotPDF.doc");
	CStdString sExtension = _T("pdf");
	CStdString sResult = ReplaceFileExtension(sFile, sExtension.c_str());
	int iPosition = sResult.ReverseFind(_T('.'));
	CStdString sNewExtension = sResult.Right((int)sResult.length() - (iPosition + 1));
	assertMessage(0 != iPosition, _T("Failed to locate file extension separator '.'"));
	assertMessage(0 == (int)sExtension.CompareNoCase(sNewExtension), _T("Failed to match the expected extension 'pdf'"));

	sFile = _T("IsPDF.pdf");
	sExtension = _T("pdf");
	sResult = ReplaceFileExtension(sFile, sExtension.c_str());
	sNewExtension = sResult.Right((int)sResult.length() - (sResult.Find(_T("."), 0) + 1));
	assertMessage(sExtension.length() == sNewExtension.length(), _T("We expected the extension lengths to be equal"));

	sFile = _T("NoExtension");
	sExtension = _T("pdf");
	sResult = ReplaceFileExtension(sFile, sExtension.c_str());
	iPosition = sResult.ReverseFind(_T('.'));
	assertMessage(0 != iPosition, _T("Failed to locate file extension separator '.'"));
	assertMessage(0 == (int)sExtension.CompareNoCase(sResult.Right((int)sResult.length() - (iPosition + 1))), _T("Failed to match the expected extension 'pdf'"));
}