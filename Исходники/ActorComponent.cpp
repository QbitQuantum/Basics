void UActorComponent::ConsolidatedPostEditChange(const FPropertyChangedEvent& PropertyChangedEvent)
{
	FComponentReregisterContext* ReregisterContext = EditReregisterContexts.FindRef(this);
	if(ReregisterContext)
	{
		delete ReregisterContext;
		EditReregisterContexts.Remove(this);

		AActor* MyOwner = GetOwner();
		if ( MyOwner && !MyOwner->IsTemplate() && PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive )
		{
			MyOwner->RerunConstructionScripts();
		}
	}

	// The component or its outer could be pending kill when calling PostEditChange when applying a transaction.
	// Don't do do a full recreate in this situation, and instead simply detach.
	if( IsPendingKill() )
	{
		// @todo UE4 james should this call UnregisterComponent instead to remove itself from the RegisteredComponents array on the owner?
		ExecuteUnregisterEvents();
		World = NULL;
	}
}