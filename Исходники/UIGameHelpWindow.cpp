UINode* UIGameHelpWindow::createHPanel ()
{
	UINode* hbox = new UINode(_frontend);
	hbox->setLayout(new UIHBoxLayout(hboxspacing, false));
	hbox->setBackgroundColor(backgroundColor);
	hbox->setBorder(true);
	hbox->setBorderColor(colorWhite);
	hbox->setStandardPadding();
	return hbox;
}