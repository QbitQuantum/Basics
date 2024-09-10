UEdGraphNode* FEdGraphSchemaAction_NewStateNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode/* = true*/)
{
    UEdGraphNode* ResultNode = NULL;

    // If there is a template, we actually use it
    if (NodeTemplate != NULL)
    {
        const FScopedTransaction Transaction( NSLOCTEXT("UnrealEd", "K2_AddNode", "Add Node") );
        ParentGraph->Modify();
        if (FromPin)
        {
            FromPin->Modify();
        }

        // set outer to be the graph so it doesn't go away
        NodeTemplate->Rename(NULL, ParentGraph);
        ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

        NodeTemplate->CreateNewGuid();
        NodeTemplate->PostPlacedNewNode();
        NodeTemplate->AllocateDefaultPins();
        NodeTemplate->AutowireNewNode(FromPin);

        NodeTemplate->NodePosX = Location.X;
        NodeTemplate->NodePosY = Location.Y;
        //@TODO: ANIM: SNAP_GRID isn't centralized or exposed - NodeTemplate->SnapToGrid(SNAP_GRID);

        ResultNode = NodeTemplate;

        ResultNode->SetFlags(RF_Transactional);

        UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ParentGraph);
        FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
    }

    return ResultNode;
}