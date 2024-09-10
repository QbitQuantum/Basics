/* イベントログの読み取り */
void ReadLog(void)
{
	DWORD BufSize;
	DWORD ReadBytes;
	DWORD NextSize;
	BOOL bResult;
	DWORD i;
	char *cp;
	char *pSourceName;
	char *pComputerName;
	HANDLE hEventLog = NULL;
	EVENTLOGRECORD *pBuf = NULL;
	char **Args = NULL;

	/* イベントログのオープン */
	hEventLog = OpenEventLog(NULL, "Application");

	if(hEventLog == NULL) {
		printf("event log can not open.\n");
		goto Exit;
	}

	for(;;) {
		/* イベントログのサイズ取得 */
		BufSize = 1;
		pBuf = (EVENTLOGRECORD *)GlobalAlloc(GMEM_FIXED, BufSize);

		bResult = ReadEventLog(
			hEventLog,
			EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
			0,
			pBuf,
			BufSize,
			&ReadBytes,
			&NextSize);

		if(!bResult && GetLastError() != ERROR_INSUFFICIENT_BUFFER) break;

		GlobalFree(pBuf);
		pBuf = NULL;

		/* バッファ割り当て */
		BufSize = NextSize;
		pBuf = (EVENTLOGRECORD *)GlobalAlloc(GMEM_FIXED, BufSize);

		/* イベントログの読み取り */
		bResult = ReadEventLog(
			hEventLog,
			EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
			0,
			pBuf,
			BufSize,
			&ReadBytes,
			&NextSize);

		if(!bResult) break;

		eventlog_record rec( pBuf );

		/* 読み取ったイベントの表示 */
		printf("レコード番号: %d\n", rec.RecordNumber() );
		time_t t = rec.TimeGenerated();
		printf("生成時刻: %s", ctime( &t ) );
		t = rec.TimeWritten();
		printf("書き込み時刻: %s", ctime( &t ) );
		printf("イベントID: %08x\n", rec.EventID() );

		printf( "イベントの種別: %s\n", rec.EventTypeText().c_str() );

		cp = (char *)pBuf;
		cp += sizeof(EVENTLOGRECORD);

		pSourceName = cp;
		cp += strlen(cp)+1;

		pComputerName = cp;
		cp += strlen(cp)+1;

		printf("ソース名: %s\n", rec.SourceName().c_str() );
		printf("コンピュータ名: %s\n", rec.ComputerName().c_str() );

		/* カテゴリの表示 */
		printf("二次カテゴリ: ", pBuf->EventCategory);
		DispMessage(pSourceName, "CategoryMessageFile", NULL, pBuf->EventCategory);

		/* メッセージの表示 */
		Args = GetArgs(pBuf);

		printf("メッセージ: ");
		DispMessage(pSourceName, "EventMessageFile", (const char **)Args, pBuf->EventID);

		if(Args != NULL) {
			GlobalFree(Args);
			Args = NULL;
		}

		/* 固有データの表示 */
		if(pBuf->DataLength > 0) {
			printf("固有データ: ");
			for(i=0; i<pBuf->DataLength; i++) printf("%02x ", *(((unsigned char *)pBuf)+(pBuf->DataOffset)+i));
			printf("\n");
		}

		printf("\n");

		/* バッファ解放 */
		GlobalFree(pBuf);
		pBuf = NULL;
	}

Exit: /* 後処理 */
	if(pBuf != NULL) GlobalFree(pBuf);
	if(Args != NULL) GlobalFree(Args);
	if(hEventLog != NULL) CloseEventLog(hEventLog);
}