void osk_dialog_frame::Create(const std::string& title, const std::u16string& message, char16_t* init_text, u32 charlimit, u32 options)
{
	state = OskDialogState::Open;

	static const auto& lineEditWidth = []() {return QLabel("This is the very length of the lineedit due to hidpi reasons.").sizeHint().width(); };

	if (m_dialog)
	{
		m_dialog->close();
		delete m_dialog;
	}

	m_dialog = new custom_dialog(false);
	m_dialog->setModal(true);

	// Title
	m_dialog->setWindowTitle(qstr(title));

	// Message
	QLabel* message_label = new QLabel(QString::fromStdU16String(message));

	// Text Input Counter
	const QString text = QString::fromStdU16String(std::u16string(init_text));
	QLabel* inputCount = new QLabel(QString("%1/%2").arg(text.length()).arg(charlimit));

	// Ok Button
	QPushButton* button_ok = new QPushButton("Ok", m_dialog);

	// Button Layout
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->setAlignment(Qt::AlignCenter);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(button_ok);
	buttonsLayout->addStretch();

	// Input Layout
	QHBoxLayout* inputLayout = new QHBoxLayout;
	inputLayout->setAlignment(Qt::AlignHCenter);

	// Text Input
	if (options & CELL_OSKDIALOG_NO_RETURN)
	{
		QLineEdit* input = new QLineEdit(m_dialog);
		input->setFixedWidth(lineEditWidth());
		input->setMaxLength(charlimit);
		input->setText(text);
		input->setFocus();

		if (options & CELL_OSKDIALOG_NO_SPACE)
		{
			input->setValidator(new QRegExpValidator(QRegExp("^\\S*$"), this));
		}

		connect(input, &QLineEdit::textChanged, [=](const QString& text)
		{
			inputCount->setText(QString("%1/%2").arg(text.length()).arg(charlimit));
			SetOskText(text);
			on_osk_input_entered();
		});
		connect(input, &QLineEdit::returnPressed, m_dialog, &QDialog::accept);

		inputLayout->addWidget(input);
	}
	else
	{
		QTextEdit* input = new QTextEdit(m_dialog);
		input->setFixedWidth(lineEditWidth());
		input->setText(text);
		input->setFocus();
		input->moveCursor(QTextCursor::End);
		m_text_old = text;

		connect(input, &QTextEdit::textChanged, [=]()
		{
			QString text = input->toPlainText();

			if (text == m_text_old)
			{
				return;
			}

			QTextCursor cursor = input->textCursor();
			const int cursor_pos_new = cursor.position();
			const int cursor_pos_old = cursor_pos_new + m_text_old.length() - text.length();

			// Reset to old state if character limit was reached
			if ((u32)m_text_old.length() >= charlimit && (u32)text.length() > charlimit)
			{
				input->blockSignals(true);
				input->setPlainText(m_text_old);
				cursor.setPosition(cursor_pos_old);
				input->setTextCursor(cursor);
				input->blockSignals(false);
				return;
			}

			int cursor_pos = cursor.position();

			// Clear text of spaces if necessary
			if (options & CELL_OSKDIALOG_NO_SPACE)
			{
				int trim_len = text.length();
				text.remove(QRegExp("\\s+"));
				trim_len -= text.length();
				cursor_pos -= trim_len;
			}

			// Crop if more than one character was pasted and the character limit was exceeded
			text.chop(text.length() - charlimit);

			// Set new text and block signals to prevent infinite loop
			input->blockSignals(true);
			input->setPlainText(text);
			cursor.setPosition(cursor_pos);
			input->setTextCursor(cursor);
			input->blockSignals(false);

			m_text_old = text;

			inputCount->setText(QString("%1/%2").arg(text.length()).arg(charlimit));
			SetOskText(text);
			on_osk_input_entered();
		});

		inputLayout->addWidget(input);
	}

	inputLayout->addWidget(inputCount);

	QFormLayout* layout = new QFormLayout(m_dialog);
	layout->setFormAlignment(Qt::AlignHCenter);
	layout->addRow(message_label);
	layout->addRow(inputLayout);
	layout->addRow(buttonsLayout);
	m_dialog->setLayout(layout);

	// Events
	connect(button_ok, &QAbstractButton::clicked, m_dialog, &QDialog::accept);

	connect(m_dialog, &QDialog::accepted, [=]
	{
		on_osk_close(CELL_MSGDIALOG_BUTTON_OK);
	});

	connect(m_dialog, &QDialog::rejected, [=]
	{
		on_osk_close(CELL_MSGDIALOG_BUTTON_ESCAPE);
	});

	// Fix size
	m_dialog->layout()->setSizeConstraint(QLayout::SetFixedSize);
	m_dialog->show();
}