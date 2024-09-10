/*********************************************************************
 *	"COMXX:" ポートのプロパティを見る.
 *********************************************************************
 */
void RS_printCommInfo(char *comXX)
{
	BOOL	rc;
	HANDLE	com_handle;
	COMMPROP CommProp;

	printf("%s:",comXX);
	
	com_handle = CreateFile(
		comXX,									/* シリアルポートの文字列 */
		GENERIC_READ | GENERIC_WRITE   ,			/* アクセスモード */
		0,
		NULL,										/* セキュリティ属性 */
		OPEN_EXISTING,								/* 作成フラグ	*/
		0,											/* 属性 */
		NULL										/* テンプレートのハンドル	*/
	);
	if(	comHandle == INVALID_HANDLE_VALUE) {
		printf(" Can't Open .");
	}else{
		rc = GetCommProperties(com_handle,&CommProp);
		if(rc) {
#if	0
　　DWORD dwMaxTxQueue； 　　// バイト単位の最大送信バッファサイズ
　　DWORD dwMaxRxQueue； 　　// バイト単位の最大受信バッファサイズ
　　DWORD dwMaxBaud； 　　　 　// ボーレート最大値
　　DWORD dwProvSubType； 　 // 特定プロバイダータイプ
　　DWORD dwProvCapabilities； // サポートされた関数
#endif
			printf("TxQue=%ld,RxQue=%ld,MaxBaud=%lx"
				,CommProp.dwMaxTxQueue
				,CommProp.dwMaxRxQueue
				,CommProp.dwMaxBaud);
		}

#if	0
		static	DCB	com_dcb;
		memset(&com_dcb,0,sizeof(com_dcb));

		com_dcb.DCBlength = sizeof(DCB);
		rc = GetCommState(comHandle,&com_dcb);
//		if(rc) 
		{
//		com_dcb.BaudRate = baudrate;
//		com_dcb.ByteSize = 8;
//		com_dcb.Parity   = NOPARITY;
//		com_dcb.StopBits = ONESTOPBIT;
			printf("Baud=%ld bits=%d parity=%d stop=%d"
				,com_dcb.BaudRate 
				,com_dcb.ByteSize 
				,com_dcb.Parity   
				,com_dcb.StopBits 
			);
		}
#endif
		CloseHandle(com_handle);

	}
	printf("\n");
}