const bool FHierarchicalLODUtilities::RemoveActorFromCluster(AActor* InActor)
{
	checkf(InActor != nullptr, TEXT("Invalid InActor"));
	
	bool bSucces = false;

	ALODActor* ParentActor = FHierarchicalLODUtilities::GetParentLODActor(InActor);
	if (ParentActor != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("UndoAction_RemoveActorFromCluster", "Remove Actor From Cluster"));
		ParentActor->Modify();
		InActor->Modify();

		bSucces = ParentActor->RemoveSubActor(InActor);

		if (!ParentActor->HasValidSubActors())
		{
			DestroyCluster(ParentActor);
		}
	}
	
	return bSucces;
}