extern "C" void SetMsiReporter(LPCSTR strAction, LPCSTR strDesc,DWORD h) {
	dwReporterType = REPORT_MSI;
	hMsiHandle = h;

#ifdef DONT_NEED
    /* this is performed in the Wix installer */
	MSIHANDLE hRec = MsiCreateRecord(4);
  
    MsiRecordClearData(hRec);
	MsiRecordSetStringA(hRec,1,strAction);
	MsiRecordSetStringA(hRec,2,strDesc);
	MsiRecordSetStringA(hRec,3,"[1]:([2])([3])([4])");

	MsiProcessMessage(h,INSTALLMESSAGE_ACTIONSTART, hRec);
	
    MsiCloseHandle(hRec);
#endif
}