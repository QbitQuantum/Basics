/** Called when the context-menu of a contact is about to be displayed
*
* This will test which of the 4 menu item should be displayed, depending
* on which contact triggered the event
*
* @param wParam :	\c HANDLE to the contact that triggered the event
* @param lParam :	Always set to 0;
*/
int Meta_ModifyMenu(WPARAM wParam, LPARAM lParam)
{
	CLISTMENUITEM mi;
	DBVARIANT dbv;
	HANDLE hContact;
	char *proto;
	char buf[512], buffer2[512];
	int i, iconIndex;
	WORD status;

	mi.flags = CMIM_FLAGS;
	mi.cbSize = sizeof(CLISTMENUITEM);

	if(DBGetContactSettingDword((HANDLE)wParam,META_PROTO,META_ID,-1) != (DWORD)-1)
	{
		int num_contacts, i;

		// save the mouse pos in case they open a subcontact menu
		GetCursorPos(&menuMousePoint);
		
		// This is a MetaContact, show the edit, force default, and the delete menu, and hide the others
		CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuEdit, (LPARAM)&mi);
		//mi.flags |= CMIM_NAME;
		//if(DBGetContactSettingByte((HANDLE)wParam, META_PROTO, "ForceDefault", 0))
		//	mi.pszName = Translate("Unforce Default");
		//else
		//	mi.pszName = Translate("Force Default");
		//CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuForceDefault, (LPARAM)&mi);
		mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
		CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuAdd, (LPARAM)&mi);
		CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuConvert, (LPARAM)&mi);
		CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDefault, (LPARAM)&mi);
		mi.flags = CMIM_FLAGS | CMIM_NAME | CMIF_HIDDEN;	// we don't need delete - already in contact menu
		mi.pszName = Translate("Delete MetaContact");
		CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDelete, (LPARAM)&mi);


		//show subcontact menu items
		num_contacts = DBGetContactSettingDword((HANDLE)wParam, META_PROTO, "NumContacts", 0);
		for(i = 0; i < MAX_CONTACTS; i++) {
			if(i < num_contacts) {
				hContact = Meta_GetContactHandle((HANDLE)wParam, i);
				proto = _strdup((char *)CallService(MS_PROTO_GETCONTACTBASEPROTO, (WPARAM)hContact, 0));

				if(!proto)
					status = ID_STATUS_OFFLINE;
				else
					status = DBGetContactSettingWord(hContact, proto, "Status", ID_STATUS_OFFLINE);

				if(options.menu_contact_label == DNT_UID) {
					strcpy(buf, "Login");
					strcat(buf, _itoa(i, buffer2, 10));

					DBGetContactSetting((HANDLE)wParam,META_PROTO,buf,&dbv);
					switch(dbv.type)
					{
						case DBVT_ASCIIZ:
							mir_snprintf(buf,512,"%s",dbv.pszVal);
							break;
						case DBVT_BYTE:
							mir_snprintf(buf,512,"%d",dbv.bVal);
							break;
						case DBVT_WORD:
							mir_snprintf(buf,512,"%d",dbv.wVal);
							break;
						case DBVT_DWORD:
							mir_snprintf(buf,512,"%d",dbv.dVal);
							break;
						default:
							buf[0] = 0;
					}
					DBFreeVariant(&dbv);
					mi.pszName = buf;
					mi.flags = 0;
				} else {
					char *name = (char *)CallService(MS_CLIST_GETCONTACTDISPLAYNAME, (WPARAM)hContact, 0);
					char *wname = (char *)CallService(MS_CLIST_GETCONTACTDISPLAYNAME, (WPARAM)hContact, GCDNF_UNICODE);

					if(wname && strncmp(name, wname, strlen(name)) != 0) {
						mi.pszName = wname;
						mi.flags = CMIF_UNICODE;
					}
					else {
						mi.pszName = name;
						mi.flags = 0;
					}
				}

				mi.flags |= CMIM_FLAGS | CMIM_NAME | CMIM_ICON;

				//mi.hIcon = LoadSkinnedProtoIcon(proto, status);
				iconIndex = (int)CallService(MS_CLIST_GETCONTACTICON, (WPARAM)hContact, 0);
				mi.hIcon = ImageList_GetIcon((HIMAGELIST)CallService(MS_CLIST_GETICONSIMAGELIST, 0, 0), iconIndex, 0);;

				free(proto);

				CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuContact[i], (LPARAM)&mi);
				DestroyIcon(mi.hIcon);
				//CallService(MS_SKIN2_RELEASEICON, (WPARAM)mi.hIcon, 0);
			} else {
				mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
				CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuContact[i], (LPARAM)&mi);
			}
		}

		// show hide nudge menu item
#define MS_NUDGE_SHOWMENU	"NudgeShowMenu"
// wParam = char *szProto
// lParam = BOOL show
		{
			char serviceFunc[256];
			hContact = Meta_GetMostOnline((HANDLE)wParam);
			mir_snprintf(serviceFunc, 256, "%s/SendNudge", (char *)CallService(MS_PROTO_GETCONTACTBASEPROTO, (WPARAM)hContact, 0));
			CallService(MS_NUDGE_SHOWMENU, (WPARAM)META_PROTO, (LPARAM)ServiceExists(serviceFunc));
		}
	}
	else
	{// This is a simple contact
		if(!Meta_IsEnabled())
		{
			// groups disabled - all meta menu options hidden
			mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDefault, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDelete, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuAdd, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuConvert, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuEdit, (LPARAM)&mi);
			for(i = 0; i < MAX_CONTACTS; i++) {
				mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
				CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuContact[i], (LPARAM)&mi);
			}

		} else if(DBGetContactSettingDword((HANDLE)wParam,META_PROTO,META_LINK,(DWORD)-1)!=(DWORD)-1) {
			// The contact is affected to a metacontact.
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDefault, (LPARAM)&mi);
			mi.flags |= CMIM_NAME;
			mi.pszName = (char *)Translate("Remove from MetaContact");
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDelete, (LPARAM)&mi);
			mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuAdd, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuConvert, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuEdit, (LPARAM)&mi);
			for(i = 0; i < MAX_CONTACTS; i++) {
				mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
				CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuContact[i], (LPARAM)&mi);
			}
		} else {
			// The contact is neutral
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuAdd, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuConvert, (LPARAM)&mi);
			mi.flags |= CMIF_HIDDEN;
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuEdit, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDelete, (LPARAM)&mi);
			CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuDefault, (LPARAM)&mi);
			for(i = 0; i < MAX_CONTACTS; i++) {
				mi.flags = CMIM_FLAGS | CMIF_HIDDEN;
				CallService(MS_CLIST_MODIFYMENUITEM, (WPARAM)hMenuContact[i], (LPARAM)&mi);
			}
		}
	}
	return 0;
}