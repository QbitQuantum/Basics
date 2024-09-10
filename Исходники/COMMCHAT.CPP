void CommsChat::OnReturnPressedPlayerchat(LPCTSTR text) 
{
	if (text[0])
	{
		CRListBox* rlistbox;
		CREdit* poo;

		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
//DeadCode RDH 14Dec99 		if (!strcmp(text,"megashootcheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=true;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"megashootcheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"invulnerablecheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"invulnerablecheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"liftcheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.liftcheat=true;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"liftcheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.liftcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else
		{
//DeadCode AMM 16Nov99 			rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);

	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
			rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
			rlistbox->AddString(text,1);
	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
			_DPlay.UISendDialogue((char*)text);
			_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(char*)text);

//DeadCode AMM 12Oct00 			if (!strcmp(text,"whateveron"))
//DeadCode AMM 12Oct00 				_DPlay.whatever=true;
//DeadCode AMM 12Oct00 			else if (!strcmp(text,"whateveroff"))
//DeadCode AMM 12Oct00 				_DPlay.whatever=false;
		}
		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
		poo=GETDLGITEM(IDC_PLAYERCHAT);
		poo->SetCaption("");										  //AMM 06/07/99

//DeadCode AMM 07Jul99 		poo->SetWindowText("");
	}
	
}