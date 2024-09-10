void C4ConsoleQtLocalizeStringDlg::AddLanguagePressed()
{
	bool lang_ok = false;
	QRegExpValidator validator(QRegExp("^[a-zA-Z][a-zA-Z]$"), this);
	QString lang_id;
	while (!lang_ok)
	{
		bool ok; int q = 0;
		lang_id = QInputDialog::getText(this, LoadResStr("IDS_CNS_ADDLANGUAGE"), LoadResStr("IDS_CNS_ADDLANGUAGEID"), QLineEdit::Normal, QString(), &ok);
		if (!ok) return;
		lang_ok = (validator.validate(lang_id, q) == QValidator::Acceptable);
		if (!lang_ok)
		{
			DoError(LoadResStr("IDS_ERR_INVALIDLANGUAGEID"));
		}
	}
	// Either add or just focus existing editor
	QLineEdit *editor = GetEditorByLanguage(lang_id.toUtf8());
	if (!editor)
	{
		editor = AddEditor(lang_id.toUtf8(), nullptr);
		adjustSize();
		setMinimumSize(size());
	}
	editor->setFocus();
}