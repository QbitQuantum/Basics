TSharedPtr<FEdMode> FEditorModeRegistry::CreateMode(FEditorModeID ModeID, FEditorModeTools& Owner)
{
	const TSharedRef<IEditorModeFactory>* ModeFactory = ModeFactories.Find(ModeID);
	if (ModeFactory)
	{
		TSharedRef<FEdMode> Instance = (*ModeFactory)->CreateMode();

		// Assign the mode info from the factory before we initialize
		Instance->Info = (*ModeFactory)->GetModeInfo();
		Instance->Owner = &Owner;

		// This binding ensures the mode is destroyed if the type is unregistered
		OnModeUnregistered().AddSP(Instance, &FEdMode::OnModeUnregistered);

		Instance->Initialize();

		return Instance;
	}

	return nullptr;
}