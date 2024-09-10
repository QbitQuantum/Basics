//needs to remain int (instead of int32) since numbers are derived from TPL that uses int
void FLiveEditorManager::Dispatch( int Status, int Data1, int Data2, const struct FLiveEditorDeviceData &Data )
{
	int Type = (Status & 0xF0) >> 4;
	int Channel = (Status % 16) + 1;
	int ControlID = Data1;
	int ID = LISTENER_ID(Channel,ControlID);
	
	int Delta = 0;	//needs to remain int (instead of int32) since numbers are derived from TPL that uses int

	//
	// Dispatch the MIDI data to all Active Listners
	//
	TArray<ILiveEditListener*> Results;
	EventListeners.MultiFind( ID, Results );
	for ( TArray<ILiveEditListener*>::TIterator It(Results); It; It++ )
	{
		ILiveEditListener *Listener = *It;
		if ( !Listener || !Listener->Target.IsValid() )
		{
			continue;
		}

		switch ( Listener->Binding.ControlType )
		{
			case ELiveEditControllerType::NoteOnOff:
				Delta = 0;
				break;
			case ELiveEditControllerType::ControlChangeContinuous:
				if ( Data2 == Data.ContinuousIncrement )
					Delta = 1;
				else if ( Data2 == Data.ContinuousDecrement )
					Delta = -1;
				else
					Delta = 0;
				break;
			case ELiveEditControllerType::ControlChangeFixed:
				Delta = Data2 - Listener->Binding.LastValue;
				Listener->Binding.LastValue = Data2;
			default:
				break;
		}

		UObject *Target = Listener->Target.Get();
		FLiveEditorManager_Dispatch_Parms Parms;
		Parms.Delta = Delta;
		Parms.MidiValue = (int32)Data2;
		Parms.ControlType = Listener->Binding.ControlType;
		Target->ProcessEvent( Target->FindFunctionChecked( Listener->Name ), &Parms );
	}
}