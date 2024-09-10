void AddRead::Execute()
{
	this->ReadActionParameters();

	

	while (1)
	{
		Read *pRead = new Read(Position);

		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("Enter String: ");

		Input *pIn = pManager->GetInput();
		bool y = pRead->setData((pIn->GetString(pOut)));

		if (y)
		{
			pManager->AddStatement(pRead);
			pOut->ClearStatusBar();
			break;
		}
		else
		{
			pOut->MsgBox("Invalid text !! Click ok to Re-enter data", "Error", true);
		}
	}
}