void PrefGeneral::AddLanguageMenu()
{
	while (langmenu->ItemAt(0))
		langmenu->RemoveItem(langmenu->ItemAt(0));

	app_info ai;
	be_app->GetAppInfo(&ai);
	BEntry entry(&ai.ref);
	BPath path;
	entry.GetPath(&path);
	path.GetParent(&path);
	path.Append("Languages");
	BDirectory directory(path.Path());
	char name[B_FILE_NAME_LENGTH];

	while (directory.GetNextEntry(&entry, false) == B_OK){
		if(entry.IsFile()){
			entry.GetPath(&path);
			entry.GetName(name);
			BMessage *m = new BMessage(CHANGE_LANGUAGE);
			m->AddString("language",name);
			BMenuItem *menuitem = new BMenuItem(name, m, 0, 0);
			menuitem->SetTarget(this);
			langmenu->AddItem(menuitem);
			if(!strcmp(name,Language.Name())){
				menuitem->SetMarked(true);
			}
		}
	}
}