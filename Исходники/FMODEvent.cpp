/** Get tags to show in content view */
void UFMODEvent::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
	Super::GetAssetRegistryTags(OutTags);
	FMOD::Studio::EventDescription* EventDesc = IFMODStudioModule::Get().GetEventDescription(this, EFMODSystemContext::Auditioning);
	
	bool bOneshot = false;
	bool bStream = false;
	bool b3D = false;
	if (EventDesc)
	{
		EventDesc->isOneshot(&bOneshot);
		EventDesc->isStream(&bStream);
		EventDesc->is3D(&b3D);
	}

	OutTags.Add(UObject::FAssetRegistryTag("Oneshot", bOneshot ? TEXT("True") : TEXT("False"), UObject::FAssetRegistryTag::TT_Alphabetical));
	OutTags.Add(UObject::FAssetRegistryTag("Streaming", bStream ? TEXT("True") : TEXT("False"), UObject::FAssetRegistryTag::TT_Alphabetical));
	OutTags.Add(UObject::FAssetRegistryTag("3D", b3D ? TEXT("True") : TEXT("False"), UObject::FAssetRegistryTag::TT_Alphabetical));
}