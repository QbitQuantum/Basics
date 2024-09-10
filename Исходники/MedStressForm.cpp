fresult MedStressForm::CreateMenu( IMenu** o_mnu )
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
	mis->ImgHandle = big_arrow_left;
	mis->Handler = _AutoDispatchMenuHandler;
	mis->Empty = FALSE;

	//ItemOriginB
	mis = &mf->Settings[ItemOriginB];
	mis->ImgHandle = big_arrow_left;
	mis->Handler = NULL;
	mis->Empty = FALSE;

	//ItemOriginС
	mis = &mf->Settings[ItemOriginC];
	mis->ImgHandle = big_arrow_left;
	mis->Handler = NULL;
	mis->Empty = FALSE;

	//ItemOriginX
	mis = &mf->Settings[ItemOriginX];
	mis->ImgHandle = big_arrow_right;
	mis->Handler = NULL;
	mis->Empty = FALSE;

	//ItemOriginY
	mis = &mf->Settings[ItemOriginY];
	mis->ImgHandle = big_arrow_right;
	mis->Handler = NULL;
	mis->Empty = FALSE;

	//ItemOriginZ
	mis = &mf->Settings[ItemOriginZ];
	mis->ImgHandle = big_arrow_right;
	mis->Handler = NULL;
	mis->Empty = FALSE;

	//ItemOriginL
	mis = &mf->Settings[ItemOriginL];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "доб.рану";
	fres = _FormManager->GetOpenFormHandler(_App->Forms->MedChooseWoundFormName,&mis->Handler);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;


	//ItemOriginE
	mis = &mf->Settings[ItemOriginE];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "назад";
	fres = _FormManager->GetCloseFormHandler(&mis->Handler, fsrNone);
	ENSURESUCCESS(fres);
	mis->Empty = FALSE;

	//ItemOriginR
	mis = &mf->Settings[ItemOriginR];
	mis->ImgHandle = small_arrow_bottom;
	mis->Text = "состояние";
	fres = _FormManager->GetOpenFormHandler(_App->Forms->MedStatusFormName,&mis->Handler);
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

	*o_mnu = mnu;

	return SUCCESS;

}