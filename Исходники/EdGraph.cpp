UEdGraphNode* UEdGraph::CreateNode( TSubclassOf<UEdGraphNode> NewNodeClass, bool bSelectNewNode/* = true*/ )
{
	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(this, NewNodeClass, NAME_None, RF_Transactional);

	if (HasAnyFlags(RF_Transient))
	{
		NewNode->SetFlags(RF_Transient);
	}

	AddNode(NewNode, false, bSelectNewNode );
	return NewNode;
}