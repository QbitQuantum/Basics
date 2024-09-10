void TextFormatButtons::showMathSymbols()
{
	SymbolDialog *mathSymbols = new SymbolDialog(SymbolDialog::mathSymbols, this, Qt::Tool);
	mathSymbols->setAttribute(Qt::WA_DeleteOnClose);
	QFont f = connectedTextEdit->font();
	if(f.pointSize()<14)
		f.setPointSize(14);
	mathSymbols->setFont(f);
	connect(mathSymbols, SIGNAL(addLetter(const QString&)), this, SLOT(addSymbol(const QString&)));
	mathSymbols->show();
	mathSymbols->setFocus();
}