// ---------------------------------------------------------------------------
// CAtPhbkEnGetInfo::ParseResponseL
// other items were commented in a header
// ---------------------------------------------------------------------------
void CAtPhbkEnGetInfo::ParseResponseL(const TDesC8& /*aResponseBuf*/)
	{
	if( iState==ESetEnStoreComplete )
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
	else if( iState==EGetEnStoreInfoComplete )
		{
		/**
		* Here is an Example 
		* +CPBS: "EN",2,16 
        * phonebooken is selected,2 locations are used and 
        * total 16 locations are available
		*/
		iError = KErrNone;
		RArray<TPtrC8> array;
		CleanupClosePushL(array);
		iParser->ParseRespondedBuffer(array,Buffer());
		//remove AT+CPBS
		if(array[0].MatchF(KAnyATCommand)!=KErrNotFound)
			{
			array.Remove(0);
			}
		TInt count = array.Count();
#ifdef _DEBUG			
		for( TInt i=0;i<count;i++ )
			{
		    LOGTEXT3(_L8("CAtPhbkEnGetInfo::ParseResponseL\tarray[%d]=%S"),
		    		      i,&array[i]);     
			}
#endif			
		if (count <= 1)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
		if(array[0].MatchF(KCPBSResponseString)==KErrNotFound)
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
				
		//parse used
		TLex8 lex(array[2]);
		TUint16 val;
		TInt ret=lex.Val(val,EDecimal);
		if(ret!=KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iUsed = val;
		
		//parse total
		TLex8 lex1(array[3]);
		ret=lex1.Val(val,EDecimal);
		if(ret!=KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		iTotal = val;
	    LOGTEXT3(_L8("CAtPhbkEnGetInfo::ParseResponseL\tPreferred store used=%d, total=%d"), 
	    		                                iUsed,iTotal);
		CleanupStack::PopAndDestroy(&array);
		}
	}