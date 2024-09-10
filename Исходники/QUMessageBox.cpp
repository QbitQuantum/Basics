QPushButton* QUMessageBox::createButton(const QIcon &icon, const QString &text, bool isDefault) {
	QPushButton *btn = new QPushButton(icon, text, this);

	if(isDefault)
		btn->setFocus();

	_buttonGroup.addButton(btn, _buttonGroup.buttons().size());
	btn->setShortcut(QVariant(_buttonGroup.buttons().size()).toString());

	return btn;
}