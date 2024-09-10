void FGameplayDebugger::WorldDestroyed(UWorld* InWorld)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	bool bIsServer = InWorld && InWorld->GetNetMode() < ENetMode::NM_Client; // (Only work on  server)
	if (!bIsServer)
	{
		return;
	}

	// remove global replicator from level
	AllReplicatorsPerWorlds.Remove(InWorld);
#endif //!(UE_BUILD_SHIPPING || UE_BUILD_TEST)
}