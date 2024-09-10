void UNiagaraNodeInput::ReallocatePins()
{
	const UEdGraphSchema_Niagara* Schema = GetDefault<UEdGraphSchema_Niagara>();
	Modify();

	// Break any links to 'orphan' pins
	for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
	{
		UEdGraphPin* Pin = Pins[PinIndex];
		TArray<class UEdGraphPin*>& LinkedToRef = Pin->LinkedTo;
		for (int32 LinkIdx = 0; LinkIdx < LinkedToRef.Num(); LinkIdx++)
		{
			UEdGraphPin* OtherPin = LinkedToRef[LinkIdx];
			// If we are linked to a pin that its owner doesn't know about, break that link
			if (!OtherPin->GetOwningNode()->Pins.Contains(OtherPin))
			{
				Pin->LinkedTo.Remove(OtherPin);
			}
		}
	}

	// Store the old Input and Output pins
	TArray<UEdGraphPin*> OldInputPins;
	TArray<UEdGraphPin*> OldOutputPins;
	GetInputPins(OldInputPins);
	GetOutputPins(OldOutputPins);

	// Move the existing pins to a saved array
	TArray<UEdGraphPin*> OldPins(Pins);
	Pins.Empty();


	switch (Input.Type)
	{
	case ENiagaraDataType::Scalar:
	{
		CreatePin(EGPD_Output, Schema->PC_Float, TEXT(""), NULL, false, false, Input.Name.ToString());
	}
		break;
	case ENiagaraDataType::Vector:
	{
		CreatePin(EGPD_Output, Schema->PC_Vector, TEXT(""), NULL, false, false, Input.Name.ToString());
	}
		break;
	case ENiagaraDataType::Matrix:
	{
		CreatePin(EGPD_Output, Schema->PC_Matrix, TEXT(""), NULL, false, false, Input.Name.ToString());
	}
		break;
	case ENiagaraDataType::Curve:
	{
		CreatePin(EGPD_Output, Schema->PC_Curve, TEXT(""), NULL, false, false, Input.Name.ToString());
	}
		break;
	};

	// Get new Input and Output pins
	TArray<UEdGraphPin*> NewInputPins;
	TArray<UEdGraphPin*> NewOutputPins;
	GetInputPins(NewInputPins);
	GetOutputPins(NewOutputPins);

	for (int32 PinIndex = 0; PinIndex < OldInputPins.Num(); PinIndex++)
	{
		if (PinIndex < NewInputPins.Num())
		{
			NewInputPins[PinIndex]->CopyPersistentDataFromOldPin(*OldInputPins[PinIndex]);
		}
	}

	for (int32 PinIndex = 0; PinIndex < OldOutputPins.Num(); PinIndex++)
	{
		if (PinIndex < NewOutputPins.Num())
		{
			NewOutputPins[PinIndex]->CopyPersistentDataFromOldPin(*OldOutputPins[PinIndex]);
		}
	}

	OldInputPins.Empty();
	OldOutputPins.Empty();

	// Throw away the original pins
	for (int32 OldPinIndex = 0; OldPinIndex < OldPins.Num(); ++OldPinIndex)
	{
		UEdGraphPin* OldPin = OldPins[OldPinIndex];
		OldPin->Modify();
		OldPin->BreakAllPinLinks();

#if 0
		UEdGraphNode::ReturnPinToPool(OldPin);
#else
		OldPin->Rename(NULL, GetTransientPackage(), REN_None);
		OldPin->RemoveFromRoot();
		OldPin->MarkPendingKill();
#endif
	}
	OldPins.Empty();

	GetGraph()->NotifyGraphChanged();
}