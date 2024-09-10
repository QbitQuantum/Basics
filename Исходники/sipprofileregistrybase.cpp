// -----------------------------------------------------------------------------
// CSIPProfileRegistryBase::StoreProfileL
// -----------------------------------------------------------------------------
//
void CSIPProfileRegistryBase::StoreArrayL(
	RPointerArray<CSIPConcreteProfile>& aProfiles,
	RPointerArray<CSIPProfile>& aRetProfiles)
	{
	int count = aProfiles.Count();

	for (TInt i = 0; i < count; i++)
		{
		TUint profileId = (aProfiles[0])->Id();
		TInt index = ProfileIndex(profileId);
		
		CSIPProfileCleanupItem* cleanupItem = new (ELeave) CSIPProfileCleanupItem(iITC);
		CleanupStack::PushL(cleanupItem);

		if(index == KErrNotFound) 
			{
			CleanupStack::PushL(TCleanupItem(CrashRevert, cleanupItem));

			cleanupItem->iProfileId = (aProfiles[0])->Id();
			cleanupItem->iConcreteProfile = aProfiles[0];
			aProfiles.Remove(0);

			StoreProfileL(cleanupItem);
			User::LeaveIfError(aRetProfiles.Append(cleanupItem->iManagedProfile));
			}
		else
			{
			CleanupStack::PushL(TCleanupItem(LocalCrashRevert, cleanupItem));

			CSIPProfileItem* item = ProfileItemL(profileId);
			CSIPProfile* managed = NewInstanceL();
			cleanupItem->iManagedProfile = managed;
			managed->SetConcreteProfile(&(item->ConcreteProfile()));
			managed->SetEnabled(item->IsEnabled());
			item->IncrementReferenceCountL(*managed);
			User::LeaveIfError(aRetProfiles.Append(managed));
			CSIPConcreteProfile* profileNotUsed = aProfiles[0];
			aProfiles.Remove(0);
			delete profileNotUsed;
			}
		}
	aProfiles.Reset();

	for (TInt j = 0; j < count; j++)
		{
		CleanupStack::Pop(); //TCleanupItem
		CleanupStack::PopAndDestroy(); //cleanupItem
		}
	}