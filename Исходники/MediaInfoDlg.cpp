CMediaInfoDlg::CMediaInfoDlg()
{
	LANGID   _SysLangId   =   GetSystemDefaultLangID();

	if(PRIMARYLANGID(_SysLangId)   ==   LANG_CHINESE) {
		if(SUBLANGID(_SysLangId)   ==   SUBLANG_CHINESE_SIMPLIFIED)
			codepage = 936;		//Simplified Chinese GBK
		else if(SUBLANGID(_SysLangId)   ==   SUBLANG_CHINESE_TRADITIONAL)
			codepage = 950;		//Traditional Chinese Big5
		else if(SUBLANGID(_SysLangId)   ==   SUBLANG_CHINESE_HONGKONG)
			codepage = 950;		//Traditional Chinese Big5
	} else if(PRIMARYLANGID(_SysLangId)   ==   LANG_JAPANESE)
		codepage = 932;			//Japanese Shift-JIS
	else if(PRIMARYLANGID(_SysLangId)   ==   LANG_KOREAN)
		codepage = 949;			//Korean

	m_wndListCtrl.RegisterClass();
}