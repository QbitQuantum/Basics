status_t perform_edit(MTextAddOn *addon)
{
	status_t result = B_OK;
	entry_ref headerFile;
	BPoint where(0,0);

	if (addon->Window() && addon->Window()->Lock())
	{
		uint32 buttons;
		addon->Window()->ChildAt(0)->GetMouse(&where, &buttons);
		addon->Window()->ChildAt(0)->ConvertToScreen(&where);
		addon->Window()->Unlock();
		where += BPoint(-3,-3);
	}

	result = addon->GetRef(headerFile);
	BString fileName;
	if (result >= B_OK)
		fileName = headerFile.name;

	CLanguageInterface *languageInterface = NULL;
	if (addon->Window())
	{
		PDoc *doc = dynamic_cast<PDoc *>(addon->Window());
		if (doc && doc->TextView())
		{
			int lang = doc->TextView()->Language();
			if (lang > -1)
				languageInterface = CLanguageInterface::FindIntf(lang);
		}
	}

	BString header;
	result = RunPopUpMenu(where, header, fileName, languageInterface);
	//printf("result %s\n", strerror(result));
	if (result == B_CANCELED)
		return B_OK;
	if (result < B_OK)
		return result;

#if 0
	// Do not change the case if a shift key was pressed
	if ((modifiers() & B_SHIFT_KEY) == 0)
		fileName.ToUpper();
#endif

	addon->Select(0, 0);

	addon->Insert(header.String());
	
	return result;
}