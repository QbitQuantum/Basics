void CLoadState::Begin()
{
	// Load References
	SingletonPointer<CMainState> MainState;
	SingletonPointer<CMainMenuState> MenuState;

	Canvas = GUIManager->GetCanvas();
	
	// Init Canvas
	Canvas->SetBackgroundColor(Gwen::Color(32, 48, 48));
	Canvas->SetDrawBackground(true);

	// Top Label
	Gwen::Controls::Label * BigLabel = new Gwen::Controls::Label(Canvas);
	BigLabel->SetFont(GUIManager->GetLargeFont());
	BigLabel->SetText(L"Loading...");
	BigLabel->SetBounds(10, 10, 1590, 300);
	BigLabel->SetTextColor(Gwen::Color(255, 255, 255, 84));

	GUIManager->Draw(0, true);
	Context->Window->SwapBuffers();
	
	AddLabel(L"Initializing System...");
	CGUIEventManager * Forwarder = new CGUIEventManager(GUIManager->GetCanvas(), Context->Window);
	
	AddLabel(L"Loading Scene Shaders...");
	LoadShaders();
	
	AddLabel(L"Loading Scene Objects...");
	LoadScene();
	
	AddLabel(L"Menu is Starting...");

	if (GetConfirmation)
	{
		Gwen::Controls::Button * Button = new Gwen::Controls::Button(GUIManager->GetCanvas());
		Button->SetBounds(250, 650, 250, 35);
		Button->SetText(L"Continue");
		Button->onPress.Add(& Handler, & CLoadStateEventHandler::OnFinish);
	}
	else
	{
		OnFinish();
	}
}