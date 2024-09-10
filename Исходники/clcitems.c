void SaveStateAndRebuildList(HWND hwnd,struct ClcData *dat)
{
	NMCLISTCONTROL nm;
	int i,j;
	struct SavedGroupState_t *savedGroup=NULL;
	int savedGroupCount=0,savedGroupAlloced=0;
	struct SavedContactState_t *savedContact=NULL;
	int savedContactCount=0,savedContactAlloced=0;
	struct SavedInfoState_t *savedInfo=NULL;
	int savedInfoCount=0,savedInfoAlloced=0;
	struct ClcGroup *group;
	struct ClcContact *contact;

	int tick=GetTickCount();
	int allocstep=1024;

  TRACE("SaveStateAndRebuildList\n");

	HideInfoTip(hwnd,dat);
	KillTimer(hwnd,TIMERID_INFOTIP);
  KillTimer(hwnd,TIMERID_REBUILDAFTER);
	KillTimer(hwnd,TIMERID_RENAME);
	EndRename(hwnd,dat,1);

	group=&dat->list;
	group->scanIndex=0;
	for(;;) {
		if(group->scanIndex==group->contactCount) {
			group=group->parent;
			if(group==NULL) break;
		}
		else if(group->contact[group->scanIndex].type==CLCIT_GROUP) {
			group=group->contact[group->scanIndex].group;
			group->scanIndex=0;
			if(++savedGroupCount>savedGroupAlloced) {
				savedGroupAlloced+=allocstep;
				savedGroup=(struct SavedGroupState_t*)mir_realloc(savedGroup,sizeof(struct SavedGroupState_t)*savedGroupAlloced);
			}
			savedGroup[savedGroupCount-1].groupId=group->groupId;
			savedGroup[savedGroupCount-1].expanded=group->expanded;
			continue;
		}
		else if(group->contact[group->scanIndex].type==CLCIT_CONTACT) {			
			if(++savedContactCount>savedContactAlloced) {
				savedContactAlloced+=allocstep;
				savedContact=(struct SavedContactState_t*)mir_realloc(savedContact,sizeof(struct SavedContactState_t)*savedContactAlloced);
			}
			savedContact[savedContactCount-1].hContact=group->contact[group->scanIndex].hContact;
			CopyMemory(savedContact[savedContactCount-1].iExtraImage,group->contact[group->scanIndex].iExtraImage,sizeof(group->contact[group->scanIndex].iExtraImage));
			savedContact[savedContactCount-1].checked=group->contact[group->scanIndex].flags&CONTACTF_CHECKED;
			if (group->contact[group->scanIndex].SubAllocated>0)
			{
				int l;
				for (l=0; l<group->contact[group->scanIndex].SubAllocated; l++)
				{
					if(++savedContactCount>savedContactAlloced) {
						savedContactAlloced+=allocstep;
						savedContact=(struct SavedContactState_t*)mir_realloc(savedContact,sizeof(struct SavedContactState_t)*savedContactAlloced);
					}
					savedContact[savedContactCount-1].hContact=group->contact[group->scanIndex].subcontacts[l].hContact;
					CopyMemory(savedContact[savedContactCount-1].iExtraImage ,group->contact[group->scanIndex].subcontacts[l].iExtraImage,sizeof(group->contact[group->scanIndex].iExtraImage));
					savedContact[savedContactCount-1].checked=group->contact[group->scanIndex].subcontacts[l].flags&CONTACTF_CHECKED;
                    

				}
			}

		}
		else if(group->contact[group->scanIndex].type==CLCIT_INFO) {
			if(++savedInfoCount>savedInfoAlloced) {
				savedInfoAlloced+=allocstep;
				savedInfo=(struct SavedInfoState_t*)mir_realloc(savedInfo,sizeof(struct SavedInfoState_t)*savedInfoAlloced);
			}
			if(group->parent==NULL) savedInfo[savedInfoCount-1].parentId=-1;
			else savedInfo[savedInfoCount-1].parentId=group->groupId;
			savedInfo[savedInfoCount-1].contact=group->contact[group->scanIndex];
			{
				TCHAR * name=NULL;
				if(savedInfo[savedInfoCount-1].contact.szText)
				{
					name=mir_strdupT(savedInfo[savedInfoCount-1].contact.szText);
					mir_free(savedInfo[savedInfoCount-1].contact.szText);
					savedInfo[savedInfoCount-1].contact.szText=name;
					group->contact[group->scanIndex].szText=NULL;
				}
			}
		}
		group->scanIndex++;
	}

	FreeGroup(&dat->list);
	RebuildEntireList(hwnd,dat);

	group=&dat->list;
	group->scanIndex=0;
	for(;;) {
		if(group->scanIndex==group->contactCount) {
			group=group->parent;
			if(group==NULL) break;
		}
		else if(group->contact[group->scanIndex].type==CLCIT_GROUP) {
			group=group->contact[group->scanIndex].group;
			group->scanIndex=0;
			for(i=0;i<savedGroupCount;i++)
				if(savedGroup[i].groupId==group->groupId) {
					group->expanded=savedGroup[i].expanded;
					break;
				}
			continue;
		}
		else if(group->contact[group->scanIndex].type==CLCIT_CONTACT) {
			for(i=0;i<savedContactCount;i++)
				if(savedContact[i].hContact==group->contact[group->scanIndex].hContact) {
					CopyMemory(group->contact[group->scanIndex].iExtraImage,savedContact[i].iExtraImage,sizeof(group->contact[group->scanIndex].iExtraImage));
					if(savedContact[i].checked) group->contact[group->scanIndex].flags|=CONTACTF_CHECKED;
					break;	
				}
			if (group->contact[group->scanIndex].SubAllocated>0)
			{
				int l;
				for (l=0; l<group->contact[group->scanIndex].SubAllocated; l++)
					for(i=0;i<savedContactCount;i++)
						if(savedContact[i].hContact==group->contact[group->scanIndex].subcontacts[l].hContact) {

							CopyMemory(group->contact[group->scanIndex].subcontacts[l].iExtraImage,savedContact[i].iExtraImage,sizeof(group->contact[group->scanIndex].iExtraImage));
							if(savedContact[i].checked) group->contact[group->scanIndex].subcontacts[l].flags|=CONTACTF_CHECKED;
                            group->contact[group->scanIndex].subcontacts[l].subcontacts=&(group->contact[group->scanIndex]);
							break;	
						}	
			}
		}
		group->scanIndex++;
	}
	if(savedGroup) mir_free(savedGroup);
	if(savedContact) mir_free(savedContact);
	for(i=0;i<savedInfoCount;i++) {
		if(savedInfo[i].parentId==-1) group=&dat->list;
		else {
			if(!FindItem(hwnd,dat,(HANDLE)(savedInfo[i].parentId|HCONTACT_ISGROUP),&contact,NULL,NULL,TRUE)) continue;
			group=contact->group;
		}
		j=AddInfoItemToGroup(group,savedInfo[i].contact.flags,NULL);
		group->contact[j]=savedInfo[i].contact;
	}
	if(savedInfo) mir_free(savedInfo);
	RecalculateGroupCheckboxes(hwnd,dat);

	RecalcScrollBar(hwnd,dat);
	nm.hdr.code=CLN_LISTREBUILT;
	nm.hdr.hwndFrom=hwnd;
	nm.hdr.idFrom=GetDlgCtrlID(hwnd);


	//srand(GetTickCount());
	
	tick=GetTickCount()-tick;
#ifdef _DEBUG
	{
	char buf[255];
	sprintf(buf,"SaveStateAndRebuildList %d \r\n",tick);
	TRACE(buf);
	}	
#endif

	ClearRowByIndexCache();
       // SetAllExtraIcons(hwnd,0);
	SendMessage(GetParent(hwnd),WM_NOTIFY,0,(LPARAM)&nm);
}