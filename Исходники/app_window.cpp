QString AppWindow::getText(QString title, QString prompt, QString text)
{
	MWidget *centralWidget = new MWidget;
	QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
	centralWidget->setLayout(layout);

	MLabel *label = new MLabel(prompt, centralWidget);
	label->setStyleName("CommonTitleInverted");

	MTextEdit *textEdit = new MTextEdit(MTextEditModel::SingleLine, text, centralWidget);

	layout->addItem(label);
	layout->addItem(textEdit);

	MDialog* dialog = new MDialog(title, M::OkButton | M::CancelButton);
	dialog->setCentralWidget(centralWidget);

	connect(dialog, SIGNAL(disappeared()), SLOT(processDialogResult()));
	if (dialog->exec(this) == M::OkButton)
		return textEdit->text();
	return "";
}