void ScriptParametersDialog::accept()
{
	int rowCount = ui->parameterTable->rowCount();

	QScriptEngine scriptEngine;

	mScript->removeAllParameters();

	for(int row = 0; row < rowCount; ++row)
	{
		QWidget *widget = ui->parameterTable->cellWidget(row, 0);
		if(!widget)
			continue;

		QLineEdit *nameLineEdit = qobject_cast<QLineEdit *>(widget);

		widget = ui->parameterTable->cellWidget(row, 1);
		if(!widget)
			continue;

		if(nameLineEdit->text().isEmpty())
			continue;

		QRegExp nameRegExp("[a-z_][a-z0-9_]*", Qt::CaseInsensitive);
		if(!nameRegExp.exactMatch(nameLineEdit->text()))
		{
			QMessageBox::warning(this, tr("Script parameter error"), tr("Incorrect parameter name \"%1\".")
				.arg(nameLineEdit->text()));
			nameLineEdit->setFocus();

			return;
		}

		bool isCode = false;
		QString value;

		switch(mParameterTypes.at(row))
		{
		case ActionTools::ScriptParameter::Text:
			{
				ActionTools::CodeLineEdit *valueWidget = qobject_cast<ActionTools::CodeLineEdit *>(widget);

				isCode = valueWidget->isCode();
				value = valueWidget->text();
			}
			break;
		case ActionTools::ScriptParameter::Number:
			{
				ActionTools::CodeSpinBox *valueWidget = qobject_cast<ActionTools::CodeSpinBox *>(widget);

				isCode = valueWidget->isCode();
				value = valueWidget->text();
			}
			break;
		case ActionTools::ScriptParameter::Window:
			{
				ActionTools::WindowEdit *valueWidget = qobject_cast<ActionTools::WindowEdit *>(widget);

				isCode = valueWidget->isCode();
				value = valueWidget->text();
			}
			break;
		case ActionTools::ScriptParameter::File:
			{
				ActionTools::FileEdit *valueWidget = qobject_cast<ActionTools::FileEdit *>(widget);

				isCode = valueWidget->isCode();
				value = valueWidget->text();
			}
			break;
		case ActionTools::ScriptParameter::Line:
			{
				ActionTools::LineComboBox *valueWidget = qobject_cast<ActionTools::LineComboBox *>(widget);

				isCode = valueWidget->isCode();
				value = valueWidget->codeLineEdit()->text();
			}
			break;
		}

		if(isCode)
		{
			QScriptSyntaxCheckResult result = scriptEngine.checkSyntax(value);
			if(result.state() != QScriptSyntaxCheckResult::Valid)
			{
				QMessageBox::warning(this, tr("Script parameter error"), tr("The script parameter named \"%1\" contains an error: \"%2\", please correct it.")
					.arg(nameLineEdit->text())
					.arg(result.errorMessage()));
				widget->setFocus();

				return;
			}
		}

		mScript->addParameter(ActionTools::ScriptParameter(nameLineEdit->text(), value, isCode, mParameterTypes.at(row)));
	}

	QDialog::accept();
}