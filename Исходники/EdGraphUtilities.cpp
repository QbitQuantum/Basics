// Reconcile other pin links:
//   - Links between nodes within the copied set are fine
//   - Links to nodes that were not copied need to be fixed up if the copy-paste was in the same graph or broken completely
// Call PostPasteNode on each node
void FEdGraphUtilities::PostProcessPastedNodes(TSet<UEdGraphNode*>& SpawnedNodes)
{
	// Run thru and fix up the node's pin links; they may point to invalid pins if the paste was to another graph
	for (TSet<UEdGraphNode*>::TIterator It(SpawnedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		UEdGraph* CurrentGraph = Node->GetGraph();

		for (int32 PinIndex = 0; PinIndex < Node->Pins.Num(); ++PinIndex)
		{
			UEdGraphPin* ThisPin = Node->Pins[PinIndex];

			for (int32 LinkIndex = 0; LinkIndex < ThisPin->LinkedTo.Num(); )
			{
				UEdGraphPin* OtherPin = ThisPin->LinkedTo[LinkIndex];

				if (OtherPin == NULL)
				{
					// Totally bogus link
					ThisPin->LinkedTo.RemoveAtSwap(LinkIndex);
				}
				else if (!SpawnedNodes.Contains(OtherPin->GetOwningNode()))
				{
					// It's a link across the selection set, so it should be broken
					OtherPin->LinkedTo.RemoveSwap(ThisPin);
					ThisPin->LinkedTo.RemoveAtSwap(LinkIndex);
				}
				else if (!OtherPin->LinkedTo.Contains(ThisPin))
				{
					// The link needs to be reciprocal
					check(OtherPin->GetOwningNode()->GetGraph() == CurrentGraph);
					OtherPin->LinkedTo.Add(ThisPin);
					++LinkIndex;
				}
				else
				{
					// Everything seems fine but sanity check the graph
					check(OtherPin->GetOwningNode()->GetGraph() == CurrentGraph);
					++LinkIndex;
				}
			}
		}
	}

	// Give every node a chance to deep copy associated resources, etc...
	for (TSet<UEdGraphNode*>::TIterator It(SpawnedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;

		Node->PostPasteNode();
		Node->ReconstructNode();

		// Ensure we have RF_Transactional set on all pasted nodes, as its not copied in the T3D format
		Node->SetFlags(RF_Transactional);
	}
}