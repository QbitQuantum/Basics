fresult ItemsListFormBase::CreateMenu( IMenu** o_mnu )
{
	fresult fres;
	MenuFactory* mf = _Factories->GetMenuFactory();

	//ready factory
	mf->CurrentInterlaced = true;
	mf->CurrentTextFormatHandle = TF_MENU;
	mf->CurrentEvenTextFormatHandle = TF_MENUEVEN;
	mf->ClearSettings();

	//Set up menu
	MenuItemSettings* settings = mf->Settings;
	MenuItemSettings* mis;

	//ItemOriginX
	mis = &settings[ItemOriginX];
	mis->ImgHandle = scroll_up;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &settings[ItemOriginZ];
	mis->ImgHandle = scroll_down;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginL
	mis = &settings[ItemOriginL];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = _prevText;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginE
	mis = &settings[ItemOriginE];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "назад";
	fres = _FormManager->GetCloseFormHandler(&mis->Handler, fsrCancel);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;
	
	//ItemOriginR
	mis = &settings[ItemOriginR];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = _nextText;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;
	//call derived update settings
	UpdateMenuSettings(settings);

	//create mnu
	IMenu* mnu = NULL;
	fres = mf->GetMenu(ABCXYZLER, &mnu);
	ENSURESUCCESS(fres);

	for (ubyte_t i=0; i<mnu->GetItemsCount();i++)
	{
		MenuItem* mi = (MenuItem*)(mnu->GetItem(i));
		if (StringEquals(mi->GetName(), "L") == TRUE)
		{
			_mnuBack = mi;
		}
		if (StringEquals(mi->GetName(), "R") == TRUE)
		{
			_mnuNext = mi;
		}
	}

	//Clean up
	mf->ClearSettings();
	mf->DefaultInterlaced=mf->CurrentInterlaced;
	mf->DefaultTextFormatHandle=mf->CurrentTextFormatHandle;
	mf->DefaultEvenTextFormatHandle=mf->CurrentEvenTextFormatHandle;

	//Get menu Items

	*o_mnu = mnu;
	return SUCCESS;
}