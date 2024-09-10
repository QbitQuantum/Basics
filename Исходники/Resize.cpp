void Resize::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	Stat=pManager->GetSelectedStatement();
	if(Stat==NULL)
		{
			pOut->PrintMessage("no selected Statement");
			return;
		}
	
	while(1)
	{
	pOut->PrintMessage("pleaze enter '+' to zoom in or enter '-' to zoom out");
	type=pIn->GetString(pOut);
	if(type=="+"||type=="-")
		break;
	}
	pOut->ClearStatusBar();		
}