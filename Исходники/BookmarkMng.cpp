void Bookmark::Save( CMixiDataList& bookmark )
{
	CString fileName;
	fileName.Format( _T("%s\\favorite.dat"), theApp.GetAppDirPath());

	FILE* fp = _wfopen(fileName, _T("w"));

	INT_PTR count = bookmark.size();
	CString buf;
	CString type;

	for (int i=0; i<count; i++) {
		CMixiData& data = bookmark[i];
#ifdef BT_MZ3
		switch (data.GetAccessType()) {
		case ACCESS_BBS:
			type = _T("b");
			break;
		case ACCESS_ENQUETE:
			type = _T("e");
			break;
		case ACCESS_EVENT:
			type = _T("v");
			break;
		case ACCESS_EVENT_JOIN:
			type = _T("j");
			break;
		}
#endif
		buf.Format(_T("%s<>%d<>%s<>%s\n"), type, data.GetID(), data.GetName(), data.GetTitle());
		fputws(buf, fp);
	}

	fclose(fp);
}