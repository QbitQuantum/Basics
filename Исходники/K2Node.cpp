void UK2Node::ReconstructNode()
{
	Modify();

	UBlueprint* Blueprint = GetBlueprint();

	// Break any links to 'orphan' pins
	for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
	{
		UEdGraphPin* Pin = Pins[PinIndex];
		TArray<class UEdGraphPin*> LinkedToCopy = Pin->LinkedTo;
		for (int32 LinkIdx = 0; LinkIdx < LinkedToCopy.Num(); LinkIdx++)
		{
			UEdGraphPin* OtherPin = LinkedToCopy[LinkIdx];
			// If we are linked to a pin that its owner doesn't know about, break that link
			if ((OtherPin == NULL) || !OtherPin->GetOwningNodeUnchecked() || !OtherPin->GetOwningNode()->Pins.Contains(OtherPin))
			{
				Pin->LinkedTo.Remove(OtherPin);
			}
		}
	}

	// Move the existing pins to a saved array
	TArray<UEdGraphPin*> OldPins(Pins);
	Pins.Empty();

	// Recreate the new pins
	ReallocatePinsDuringReconstruction(OldPins);

	bool bDestroyOldPins = true;

	if (Pins.Num() == 0)
	{
		//keep old pins on callfunction so that graph doesn't get broken up just because function is missing
		if (IsA(UK2Node_CallFunction::StaticClass()) || IsA(UK2Node_MacroInstance::StaticClass()))
		{
			Pins = OldPins;
			bDestroyOldPins = false;
		}
	}
	else
	{
		// Rewire any connection to pins that are matched by name (O(N^2) right now)
		//@TODO: Can do moderately smart things here if only one pin changes name by looking at it's relative position, etc...,
		// rather than just failing to map it and breaking the links
		for (int32 OldPinIndex = 0; OldPinIndex < OldPins.Num(); ++OldPinIndex)
		{
			UEdGraphPin* OldPin = OldPins[OldPinIndex];

			for (int32 NewPinIndex = 0; NewPinIndex < Pins.Num(); ++NewPinIndex)
			{
				UEdGraphPin* NewPin = Pins[NewPinIndex];

				const ERedirectType RedirectType = DoPinsMatchForReconstruction(NewPin, NewPinIndex, OldPin, OldPinIndex);
				if (RedirectType != ERedirectType_None)
				{
					ReconstructSinglePin(NewPin, OldPin, RedirectType);
					break;
				}
			}
		}
	}


	if (bDestroyOldPins)
	{
		// Throw away the original pins
		for (int32 OldPinIndex = 0; OldPinIndex < OldPins.Num(); ++OldPinIndex)
		{
			UEdGraphPin* OldPin = OldPins[OldPinIndex];
			OldPin->Modify();
			OldPin->BreakAllPinLinks();
			
			// just in case this pin was set to watch (don't want to save PinWatches with dead pins)
			Blueprint->PinWatches.Remove(OldPin);
#if 0
			UEdGraphNode::ReturnPinToPool(OldPin);
#else
			OldPin->Rename(NULL, GetTransientPackage(), (Blueprint->bIsRegeneratingOnLoad ? REN_ForceNoResetLoaders : REN_None));
			OldPin->RemoveFromRoot();
			OldPin->MarkPendingKill();
#endif
		}
	}

	// Let subclasses do any additional work
	PostReconstructNode();

	GetGraph()->NotifyGraphChanged();
}