UEdGraphPin* UEdGraphNode::AllocatePinFromPool(UEdGraphNode* OuterNode)
{
	if (PooledPins.Num() > 0)
	{
		UEdGraphPin* Result = PooledPins.Pop();
		Result->Rename(NULL, OuterNode);
		return Result;
	}
	else
	{
		UEdGraphPin* Result = NewObject<UEdGraphPin>(OuterNode);
		return Result;
	}
}