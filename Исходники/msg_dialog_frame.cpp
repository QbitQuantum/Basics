void msg_dialog_frame::CreateOsk(const std::string& msg, char16_t* osk_text)
{
	if (osk_dialog)
	{
		osk_dialog->close();
		delete osk_dialog;
	}

	osk_dialog = new custom_dialog(type.disable_cancel);
	osk_dialog->setModal(true);
	osk_text_return = osk_text;

	//Title
	osk_dialog->setWindowTitle(qstr(msg));
	osk_dialog->setWindowFlags(osk_dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	//Text Input
	QLineEdit* input = new QLineEdit(osk_dialog);
	input->setFixedWidth(200);
	input->setFocus();

	//Ok Button
	QPushButton* button_ok = new QPushButton("Ok", osk_dialog);
	button_ok->setFixedWidth(50);

	//Layout
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->setAlignment(Qt::AlignCenter);
	buttonsLayout->addWidget(button_ok);

	QFormLayout* layout = new QFormLayout(osk_dialog);
	layout->setFormAlignment(Qt::AlignHCenter);
	layout->addRow(input);
	layout->addRow(buttonsLayout);
	osk_dialog->setLayout(layout);

	//Events
	connect(input, &QLineEdit::textChanged, [=] {
		std::memcpy(osk_text_return, reinterpret_cast<const char16_t*>(input->text().constData()), input->text().size() * 2);
		on_osk_input_entered();
	});
	connect(input, &QLineEdit::returnPressed, [=] { on_close(CELL_MSGDIALOG_BUTTON_OK); osk_dialog->accept(); });
	connect(button_ok, &QAbstractButton::clicked, [=] { on_close(CELL_MSGDIALOG_BUTTON_OK); osk_dialog->accept(); });
	connect(osk_dialog, &QDialog::rejected, [=] {if (!type.disable_cancel) { on_close(CELL_MSGDIALOG_BUTTON_ESCAPE); }});

	//Fix size
	osk_dialog->setFixedSize(osk_dialog->sizeHint());
	osk_dialog->show();
}