void AddSOAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
		pManager->UnSelect();
	

	while(1)
	{pOut->PrintMessage("Single Operator Assignment Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	
	Point P[4];
	P[0].x=Position.x-UI.ASSGN_WDTH/2;            P[1].x=Position.x-UI.ASSGN_WDTH/2;             P[2].x=Position.x+UI.ASSGN_WDTH/2;               P[3].x=Position.x+UI.ASSGN_WDTH/2;
	P[0].y=Position.y;     P[1].y=Position.y+UI.ASSGN_HI;                                       P[2].y=P[1].y;        P[3].y=P[0].y;
	if(P[0].x>UI.MnItWdth&&P[0].y>UI.TlBrWdth&&P[1].y<UI.height-UI.StBrWdth)
		if(!pManager->onObject(P[0])&&!pManager->onObject(P[1])&&!pManager->onObject(P[2])&&!pManager->onObject(P[3]))
		break;
	if(pManager->onBars(Position)||pManager->onObject(Position))
	{pOut->ClearStatusBar();	return;}
			
	
	}
	pOut->ClearStatusBar();
	
}