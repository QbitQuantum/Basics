/**
* Delete all Instances in the calendar file 
*/
void CTestCalInterimApiModifier::DeleteInstancesL()
	{
 	CCalInstanceView* instanceView = CCalInstanceView::NewL(GetSession(), *this);
	CleanupStack::PushL(instanceView);
	CActiveScheduler::Start();
	TInt err;
	RPointerArray<CCalInstance>	instanceArray;
	TCalTime	calStartDateTime;
	calStartDateTime.SetTimeLocalL(TCalTime::MinTime());
	TCalTime	calEndDateTime;
	calEndDateTime.SetTimeLocalL(TCalTime::MaxTime());
	CalCommon::TCalTimeRange	calTimeRange(calStartDateTime, calEndDateTime);

	CleanupStack::PushL(TCleanupItem(ResetAndDestroyInstanceArray, &instanceArray));
	instanceView->FindInstanceL(instanceArray, CalCommon::EIncludeAll, calTimeRange);
	if(instanceArray.Count() != 0)
		{
		TRAP(err, instanceView->DeleteL(instanceArray[0], CalCommon::EThisAndAll));
		instanceArray.Remove(0);
		if(err != KErrNone)
			{
			iTestStep->ERR_PRINTF2(KErrDeleteOperation,err);
			iTestStep->SetTestStepResult(EFail);
			}
		}
	else
		{
		iTestStep->WARN_PRINTF1(KWarnInstancesNotFound);
		}
		
	CleanupStack::PopAndDestroy();// instanceArray
	CleanupStack::PopAndDestroy(); // instanceView
	}