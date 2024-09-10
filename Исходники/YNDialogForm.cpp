fresult YNDialogForm::CreateMenu( IMenu** o_mnu )
{
	fresult fres;
	MenuFactory* mf = _Factories->GetMenuFactory();

	//ready factory
	mf->CurrentInterlaced = true;
	mf->CurrentTextFormatHandle = TF_MENU;
	mf->CurrentEvenTextFormatHandle = TF_MENUEVEN;
	mf->ClearSettings();

	//Set up menu
	MenuItemSettings* mis;
	//ItemOriginZ
	mis = &mf->Settings[ItemOriginZ];
	mis->ImgHandle = small_arrow_right_red;
	mis->OverrideTextFormat = TF_MENU_RED;
	mis->Text = "                     ";
	fres = _FormManager->GetCloseFormHandler(&mis->Handler, fsrOK);
	mis->Empty = FALSE;

	//ItemOriginE
	mis = &mf->Settings[ItemOriginE];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "назад";
	fres = _FormManager->GetCloseFormHandler(&mis->Handler, fsrCancel);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;

	//create mnu
	IMenu* mnu = NULL;
	fres = mf->GetMenu(ABCXYZLER, &mnu);
	ENSURESUCCESS(fres);

	//Clean up
	mf->ClearSettings();
	mf->DefaultInterlaced=mf->CurrentInterlaced;
	mf->DefaultTextFormatHandle=mf->CurrentTextFormatHandle;
	mf->DefaultEvenTextFormatHandle=mf->CurrentEvenTextFormatHandle;

	//Get menu Items
	_miYes = (MenuItem*)mnu->GetItem(0);
	FAILIF(_miYes==NULL);
	_miCancel =(MenuItem*)mnu->GetItem(1);
	FAILIF(_miCancel==NULL);

	*o_mnu = mnu;
	return SUCCESS;
}