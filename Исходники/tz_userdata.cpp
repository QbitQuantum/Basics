/**
Delete user-defined time zones.

@SYMTestCaseID 	PIM-APPSERV-TZS-CO-0003

@SYMTestCaseDesc
	The purpose of this test is to verify that user-defined time zones can be
	deleted.

@SYMTestActions  
	1.	Get all existing user-defined time zones.
	2.	Delete the user-defined time zone as the last element in the array one
		by one.
	3.	Try to read the user-defined time zone deleted in action 2.

@SYMTestExpectedResults
	The user-defined time zone does not exist.

@SYMTestType
	CT

@SYMTestPriority
	1
*/
void CTzUserDataTest::TestDeleteUserDefinedTzL()	
	{
	test.Next(_L("@SYMTestCaseID  PIM-APPSERV-TZS-CO-0003"));
	RPointerArray<CTzId> ids;
	CleanupStack::PushL(TCleanupItem(ResetAndDestroyTzIdArray, &ids));

	for(TInt ii=iTzIds.Count()-1; ii>=0; --ii)
		{
		iUserData->GetTzIdsL(ids);
		
		// The array obtained should be same as expected who elements is deleted
		// one by one in each loop.
		CompareArray(ids,iTzIds);
		ids.ResetAndDestroy();
		
		// Delete the user-defined time zone as the last element in the array.
		iUserData->DeleteL(*(iTzIds[ii]));
		
		// The rule and names of the last element in the array should not be
		// found since it has been deleted.
		TRAPD(err, iUserData->ReadRulesL(*(iTzIds[ii])));
		test(err == KErrNotFound);
		TRAP(err, iUserData->ReadNamesL(*(iTzIds[ii])));
		test(err == KErrNotFound);

		delete iTzIds[ii];
		iTzIds.Remove(ii);
		}

	CleanupStack::PopAndDestroy(&ids);
	}