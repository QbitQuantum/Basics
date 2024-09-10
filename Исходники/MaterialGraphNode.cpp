void UMaterialGraphNode::RecreateAndLinkNode()
{
	// Throw away the original pins
	for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
	{
		UEdGraphPin* Pin = Pins[PinIndex];
		Pin->Modify();
		Pin->BreakAllPinLinks();

#if 0
		UEdGraphNode::ReturnPinToPool(Pin);
#else
		Pin->Rename(NULL, GetTransientPackage(), REN_None);
		Pin->RemoveFromRoot();
		Pin->MarkPendingKill();
#endif
	}
	Pins.Empty();

	AllocateDefaultPins();

	CastChecked<UMaterialGraph>(GetGraph())->LinkGraphNodesFromMaterial();
}