int CALLBACK
IoSkSortCallback(
	__in LPARAM First, 
	__in LPARAM Second,
	__in LPARAM Param
	)
{
    WCHAR FirstData[MAX_PATH + 1];
    WCHAR SecondData[MAX_PATH + 1];
	PDIALOG_OBJECT Object;
	PIO_FORM_CONTEXT Context;
	LISTVIEW_OBJECT *ListView;
	PIO_OBJECT_ON_DISK Object1, Object2;
	HWND hWnd;
    int Result;
	HWND hWndList;
	__int64 I1,I2;
	double F1,F2;

	hWnd = (HWND)Param;
	hWndList = GetDlgItem(hWnd, IDC_LIST_IO_SOCKET);

	Object = (PDIALOG_OBJECT)SdkGetObject(hWnd);
	Context = SdkGetContext(Object, IO_FORM_CONTEXT);

	ListView = Context->ListView;
	ListViewGetParam(hWndList, (LONG)First, (LPARAM *)&Object1);
	ListViewGetParam(hWndList, (LONG)Second, (LPARAM *)&Object2);

	ASSERT(Object1 != NULL);
	ASSERT(Object2 != NULL);

	ListView_GetItemText(hWndList, First,  ListView->LastClickedColumn, FirstData,  MAX_PATH);
	ListView_GetItemText(hWndList, Second, ListView->LastClickedColumn, SecondData, MAX_PATH);

    //
    // Symbol or Module name or Line
    //

	switch(ListView->LastClickedColumn){
	
	case _SkSourcePort:
	case _SkDestinePort:
	case _SkIoCount:
	case _SkReadCount:
	case _SkWriteCount:
	case _SkFailedCount:
	case _SkReadBytes:
	case _SkWriteBytes:
	case _SkMaxReadBytes:
	case _SkMeanReadBytes:
	case _SkMaxWriteBytes:
	case _SkMeanWriteBytes:

		I1 = _wcstoi64(FirstData, NULL, 10);
		I2 = _wcstoi64(SecondData, NULL, 10);
		Result = (int)(I1 - I2);
		break;

	case _SkSourceAddress:
	case _SkDestineAddress:
	case _SkProtocal:

		Result = wcsicmp(FirstData, SecondData);
		break;

	case _SkMaxReadLatency:
	case _SkMeanReadLatency:
	case _SkMaxWriteLatency:
	case _SkMeanWriteLatency:

		F1 = wcstod(FirstData, NULL);
		F2 = wcstod(SecondData, NULL);

		if (F1 < F2) {
			Result = -1;
		}
		else if (fabs(F1 - F2) < 0.0001f) {
			Result = 0;
		}
		else if (F1 > F2) {
			Result = 1;
		}
		else {
			Result = 0;
		}
		break;

	default:
		ASSERT(0);
		Result = 0;
	}
	
	return ListView->SortOrder ? Result : -Result;
}