void FProfilerClientManager::Track( const TArray<ISessionInstanceInfoPtr>& Instances )
{
#if STATS
	if (MessageEndpoint.IsValid() && ActiveSessionId.IsValid())
	{
		TArray<FGuid> ActiveInstances;
		Connections.GenerateKeyArray(ActiveInstances);

		for (int32 i = 0; i < Instances.Num(); ++i)
		{
			if (Connections.Find(Instances[i]->GetInstanceId()) == nullptr)
			{
				Track(Instances[i]->GetInstanceId());
			}
			else
			{
				ActiveInstances.Remove(Instances[i]->GetInstanceId());
			}
		}

		for (int32 i = 0; i < ActiveInstances.Num(); ++i)
		{
			Untrack(ActiveInstances[i]);
		}
	}
#endif
}