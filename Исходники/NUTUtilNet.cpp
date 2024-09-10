void NUTNet::MarkUnitTestWorldForCleanup(UWorld* CleanupWorld, bool bImmediate/*=false*/)
{
	UnitTestWorlds.Remove(CleanupWorld);
	PendingUnitWorldCleanup.Add(CleanupWorld);

	if (!bImmediate)
	{
		GEngine->DeferredCommands.AddUnique(TEXT("CleanupUnitTestWorlds"));
	}
	else
	{
		CleanupUnitTestWorlds();
	}
}