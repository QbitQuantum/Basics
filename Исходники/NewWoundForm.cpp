fresult NewWoundForm::CreateMenu( IMenu** o_mnu )
{
	fresult fres;
	MenuFactory* mf = _Factories->GetMenuFactory();
	MenuItemFactory* mif = _Factories->GetMenuItemFactory();

	//ready factory
	mf->CurrentInterlaced = FALSE;
	mf->CurrentTextFormatHandle = TF_MENU;
	mf->CurrentEvenTextFormatHandle = TF_MENU;
	mif->CurrentTextLines = 2;

	mf->ClearSettings();

	//Set up menu
	MenuItemSettings* mis;

	IMenuHandler* mh = CREATE_MENU_HANDLER(NewWoundForm, OnWound);

	//ItemOriginA
	mis = &mf->Settings[ItemOriginA];
	mis->Text = "Голова\n     ";
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginB
	mis = &mf->Settings[ItemOriginB];
	mis->Text = "Живот\n     ";
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginС
	mis = &mf->Settings[ItemOriginC];
	mis->Text = "Левая\n рука ";
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginX
	mis = &mf->Settings[ItemOriginX];
	mis->Text = "Грудь\n     ";
	mis->ScreenOrigin.Top = mis->ScreenOrigin.Top -5;
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginY
	mis = &mf->Settings[ItemOriginY];
	mis->Text = "Спина\n     ";
	mis->ScreenOrigin.Top = mis->ScreenOrigin.Top -5;
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &mf->Settings[ItemOriginZ];
	mis->Text = "Правая\n рука";
	mis->ScreenOrigin.Top = mis->ScreenOrigin.Top -5;
	mis->Handler = mh;
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &mf->Settings[ItemOriginL];
	mis->Text = "Левая\n нога";
	mis->Handler = mh;
	mis->Empty = FALSE;

	mis = &mf->Settings[ItemOriginE];
	mis->ImgHandle = GreenOk;
	fres = _FormManager->GetCloseFormHandler(&mis->Handler);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &mf->Settings[ItemOriginR];
	mis->Text = "Правая\n нога";
	mis->Handler = mh;
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
	mif->CurrentTextLines= mif->DefaultTextLines;
	*o_mnu = mnu;

	return SUCCESS;

}