// ---------------------------------------------------------------------------
// CAtPhbkStoreRead::ParseResponseL
// other items were commented in a header
// ---------------------------------------------------------------------------
void CAtPhbkStoreRead::ParseResponseL(const TDesC8& /*aResponseBuf*/)
	{
	if( iState == ESetStoreNameComplete )
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
	else if( iState == EReadEntryComplete )
		{
		/**
		* +CPBR = <index>,<number>,<129/145>,<text> 
		* OK    
		*/
		RArray<TPtrC8> array;
		CleanupClosePushL(array);
		iParser->ParseRespondedBuffer(array,Buffer());
		// remove the string of AT+CPBR=..
		if(array[0].MatchF(KAnyATCommand) != KErrNotFound)
			{
			array.Remove(0);
			}
		TInt count = array.Count();
#ifdef _DEBUG		
		for( TInt i=0;i<count;i++ )
			{
			LOGTEXT3(_L8("CAtPhbkStoreRead::ParseResponseL\tarray[%d]=%S"),i,&array[i]); 
			}
#endif		
		if((array[1].Match(KLtsyOkString) == KErrNone))
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNone;
			iEndFlag = ETrue;
			return; 
			}
		else if((array[1].Match(KLtsyErrorString) == KErrNone))
			{
			CleanupStack::PopAndDestroy();
			iError = KErrGeneral;
			iEndFlag = ETrue;
			return; 
			}
	  
		iError = KErrNone;
		//remove number line if it has 
		if( array[0].MatchF(KCPBRSResponseString) == KErrNotFound )
			{
			array.Remove(0);
			}
		if( array[0].MatchF(KCPBRSResponseString) == KErrNotFound )
			{
			CleanupStack::PopAndDestroy();
			iError = KErrNotFound;
			return;
			}
		//parse index
		TLex8 lex(array[1]);
		TUint16 val;
		TInt ret = lex.Val(val,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		//Index  
		iReadEntry.iIndex = val;             
		iReadEntry.iNumber.Copy(array[2]);   
		//Parse TON/NPI
		TLex8 lex1(array[3]);
		TUint16 val1;
		ret = lex1.Val(val1,EDecimal);
		if(ret != KErrNone)
			{
			CleanupStack::PopAndDestroy();
			iError = ret;
			return;
			}
		 //TON/NPI
		iReadEntry.iTon = (TUint8)val1;  
		iReadEntry.iText.Copy(array[4]);
		CleanupStack::PopAndDestroy();
		} 
  	}