void UK2Node_CustomEvent::RenameCustomEventCloseToName(int32 StartIndex)
{
	bool bFoundName = false;
	const FString& BaseName = CustomFunctionName.ToString();

	for (int32 NameIndex = StartIndex; !bFoundName; ++NameIndex)
	{
		const FString NewName = FString::Printf(TEXT("%s_%d"), *BaseName, NameIndex);
		if (Rename(*NewName, GetOuter(), REN_Test))
		{
			UBlueprint* Blueprint = GetBlueprint();
			CustomFunctionName = FName(NewName.GetCharArray().GetData());
			Rename(*NewName, GetOuter(), (Blueprint->bIsRegeneratingOnLoad ? REN_ForceNoResetLoaders : 0) | REN_DontCreateRedirectors);
			bFoundName = true;
		}
	}
}