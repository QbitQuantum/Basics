// ---------------------------------------------------------------------------
// CAtSmsStoreReadAll::ParseResponseL
// other items were commented in a header
// ---------------------------------------------------------------------------
void CAtSmsStoreReadAll::ParseResponseL(const TDesC8& /*aResponseBuf*/)
	{
	/**
	* Response:+CMGR:<stat>,[<alpha>],<length><CR><LF><pdu>
	*/
	iError = KErrNone;	
	RArray<TPtrC8> array;
	CleanupClosePushL(array);
	iParser->ParseRespondedBuffer(array,Buffer());
	if(array[0].MatchF(KAnyATCommand)!=KErrNotFound)
		{
		array.Remove(0);
		}
	TInt count = array.Count();
#ifdef _DEBUG
	for( TInt i=0;i<count;i++ )
		{
        LOGTEXT3(_L8("CAtSmsStoreReadAll::ParseResponseL\tarray[%d]=%S"),i,&array[i]);  
		}
#endif   
	if (count <= 1)
		{
		CleanupStack::PopAndDestroy();
		iError = KErrNotFound;
		return;
		}
	if(array[0].MatchF(KCMGRResponseString)==KErrNotFound)
		{
		LOGTEXT(_L8("CAtSmsStoreReadAll::ParseResponseL\tFound +CMGR String!"));
		CleanupStack::PopAndDestroy();
		iError = KErrNotFound;
		return;
		}
	// parse the message status
	TLex8 lex(array[1]);
	TUint16 val;
	TInt ret=lex.Val(val,EDecimal);
	if(ret!=KErrNone)
		{
		CleanupStack::PopAndDestroy();
		iError = ret;
		return;
		}
	iSmsData.iMessageStatus = val;
	
	//parse the message length
	TLex8 lex1(array[3]);
	TUint msgLength;
	ret=lex1.Val(msgLength,EDecimal);
	if(ret!=KErrNone)
		{
		CleanupStack::PopAndDestroy();
		iError = ret;
		return;
		}
	LOGTEXT2(_L8("CAtSmsStoreReadAll::ParseResponseL\tMessage Length=%d"),msgLength);
	TBuf8<KMaxAsciiPduLength>  pdu;	   //Binary Message pdu
	SmsAtUtil::ConvertAsciiToBinary(array[4],pdu);
	TPtrC8 pduPtr(pdu);
	
	RMobilePhone::TMobileAddress gsmServiceCentre;   //messages's SCA
	if (msgLength*2 < array[4].Length())
		{
		// There is an SCA prepended so remove this and store it in iGsmServiceCentre
		SmsAtUtil::ReadAndRemoveAddressFromPdu(pduPtr,gsmServiceCentre);
		}
	iSmsData.iSmsMsg = pduPtr;
	iSmsData.iServiceCentre = gsmServiceCentre.iTelNumber;
	iSmsData.iMobileScNPI = gsmServiceCentre.iNumberPlan;
	iSmsData.iMobileScTON = gsmServiceCentre.iTypeOfNumber;
	LOGTEXT2(_L8("CAtSmsStoreReadAll::ParseResponseL\tMessage Status=%d"),
			                          iSmsData.iMessageStatus);
	LOGTEXT3(_L8("CAtSmsStoreReadAll::ParseResponseL\tSmsMsg=%S, ServiceCentre=%S"), 
			                          &iSmsData.iSmsMsg, &iSmsData.iServiceCentre);
	CleanupStack::PopAndDestroy(&array);
	}