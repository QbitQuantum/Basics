void exportDB(HANDLE hContact, char* module) // hContact == -1 export entire db. module == NULL export entire contact.
{                                            // hContact == -1, module == "" - all contacts
	FILE* file = NULL;
	char fileName[MAX_PATH];
	int nullcontactDone = 0;
	ModuleSettingLL modlist;
	struct ModSetLinkLinkItem *mod;

	// enum all the modules
	if (!EnumModules(&modlist)) { msg(Translate("Error Loading Module List"),modFullname); return;}

	if (Openfile(fileName, ((int)hContact==-1)?NULL:module))
	{
		if (!(file = fopen(fileName, "wt"))) { msg(Translate("Couldn't open file for writing"), modFullname); return; }

		SetCursor(LoadCursor(NULL,IDC_WAIT));

		// exporting entire db
		if (hContact == INVALID_HANDLE_VALUE)
		{
			hContact = NULL;

			if (module == NULL)
			{
				fprintf(file, "SETTINGS:\n");
				mod = modlist.first;
				while(mod)
				{
					if (IsModuleEmpty(hContact, mod->name))
					{
						mod = (struct ModSetLinkLinkItem *)mod->next;
						continue;
					}
					exportModule(hContact, mod->name, file);
					mod = (struct ModSetLinkLinkItem *)mod->next;
					if (mod)
						fprintf(file, "\n");
				}
			}
			else
			{
				if (module == "") module = NULL; // reset module for all contacts export
			}

			hContact = (HANDLE)CallService(MS_DB_CONTACT_FINDFIRST, 0, 0);

			while (hContact)
			{
				if (!hContact) continue;

				// filter
				if (Mode != MODE_ALL)
				{
					char szProto[256];
					int loaded = 0;

					if (GetValue(hContact,"Protocol","p",szProto,SIZEOF(szProto)))
						loaded = IsProtocolLoaded(szProto);

					if ((loaded && Mode == MODE_UNLOADED) || (!loaded && Mode == MODE_LOADED))
					{
						hContact = (HANDLE)CallService(MS_DB_CONTACT_FINDNEXT, (WPARAM)hContact, 0);
						continue;
					}
				}

				fprintf(file, "CONTACT: %s\n", NickFromHContact(hContact));

				if (module == NULL) // export all modules
				{
					mod = modlist.first;
					while(mod)
					{
						if (IsModuleEmpty(hContact, mod->name))
						{
							mod = (struct ModSetLinkLinkItem *)mod->next;
							continue;
						}
						exportModule(hContact, mod->name, file);
						mod = (struct ModSetLinkLinkItem *)mod->next;
						if (mod)
							fprintf(file, "\n");
					}
				}
				else // export module
				{
					exportModule(hContact, module, file);
				}
				hContact = (HANDLE)CallService(MS_DB_CONTACT_FINDNEXT, (WPARAM)(HANDLE)hContact, 0);
			}
		}
		// exporting a contact
		else
		{
			if (!module) // exporting every module
			{
				if (hContact)
					fprintf(file, "CONTACT: %s\n", NickFromHContact(hContact));
				else
					fprintf(file, "SETTINGS:\n");

				mod = modlist.first;
				while(mod)
				{
					if (IsModuleEmpty(hContact, mod->name))
					{
						mod = (struct ModSetLinkLinkItem *)mod->next;
						continue;
					}
					exportModule(hContact, mod->name, file);
					mod = (struct ModSetLinkLinkItem *)mod->next;
					if (mod)
						fprintf(file, "\n");
				}
			}
			else
			{
				if (hContact)
					fprintf(file, "FROM CONTACT: %s\n", NickFromHContact(hContact));
				else
					fprintf(file, "SETTINGS:\n");

				exportModule(hContact, module, file);
			}
		}
		fclose(file);

		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}

	FreeModuleSettingLL(&modlist);
}