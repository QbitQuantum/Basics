void CMainControlEngine::GetIapNumFromFile()
{
	
	TBuf<255> nParmValue;

	iDBEngine->GetSystemParmWithSQL(KIAPNUM,nParmValue); 

	if(nParmValue.Length ()==0)
	{
		// open the IAP communications database 
		CCommsDatabase* commDB = CCommsDatabase::NewL(EDatabaseTypeIAP);
		CleanupStack::PushL(commDB);

		// initialize a view 
		CCommsDbConnectionPrefTableView* commDBView = commDB->OpenConnectionPrefTableInRankOrderLC(ECommDbConnectionDirectionUnknown);
		//CCommsDbConnectionPrefTableView* commDBView = commDB->OpenConnectionPrefTableInRankOrderLC(ECommDbConnectionDirectionOutgoing);

		// go to the first record 
		TInt err=commDBView->GotoFirstRecord();

		if(err==KErrNotFound)
		{
			iIapValue=-1;
		}
		else
		{
			// Declare a prefTableView Object.
			CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref pref;
			// read the connection preferences 
			commDBView->ReadConnectionPreferenceL(pref);
			TUint32 iap= pref.iBearer.iIapId; 
			iIapValue=((TInt)iap);

			//保存到数据库中
			SetIapNum(iIapValue);
		}
		// pop and destroy the IAP View 
		CleanupStack::PopAndDestroy(commDBView);

		// pop and destroy the database object
		CleanupStack::PopAndDestroy(commDB);
	}
	else
	{
		TLex temp(nParmValue);
		temp.Val( iIapValue);
	}
}