int InstructionsMenu::addDisabledTextButton(const string &text, int x, int y, bool isHeader)
{
	TextButton *txtBut = new TextButton();
	txtBut->setText(text);	
	txtBut->setX(x);
	txtBut->setY(y);
	txtBut->setEnabled(false);
	txtBut->setTextColor(INSTR_R, INSTR_G, INSTR_B);
	if (isHeader) {
		txtBut->setTextSize(HEADER_TEXT_SIZE);	
	} else {
		txtBut->setTextSize(STANDARD_TEXT_SIZE);
	}
	m_buttons.push_back(txtBut);
	return txtBut->getHeight() + BUTTON_SEP;	
}