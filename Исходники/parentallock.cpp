void eParentalSetup::init_eParentalSetup()
{
	loadSettings();

	parentallock=new eCheckbox(this, parentalpin_enabled, 1);
	parentallock->setText(_("Parental lock"));
	parentallock->move(ePoint(10, yPos()));
	parentallock->resize(eSize(200, widgetHeight()));
	parentallock->setHelpText(_("enable/disable parental lock"));
	CONNECT(parentallock->checked, eParentalSetup::plockChecked );

	changeParentalPin = new eButton(this);
	changeParentalPin->setText(_("change PIN"));
	changeParentalPin->move(ePoint(230, yPos()));
	changeParentalPin->resize(eSize(160, widgetHeight()));
	changeParentalPin->setHelpText(_("change Parental PIN (ok)"));
	changeParentalPin->loadDeco();
	CONNECT(changeParentalPin->selected_id, eParentalSetup::changePin );
	if ( !parentalpin_enabled )
	{
		changeParentalPin->hide();
	}

	nextYPos(35);  
	setuplock=new eCheckbox(this, setuppin_enabled, 1);
	setuplock->setText(_("Setup lock"));
	setuplock->move(ePoint(10, yPos()));
	setuplock->resize(eSize(200, widgetHeight()));
	setuplock->setHelpText(_("enable/disable setup lock"));
	CONNECT(setuplock->checked, eParentalSetup::slockChecked );

	changeSetupPin = new eButton(this);
	changeSetupPin->setText(_("change PIN"));
	changeSetupPin->move( ePoint( 230, yPos()));
	changeSetupPin->resize( eSize(160, widgetHeight()));
	changeSetupPin->setHelpText(_("change Setup PIN (ok)"));
	changeSetupPin->loadDeco();
	CONNECT(changeSetupPin->selected_id, eParentalSetup::changePin );
	if ( !setuppin_enabled )
	{
		changeSetupPin->hide();
	}

	nextYPos(35);  
	pin_timeout_label = new eLabel (this);
	pin_timeout_label->setText (_("Pin timeout"));
	pin_timeout_label->move (ePoint (10, yPos()));
	pin_timeout_label->resize (eSize (370, widgetHeight()));

	pin_timeout = new eNumber (this, 1, 0, 999, 4, &pintimeout, 0, pin_timeout_label);
	pin_timeout->move (ePoint (230, yPos()));
	pin_timeout->resize (eSize (50, widgetHeight()));
	pin_timeout->setHelpText (_("Number of minutes the entered pin is valid. After this timeout you need to re-enter the pin when zapping to protected service (0 to disable)"));
	pin_timeout->loadDeco();

	nextYPos(35);  
	maxpin_errors_label = new eLabel (this);
	maxpin_errors_label->setText (_("Max Pin errors"));
	maxpin_errors_label->move (ePoint (10, yPos()));
	maxpin_errors_label->resize (eSize (370, widgetHeight()));

	maxpin_errors = new eNumber (this, 1, 0, 999, 4, &maxpinerrors, 0, maxpin_errors_label);
	maxpin_errors->move (ePoint (230, yPos()));
	maxpin_errors->resize (eSize (50, widgetHeight()));
	maxpin_errors->setHelpText (_("Maximum number of chances to enter correct pin. When pin is entered wrong for x times the pin validation will be blocked temporarily (0 to disable)"));
	maxpin_errors->loadDeco();

	nextYPos(35);  
	pinerror_block_time_label = new eLabel (this);
	pinerror_block_time_label->setText (_("Pin block timeout"));
	pinerror_block_time_label->move (ePoint (10, yPos()));
	pinerror_block_time_label->resize (eSize (370, widgetHeight()));

	pinerror_block_time = new eNumber (this, 1, 1, 999, 4, &pinerrorblocktime, 0, pinerror_block_time_label);
	pinerror_block_time->move (ePoint (230, yPos()));
	pinerror_block_time->resize (eSize (50, widgetHeight()));
	pinerror_block_time->setHelpText (_("Number of minutes pincode check is disabled when pin validation has failed maximum times."));
	pinerror_block_time->loadDeco();

	nextYPos(35);  
	hidelocked=new eCheckbox(this, shidelocked, 1);
	hidelocked->setText(_("Hide locked services"));
	hidelocked->move(ePoint(10, yPos()));
	hidelocked->resize(eSize(380, widgetHeight()));
	hidelocked->setHelpText(_("don't show locked services in any list"));
	hidelocked->loadDeco();
	CONNECT(hidelocked->checked, eParentalSetup::hidelockChecked );
	if ( !parentalpin_enabled )
	{
		hidelocked->hide();
	}

	/* help text for parental setup */
	setHelpText(_("\tParental Lock\n\n>>> [MENU] >>> [6] Setup >>> [5] Parental Lock\n. . . . . . . . . .\n\n" \
								"Here you can enable and setup Parental Lock. After reboot locked channels will not be available unless unlocked with your PIN code\n" \
								". . . . . . . . . .\n\nUsage:\n\n[UP]/[DOWN]\tSelect Inputfield or Button\n\nParental lock\tToggle Channel access on/off\n\n" \
								"Setup lock\tToggle setup access on/off\n\nChange PIN\tEnter a new PIN code\n\n[GREEN]\tSave Settings and Close Window\n\n" \
								"[EXIT]\tClose window without saving changes"));
								

	buildWindow();

	CONNECT(bOK->selected, eParentalSetup::okPressed);
}