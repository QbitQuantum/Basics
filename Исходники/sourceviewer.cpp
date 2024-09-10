void SourceViewer::setSourceText(const QString &key, const QString &name, const QString &searchText, const QByteArray &sourceTextBuffer)
{
	QTextEdit *logTextEdit = NULL;
	QTextEditorContextMap::const_iterator i = logTextWidgetMap_.find(key);
	if(i == logTextWidgetMap_.end())
	{
		// New tab created..
		logTextEdit = new QTextEdit();
		QObject::connect(logTextEdit, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
		logTextEdit->setReadOnly(true);

		SourceViewContext* ctx = new SourceViewContext();
		ctx->logTextEdit = logTextEdit;
		logTextWidgetMap_.insert(key, ctx);
		ui.tabWidget->insertTab(0, logTextEdit, name);
		ui.tabWidget->setCurrentIndex(0);
	}
	else
	{
		// Already the tab exists.
		logTextEdit = i.value()->logTextEdit;
		int index = ui.tabWidget->indexOf(logTextEdit);
		if(index >= 0)
		{
			ui.tabWidget->setCurrentIndex(index);
		}
	}

	workingHighlightText_ = true;

	ui.searchText->setText(searchText);

	logTextEdit->setText(sourceTextBuffer);

	logTextEdit->setFocus();

	if(searchText.isEmpty() == false) 
	{
		doHighlightText(searchText, ui.caseSensitiveCheck->isChecked());
	
		QTextDocument::FindFlags flags = 0x0;
		if(ui.caseSensitiveCheck->isChecked())
			flags |=  QTextDocument::FindCaseSensitively;

		logTextEdit->moveCursor(QTextCursor::Start);

		while(logTextEdit->find(searchText, flags))
		{
			break;
		}
	}

	workingHighlightText_ = false;
}