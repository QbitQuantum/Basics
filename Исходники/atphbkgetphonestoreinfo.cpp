// ---------------------------------------------------------------------------
// CAtPhbkGetPhoneStoreInfo::ParseResponseL
// other items were commented in a header
// ---------------------------------------------------------------------------
void CAtPhbkGetPhoneStoreInfo::ParseResponseL(const TDesC8& /*aResponseBuf*/)
	{
	if( iState == ESetPhoneStoreComplete )
		{
		if (CurrentLine().Match(KLtsyOkString) == 0)
			{
			iError = KErrNone;
			}
		else
			{
			iError = KErrGeneral;
			}
		}
	else if( iState == EGetPhoneStoreInfoComplete )
		{
		/**
		* Here is an Example 
		* +CPBS: "SM",6,250  
        * ADN phonebook is selected,6 locations are used and 
        * total 250 locations are available
		*/
		iError = KErrNone;
		RArray<TPtrC8> array;
		CleanupClosePushL(array);
		iParser->ParseRespondedBuffer(array,Buffer());
		//remove AT+CPBS
		if(array[0].MatchF(KAnyATCommand) != KErrNotFound)
			{
			array.Remove(0);
			}
		TInt count = array.Count();
#ifdef _DEBUG			
		for( TInt i=0;i<count;i++ )
			{
		    LOGTEXT3(_L8("CAtPhbkGetPhoneStoreInfo::ParseResponseL\tarray[%d]=%S"),
		    		      i,&array[i]);     
			}
#endif			
		if (count <= 1)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
		if(array[0].MatchF(KCPBSResponseString) == KErrNotFound)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
				
		//parse used
		TLex8 lex(array[2]);
		TUint16 val;
		TInt ret = lex.Val(val,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iPhoneStoreInfo.iUsedEntries = val;
		
		//parse total
		TLex8 lex1(array[3]);
		ret = lex1.Val(val,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iPhoneStoreInfo.iTotalEntries = val;
		iPhoneStoreInfo.iType = RMobilePhoneStore::EPhoneBookStore;
	    LOGTEXT3(_L8("CAtPhbkGetPhoneStoreInfo::ParseResponseL\tPreferred store used=%d, total=%d"), 
	    		                                iPhoneStoreInfo.iUsedEntries,iPhoneStoreInfo.iTotalEntries);
		CleanupStack::PopAndDestroy(&array);
		}
	else 
		{
		/**
		* Parse result of AT+CPMS? 
		* Response:+CPMS:<mem1>,<used1>,<total1>,<mem2>,<used2>,<total2>
		* Here only the first mem is used. mem1 is SM
		*/
		iError = KErrNone;
		RArray<TPtrC8> array;
		CleanupClosePushL(array);
		iParser->ParseRespondedBuffer(array,Buffer());
		if(array[0].MatchF(KAnyATCommand) != KErrNotFound)
			{
			array.Remove(0);
			}
		TInt Count = array.Count();
		if (Count <= 1)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
		if(array[0].MatchF(KCPMSResponseString) == KErrNotFound)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
		//parse name 
		TPtrC8 name(array[1]);
		
		//parse used
		TLex8 lex(array[2]);
		TUint16 val;
		TInt ret = lex.Val(val,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iPhoneStoreInfo.iUsedEntries = val;
		
		//parse total
		TLex8 lex1(array[3]);
		ret = lex1.Val(val,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iPhoneStoreInfo.iTotalEntries = val;
		iPhoneStoreInfo.iType = RMobilePhoneStore::EShortMessageStore;
		LOGTEXT3(_L8("CAtPhbkGetPhoneStoreInfo::ParseResponseL\tPreferred store used=%d, total=%d"), 
			    		                        iPhoneStoreInfo.iUsedEntries,iPhoneStoreInfo.iTotalEntries);
		CleanupStack::PopAndDestroy(&array);
		}
	}