void CATSmsMessagingRead::PopulateScaFieldsAndRemove(TPtrC8& aPdu, RMobilePhone::TMobileAddress& aGsmServiceCentre)
//
// Populate the SCA field in the MM ETel structure from the SCA prepended in a received PDU.
//
	{
	const TUint8 KTONBitMask =0x70;
	const TUint8 KNPIBitMask=0x0f;
	const TUint8 KTONBitShift=4;
	const TUint8 KNPIBitShift=0;
	_LIT(KInternationalPrefix,"+");

	__ASSERT_ALWAYS(aPdu.Length()>0,Panic(ECMTHandlerDesPassedWithZeroLength));

	aGsmServiceCentre.iTypeOfNumber=(RMobilePhone::TMobileTON)0;
	aGsmServiceCentre.iNumberPlan=(RMobilePhone::TMobileNPI)0;
	aGsmServiceCentre.iTelNumber.Zero();
	
	TUint8 len=aPdu[0];
	
	if(len==0)
		{
		// A zero length SCA has been prepended - just strip this first byte off
		aPdu.Set(aPdu.Mid(len+1));
		return;
		}

	TUint8 numDes=aPdu[1];
	aGsmServiceCentre.iTypeOfNumber=(RMobilePhone::TMobileTON)((numDes&KTONBitMask)>>KTONBitShift);
	aGsmServiceCentre.iNumberPlan=(RMobilePhone::TMobileNPI)((numDes&KNPIBitMask)>>KNPIBitShift);

	if(aGsmServiceCentre.iTypeOfNumber==RMobilePhone::EInternationalNumber)
		aGsmServiceCentre.iTelNumber.Append(KInternationalPrefix);

	TInt i;
	TUint16 digit;
	for(i=2;i<(len+1);i++)
		{
		digit=(TUint16)((aPdu[i]&0x0f)+0x30);
		aGsmServiceCentre.iTelNumber.Append(digit);
		digit=(TUint16)(((aPdu[i]&0xf0)>>4)+0x30);
		if(digit==0x003f)		// 'F' is the padding digit at the end of a number
			break;
		aGsmServiceCentre.iTelNumber.Append(digit);
		}
	aPdu.Set(aPdu.Mid(len+1));
	}