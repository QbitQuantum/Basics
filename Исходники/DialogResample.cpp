DialogResample::DialogResample(PPScreen* screen, 
							   DialogResponder* responder,
							   pp_int32 id) :
	PPDialogBase(),
	count(0),
	resamplerHelper(new ResamplerHelper()),
	interpolationType(1),
	adjustFtAndRelnote(true)
{
#ifdef __LOWRES__
	initDialog(screen, responder, id, "Resample" PPSTR_PERIODS, 290, 142+15+20+16, 26+15, "Ok", "Cancel");
#else
	initDialog(screen, responder, id, "Resample" PPSTR_PERIODS, 290, 142+20+16, 26, "Ok", "Cancel");
#endif

	pp_int32 x = getMessageBoxContainer()->getLocation().x;
	
	pp_int32 width = getMessageBoxContainer()->getSize().width;
	
	pp_int32 x2 = x;
	pp_int32 y2 = getMessageBoxContainer()->getControlByID(MESSAGEBOX_STATICTEXT_MAIN_CAPTION)->getLocation().y;

	PPButton* button;

	y2 +=16;
	
	// enter edit field 1
	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "Relative note", true));	
	
	x2+=17*8;
	PPListBox* listBox = new PPListBox(MESSAGEBOX_LISTBOX_VALUE_ONE, screen, this, PPPoint(x2, y2), PPSize(7*8,12), true, true, false);
	listBox->showSelection(false);
	listBox->setBorderColor(messageBoxContainerGeneric->getColor());
	listBox->setMaxEditSize(8);
	listBoxes[0] = listBox;
	messageBoxContainerGeneric->addControl(listBox);	
	
	button = new PPButton(MESSAGEBOX_BUTTON_INCREASE_VALUEONE, screen, this, PPPoint(x2 + listBox->getSize().width + 2, y2), PPSize(16, 11));
	button->setText("+");
	messageBoxContainerGeneric->addControl(button);
	
	button = new PPButton(MESSAGEBOX_BUTTON_DECREASE_VALUEONE, screen, this, PPPoint(x2 + listBox->getSize().width + 2 + button->getSize().width + 1, y2), PPSize(16, 11));
	button->setText("-");
	messageBoxContainerGeneric->addControl(button);

	y2+=16;

	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "Fine tune", true));	
	
	x2+=17*8;
	listBox = new PPListBox(MESSAGEBOX_LISTBOX_VALUE_TWO, screen, this, PPPoint(x2, y2), PPSize(7*8,12), true, true, false);
	listBox->showSelection(false);
	listBox->setBorderColor(messageBoxContainerGeneric->getColor());
	listBox->setMaxEditSize(8);
	listBoxes[1] = listBox;
	messageBoxContainerGeneric->addControl(listBox);	
	
	button = new PPButton(MESSAGEBOX_BUTTON_INCREASE_VALUETWO, screen, this, PPPoint(x2 + listBox->getSize().width + 2, y2), PPSize(16, 11));
	button->setText("+");
	messageBoxContainerGeneric->addControl(button);
	
	button = new PPButton(MESSAGEBOX_BUTTON_DECREASE_VALUETWO, screen, this, PPPoint(x2 + listBox->getSize().width + 2 + button->getSize().width + 1, y2), PPSize(16, 11));
	button->setText("-");
	messageBoxContainerGeneric->addControl(button);

	y2+=16;

	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "C4 speed (Hz)", true));	
	
	x2+=14*8;
	listBox = new PPListBox(MESSAGEBOX_LISTBOX_VALUE_THREE, screen, this, PPPoint(x2, y2), PPSize(10*8,12), true, true, false);
	listBox->showSelection(false);
	listBox->setBorderColor(messageBoxContainerGeneric->getColor());
	listBox->setMaxEditSize(8);
	listBoxes[2] = listBox;
	messageBoxContainerGeneric->addControl(listBox);	
	
	button = new PPButton(MESSAGEBOX_BUTTON_INCREASE_VALUETHREE, screen, this, PPPoint(x2 + listBox->getSize().width + 2, y2), PPSize(16, 11));
	button->setText("+");
	messageBoxContainerGeneric->addControl(button);
	
	button = new PPButton(MESSAGEBOX_BUTTON_DECREASE_VALUETHREE, screen, this, PPPoint(x2 + listBox->getSize().width + 2 + button->getSize().width + 1, y2), PPSize(16, 11));
	button->setText("-");
	messageBoxContainerGeneric->addControl(button);

	y2+=16;
	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "New size:", true));	
	x2+=18*8;
	messageBoxContainerGeneric->addControl(new PPStaticText(MESSAGEBOX_STATICTEXT_USER1, screen, this, PPPoint(x2, y2+2), "XXXXXXXX"));	

	y2+=16;

	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "Interpolation:", true));	
	
	x2+=15*8;
	button = new PPButton(MESSAGEBOX_CONTROL_USER1, screen, this, PPPoint(x2, y2), PPSize(button->getLocation().x + button->getSize().width - x2, 11), false);
	button->setText(resamplerHelper->getResamplerName(interpolationType, true));
	button->setColor(messageBoxContainerGeneric->getColor());
	button->setTextColor(PPUIConfig::getInstance()->getColor(PPUIConfig::ColorStaticText));

	messageBoxContainerGeneric->addControl(button);

	y2+=16;

	x2 = x + width / 2 - (10*8+35 + 14*8)/2;
	messageBoxContainerGeneric->addControl(new PPStaticText(0, screen, this, PPPoint(x2, y2+2), "Adjust Ft/Rel.Note:", true));	
	x2+= 21*8;
	
	checkBox = new PPCheckBox(MESSAGEBOX_CONTROL_USER2, screen, this, PPPoint(x2, y2+1));
	checkBox->checkIt(adjustFtAndRelnote);
	messageBoxContainerGeneric->addControl(checkBox);

	y2+=16;

#ifdef __LOWRES__
	pp_int32 height = getMessageBoxContainer()->getSize().height;
	pp_int32 y = getMessageBoxContainer()->getLocation().y;

	const char buttonTexts[] = {'1','2','3','4','5','6','7','8','9','0','+','-','.','<','>'};
	
	pp_int32 bWidth = (width - 22*2 - 2*3) / sizeof(buttonTexts);
	pp_int32 x2_2 = x+4;
	
	pp_int32 y2_2 = y+height - 4 - 13;
	
	messageBoxContainerGeneric->addControl(new PPSeperator(0, screen, PPPoint(x2_2-1, y2_2-3), width-2*3, messageBoxContainerGeneric->getColor(), true));
	
	pp_uint32 i = 0;
	for (i = 0; i < sizeof(buttonTexts); i++)
	{
		button = new PPButton(MESSAGEBOX_BUTTON_KEYS_BASE+i, screen, this, PPPoint(x2_2, y2_2), PPSize(bWidth+1, 13));
		button->setText(buttonTexts[i]);
		messageBoxContainerGeneric->addControl(button);
		x2_2+=bWidth;
	}
	
	bWidth = 22;
	
	button = new PPButton(MESSAGEBOX_BUTTON_KEYS_BASE+i, screen, this, PPPoint(x2_2, y2_2), PPSize(bWidth+1-3, 13));
	button->setFont(PPFont::getFont(PPFont::FONT_TINY));
	button->setText("Del");
	messageBoxContainerGeneric->addControl(button);
	x2_2+=bWidth-3;
	i++;
	button = new PPButton(MESSAGEBOX_BUTTON_KEYS_BASE+i, screen, this, PPPoint(x2_2, y2_2), PPSize(bWidth+1, 13));
	button->setFont(PPFont::getFont(PPFont::FONT_TINY));
	button->setText("Back");
	messageBoxContainerGeneric->addControl(button);
#endif

	currentSelectedListBox = 0;
	relnote = finetune = 0;
	c4spd = 0.0f;
}