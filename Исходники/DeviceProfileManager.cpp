UDeviceProfile& UDeviceProfileManager::CreateProfile( const FString& ProfileName, const FString& ProfileType, const FString& InSpecifyParentName )
{
	UDeviceProfile* DeviceProfile = FindObject<UDeviceProfile>( GetTransientPackage(), *ProfileName );
	if( DeviceProfile == NULL )
	{
		// Build Parent objects first. Important for setup
		FString ParentName = InSpecifyParentName;
		if (ParentName.Len() == 0)
		{
			const FString SectionName = FString::Printf(TEXT("%s %s"), *ProfileName, *UDeviceProfile::StaticClass()->GetName());
			GConfig->GetString(*SectionName, TEXT("BaseProfileName"), ParentName, GetDeviceProfileIniName());
		}

		UObject* ParentObject = nullptr;
		// Recursively build the parent tree
		if (ParentName.Len() > 0)
		{
			ParentObject = FindObject<UDeviceProfile>(GetTransientPackage(), *ParentName);
			if (ParentObject == nullptr)
			{
				ParentObject = &CreateProfile(ParentName, ProfileType);
			}
		}

		// Create the profile after it's parents have been created.
		DeviceProfile = NewObject<UDeviceProfile>(GetTransientPackage(), *ProfileName);
		DeviceProfile->DeviceType = DeviceProfile->DeviceType.Len() > 0 ? DeviceProfile->DeviceType : ProfileType;
		DeviceProfile->BaseProfileName = DeviceProfile->BaseProfileName.Len() > 0 ? DeviceProfile->BaseProfileName : ParentName;
		DeviceProfile->Parent = ParentObject;

		// Add the new profile to the accessible device profile list
		Profiles.Add( DeviceProfile );

		// Inform any listeners that the device list has changed
		ManagerUpdatedDelegate.Broadcast(); 
	}

	return *DeviceProfile;
}