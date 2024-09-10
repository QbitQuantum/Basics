UEdGraphNode* FEdGraphSchemaAction_K2NewNode::CreateNode(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, class UK2Node* NodeTemplate, bool bSelectNewNode/* = true*/)
{
	// Smart pointer that handles fixup after potential node reconstruction
	FWeakGraphPinPtr FromPinPtr = FromPin;

	// Duplicate template node to create new node
	UEdGraphNode* ResultNode = DuplicateObject<UK2Node>(NodeTemplate, ParentGraph);
	ResultNode->SetFlags(RF_Transactional);

	ParentGraph->AddNode(ResultNode, true, bSelectNewNode);

	ResultNode->CreateNewGuid();
	ResultNode->PostPlacedNewNode();
	ResultNode->AllocateDefaultPins();

	// For input pins, new node will generally overlap node being dragged off
	// Work out if we want to visually push away from connected node
	int32 XLocation = Location.X;
	if (FromPinPtr.IsValid() && FromPinPtr->Direction == EGPD_Input)
	{
		UEdGraphNode* PinNode = FromPinPtr->GetOwningNode();
		const float XDelta = FMath::Abs(PinNode->NodePosX - Location.X);

		if (XDelta < NodeDistance)
		{
			// Set location to edge of current node minus the max move distance
			// to force node to push off from connect node enough to give selection handle
			XLocation = PinNode->NodePosX - NodeDistance;
		}
	}
	ResultNode->NodePosX = XLocation;
	ResultNode->NodePosY = Location.Y;
	ResultNode->SnapToGrid(SNAP_GRID);

	// make sure to auto-wire after we position the new node (in case the 
	// auto-wire creates a conversion node to put between them)
	ResultNode->AutowireNewNode(FromPinPtr);

	// Update Analytics for the new nodes
	FBlueprintEditorUtils::AnalyticsTrackNewNode( ResultNode );
	// NOTE: At this point the node may have been reconstructed, depending on node type!

	return ResultNode;
}