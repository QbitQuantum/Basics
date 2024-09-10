bool UGameInstance::HandleOpenCommand(const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld)
{
	check(WorldContext && WorldContext->World() == InWorld);

	UEngine* const Engine = GetEngine();

	FURL TestURL(&WorldContext->LastURL, Cmd, TRAVEL_Absolute);
	if (TestURL.IsLocalInternal())
	{
		// make sure the file exists if we are opening a local file
		if (!Engine->MakeSureMapNameIsValid(TestURL.Map))
		{
			Ar.Logf(TEXT("ERROR: The map '%s' does not exist."), *TestURL.Map);
			return true;
		}
	}

	Engine->SetClientTravel(InWorld, Cmd, TRAVEL_Absolute);
	return true;
}