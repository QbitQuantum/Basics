void CEDAutoSelectFileDlg::EventHandler(CGUIEvent *event)
{
	if(!event)
		return;

	CGUIEventProgram *ep;
	CGUIButton *bt;
	CGUIEditWindow *eb;

	ep = nameServer->ResolveID(event->sender);

	//-----------------------------------------------------------------------------------
	eb = dynamic_cast<CGUIEditWindow*>(ep); //editboxy
	if(eb && event->eventID == EOk){
		if(eb == edA)
		{
			int ret=0;
			if(eb->Sync(1)==0)
			{
				ret = FS->IsValidFilename(AName);
			}
			if(!ret) {
				eb->BadInput();
				BadInput(event->sender);
			}
		}
		else if(eb == edAPath)
		{
			int ret=0;
			if(eb->Sync(1)==0)
			{
				FS->ChangeDir("$GAME$");
				if(APath[0]==0)
					ret=1;
				else
					ret = FS->ChangeDir(APath);
			}
			if(!ret)
			{
				eb->BadInput();
				BadInput(event->sender);
			}
		}
	}

	//-----------------------------------------------------------------------------------
	bt = dynamic_cast<CGUIButton*>(ep); //buttony
	if(bt)
	{
		if(event->eventID == EClicked)
		{
			if(bt == bASelector)	//vyber levelu - cesty + eventualne i jmena
			{ 
				CEDFileSelector *fs = dynamic_cast<CEDFileSelector*>(nameServer->ResolveID(fsASelector));
				if(fs)
				{
					fs->FocusMe(); //uz existuje FileSelector se skripty -> jen ho nafocusuju
				}
				else
				{
					float bx=0,by=0;
					desktop->GetDesktopPos(bASelector,bx,by); //zjistim souradnice tlacitka "..." v desktopu
					
					fs = new CEDFileSelector(bx,by,300,500);
					fs->title->SetText("Select A file (dir):");
					fs->title->SetIcon(new CGUIRectHost(0,0,styleSet->Get("BUT_Save_Up")->GetTexture(0)));
					fs->title->SetButtons(true,false,false);
					fs->compareFunction=&(CEDFileSelector::CompareLevelDIR);
					fs->SetCompareFunctionSubTree(&(CEDFileSelector::CompareLevelDIR));
					fs->filterExt = eEXTauto;
					fs->AcceptEvent(GetID(),ETree);
					desktop->AddBackElem(fs);
					fs->SetModal(1);

					fsASelector = fs->GetID();
				}
			}
		}
		else if(event->eventID == EStateChanged)
		{
			CGUIEditWindow *ew = GetObjFromID<CGUIEditWindow>(IDbadElem);
			if(ew==edA && bt==bASelector)
			{
				int cs = bt->GetState();
				
				if(cs == 2) 
					canceling = 1;//cancel je zamacklej
				else
				{
					if(IDbadElem){
						CGUIElement *el = dynamic_cast<CGUIElement*>(nameServer->ResolveID(IDbadElem));
						if(el)
							SetFocusEl(el,0);
						IDbadElem = 0;
					}
					canceling = 0;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------
	if(event->eventID == ETree)
	{
		if(event->sender == fsASelector && event->pInt2 == 0) //obsluha vyberu jmena Levelu / cesty k Levelu
		{
			CEDFileSelector *fs = dynamic_cast<CEDFileSelector*>(nameServer->ResolveID(fsASelector));
			if(fs)
			{
				char *dir=0,*file=0,*root=0;
				int sf;

				sf = fs->GetSelectedFileRelativ(event->pID,&root,&dir,&file);
				assert(sf!=-1);

				_snprintf(APath,STRINGLEN,"%s",dir);

				int ext;
				KerServices.ConvertFileNameToShort(file,ext,0,0);


				if(sf==1)	// jde o adresar
				{
					if(dir[0]==0)
						_snprintf(APath,STRINGLEN,"%s",file);
					else
						_snprintf(APath,STRINGLEN,"%s\\%s",dir,file);
				}

				if(ext==eEXTauto)
				{
					_snprintf(AName,STRINGLEN,"%s",file);
					edA->Sync(false);

					fs->CloseWindow();
					FocusMe();
					SetFocusEl(FindNextTABElement(edAPath->GetTabOrder(),false),0);					
				}
				

				edAPath->Sync(false);
				IDbadElem = 0;

				SAFE_DELETE_ARRAY(root);
				SAFE_DELETE_ARRAY(dir);
				SAFE_DELETE_ARRAY(file);
			}		
		}
	}
	//------------------------------------------------------------------------------------

	CGUIDlgOkCancel::EventHandler(event); //zavolam eventhander predka
}