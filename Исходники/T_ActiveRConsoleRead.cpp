TBool	CT_ActiveRConsoleRead::KickStartL(const TDesC& aSection, const TInt aAsyncErrorIndex, RConsole& aConsole)
/**
 * Kick Start the object and set up intials
 *	@param		aSection			The section in the ini containing data for the command
 * 	@param		aAsyncErrorIndex	Command index for async calls to return errors to
 *	@param		aConsole			The RConsole object
 */
	{
	TBuf<KMaxTestExecuteCommandLength>	tempStore;
	iSection.Set(aSection);

	iColourValueBlack	=KBlack;
	iColourValueWhite	=KWhite;
	iDataWrapperBase.GetUint8FromConfig(iSection, KFldColourBlack(), iColourValueBlack);
	iDataWrapperBase.GetUint8FromConfig(iSection, KFldColourWhite(), iColourValueWhite);

	iTimeOut=KDefaultTimeout;
	iDataWrapperBase.GetIntFromConfig(iSection, KFldTimeout(), iTimeOut);

	iErrorMargin=0;
	iDataWrapperBase.GetIntFromConfig(iSection, KFldErrorMargin(), iErrorMargin);

	iHasExitKeyCode=iDataWrapperBase.GetHexFromConfig(iSection, KFldExitKeyCode(), iExitKeyCode);

	iHasExitRectangle=iDataWrapperBase.GetRectFromConfig(iSection, KFldExitRectangle(), iExitRectangle);
	if ( iHasExitRectangle )
		{
		//	Draw rectangle
		TInt	height =Abs(iExitRectangle.iBr.iY-iExitRectangle.iTl.iY);
		TInt	width	=Abs(iExitRectangle.iBr.iX-iExitRectangle.iTl.iX);
		CDrawUtils::DrawSquareUtility(iExitRectangle.iTl, height, width, iColourValueWhite);
		}

	iEvent.Reset();

	TEventConfig	config;
	TInt			eventIndex=0;
	TBool			dataOk=ETrue;
	TBool			moreData=ETrue;
	while ( moreData )
		{
		tempStore.Format(KFldEventType, ++eventIndex);
		moreData=iDataWrapperBase.GetEnumFromConfig(iSection, tempStore, iEnumRawEventTable, config.iEventType);
		if ( moreData )
			{
			tempStore.Format(KFldEventOccurance, eventIndex);
			TInt	eventOccurance=EEventOccuranceOnce;
			iDataWrapperBase.GetEnumFromConfig(iSection, tempStore, iEnumEventOccuranceTable, eventOccurance);
			config.iEventOccurance=(TEventOccurance)eventOccurance;
			
			tempStore.Format(KFldDataVerify, eventIndex);
			config.iDataVerify=EFalse;
			iDataWrapperBase.GetBoolFromConfig(iSection, tempStore, config.iDataVerify);

			tempStore.Format(KFldDataDraw, eventIndex);
			config.iDataDraw=EFalse;
			iDataWrapperBase.GetBoolFromConfig(iSection, tempStore, config.iDataDraw);

			iEvent.AppendL(config);
			dataOk=ETrue;
			}
		}

	//	If -1 then we have an umlimited number of test(s) that completes with an exit event
	//	which can be an exit key code or a pen event in the exit rectangle
	iNumberOfTests=-1;
	iDataWrapperBase.GetIntFromConfig(iSection, KFldTests(), iNumberOfTests);

	if ( dataOk )
		{
		iTestIndex=0;
		dataOk=KickNext(aAsyncErrorIndex, aConsole);
		}

	return dataOk;
	}