void EditConnector::Execute()
{
	Output *pOut = pManager->GetOutput();

	if (pManager->ZM)
	{
		pOut->MsgBox("You can't Edit Connectors in zoom mode !!", "Error", true);
		return;
	}

	if (pManager->ConnSelectedCount > 0)
	{
		int toBeEdited = pManager->ConnSelectedCount;

		Action* DeleteConnAct = new Delete(pManager);
		DeleteConnAct->Execute();

		for (int i = 0; i < pManager->StatCount; i++)
		{
			pManager->StatList[i]->SetSelected(false);
		}
		pManager->EmptySelectedList();

		pManager->UpdateInterface();

		pOut->ClearStatusBar();

		for (int i = 0; i < toBeEdited; ++i)
		{
			pManager->UpdateInterface();
			Point SrcP, DstP;
			Statement *SrcS, *DstS;
			while (1)
			{
				pOut->PrintMessage("Select new source for Selected connector " + to_string(i + 1) + ": ");
				pManager->pIn->GetPointClicked(SrcP);
				SrcS = pManager->GetStatement(SrcP);
				if (SrcS)
				{
					SrcS->SetSelected(true);
					pManager->AddSelected(SrcS);
				}
				pManager->UpdateInterface();
				pOut->PrintMessage("Select new destination for Selected connector " + to_string(i + 1) + ": ");
				pManager->pIn->GetPointClicked(DstP);
				DstS = pManager->GetStatement(DstP);
				if (DstS)
				{
					DstS->SetSelected(true);
					pManager->AddSelected(DstS);
				}
				pManager->UpdateInterface();
				if (SrcS && DstS && SrcS != DstS && !SrcS->hasConn() && !dynamic_cast<End*>(SrcS) && !dynamic_cast<Start*>(DstS))
				{
					break;
				}
				else
				{
					if (SrcS)
					{
						SrcS->SetSelected(false);
						pManager->RemoveSelected(SrcS);
					}
					if (DstS)
					{
						DstS->SetSelected(false);
						pManager->RemoveSelected(DstS);
					}
					pManager->EmptySelectedList();
					pManager->UpdateInterface();
					pOut->MsgBox("Invalid source or destination !! Click ok to Re-select", "Error", true);
				}
			}

			Action* AddConnAct = new AddConnector(pManager);
			AddConnAct->Execute();
			delete AddConnAct;
		}

		DeleteConnAct = new Delete(pManager);
		DeleteConnAct->Execute();
		delete DeleteConnAct;

		pOut->PrintMessage("Edited Successfully !");
	}
	else
		pOut->MsgBox("You Should select the connector(s) first then click on the action", "Info", false);
}