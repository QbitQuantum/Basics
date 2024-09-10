BOOL ProRbtDb::CheckAmountInStock(int * retAmount, char* Barcode, CPharmaRobot10Dlg* pdialog)
{
	size_t convertedChars, origsize;
	CString st;
	wchar_t wcstring[100];
	BConsisStockRequest * pBrequest = (BConsisStockRequest *)pdialog->ConsisMessageB;

	//Try to catch the Mutex for CONSIS Access
	//Protect with Mutex the CONSIS resource
	CSingleLock singleLock(&(pdialog->m_MutexBMessage));

	// Attempt to lock the shared resource
	if (singleLock.Lock(INFINITE))
	{
		//log locking success
	}

	//Build B Message
	memset(pdialog->ConsisMessageB, '0', 41);
	pdialog->ConsisMessageB[41] = '\0';

	/*Counter Unit*/
	pBrequest->DemandingCounterUnitId[3] = '1';

	/*Barcode*/
	memset(pBrequest->ArticleId,' ',30);
	size_t barcodesize = strlen(Barcode);
	memcpy(&(pBrequest->ArticleId[30 - barcodesize]), Barcode, barcodesize);

	pdialog->ConsisMessageB[0] = 'B';

	//Print in dialog box the B request
	origsize = 43;
	mbstowcs_s(&convertedChars, wcstring, origsize, pdialog->ConsisMessageB, _TRUNCATE);
	st = wcstring; pdialog->m_listBoxMain.AddString(st);

	pdialog->Consis.SendConsisMessage(pdialog->ConsisMessageB, 41);

	memset(pdialog->Consis.bmessageBuffer, 0, MAX_CONSIS_MESSAGE_SIZE);
	/* Infinitly wait for the reply to arrive from CONSIS by means of AsynchDialogue listener*/
	::WaitForSingleObject(pdialog->Consis.bMessageEvent.m_hObject, INFINITE);

	bConsisReplyHeader *pHeader = (bConsisReplyHeader *)pdialog->Consis.bmessageBuffer;

	//Extract Total Quantity of Item
	char TotalQua[6];
	TotalQua[5] = '\0';
	memcpy(TotalQua, pHeader->TotalQuantity, sizeof(pHeader->TotalQuantity));
	*retAmount =  atoi(TotalQua);

	singleLock.Unlock();

	return TRUE;
}