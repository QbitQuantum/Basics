fresult MedChooseWoundForm::CreateMenu( IMenu** o_mnu )
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


	//ItemOriginA
	mis = &mf->Settings[ItemOriginA];
	mis->Text = "Травма головы";
	mis->ImgHandle = small_arrow_left;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginB
	mis = &mf->Settings[ItemOriginB];
	mis->Text = "Травма\nконечности";
	mis->ImgHandle = small_arrow_left;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginС
	mis = &mf->Settings[ItemOriginC];
	mis->Text = "Травма\nкорпуса";
	mis->ImgHandle = small_arrow_left;
	fres = _FormManager->GetOpenFormHandler(_App->Forms->MedChooseTorsoWoundFormName,&mis->Handler);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;

	//ItemOriginX
	mis = &mf->Settings[ItemOriginX];
	mis->Text = "Избит";
	mis->ImgHandle = small_arrow_right;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginY
	mis = &mf->Settings[ItemOriginY];
	mis->Text = "Оглушен";
	mis->ImgHandle = small_arrow_right;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &mf->Settings[ItemOriginZ];
	mis->Text = "При смерти";
	mis->ImgHandle = small_arrow_right;
	mis->Handler = _AutoDispatchMenuHandler;
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

	*o_mnu = mnu;
	return SUCCESS;
}