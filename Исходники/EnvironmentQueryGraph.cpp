void UEnvironmentQueryGraph::RemoveOrphanedNodes()
{
	UEnvQuery* QueryAsset = CastChecked<UEnvQuery>(GetOuter());

	// Obtain a list of all nodes that should be in the asset
	TSet<UObject*> AllNodes;
	for (int32 Index = 0; Index < Nodes.Num(); ++Index)
	{
		UEnvironmentQueryGraphNode_Option* OptionNode = Cast<UEnvironmentQueryGraphNode_Option>(Nodes[Index]);
		if (OptionNode)
		{
			UEnvQueryOption* OptionInstance = Cast<UEnvQueryOption>(OptionNode->NodeInstance);
			if (OptionInstance)
			{
				AllNodes.Add(OptionInstance);
				if (OptionInstance->Generator)
				{
					AllNodes.Add(OptionInstance->Generator);
				}
			}

			for (int32 SubIdx = 0; SubIdx < OptionNode->Tests.Num(); SubIdx++)
			{
				if (OptionNode->Tests[SubIdx] && OptionNode->Tests[SubIdx]->NodeInstance)
				{
					AllNodes.Add(OptionNode->Tests[SubIdx]->NodeInstance);
				}
			}
		}
	}

	// Obtain a list of all nodes actually in the asset and discard unused nodes
	TArray<UObject*> AllInners;
	const bool bIncludeNestedObjects = false;
	GetObjectsWithOuter(QueryAsset, AllInners, bIncludeNestedObjects);
	for (auto InnerIt = AllInners.CreateConstIterator(); InnerIt; ++InnerIt)
	{
		UObject* Node = *InnerIt;
		const bool bEQSNode =
			Node->IsA(UEnvQueryGenerator::StaticClass()) ||
			Node->IsA(UEnvQueryTest::StaticClass()) ||
			Node->IsA(UEnvQueryOption::StaticClass());

		if (bEQSNode && !AllNodes.Contains(Node))
		{
			Node->SetFlags(RF_Transient);
			Node->Rename(NULL, GetTransientPackage(), REN_DontCreateRedirectors | REN_NonTransactional | REN_ForceNoResetLoaders);
		}
	}
}