void PopulatorDialog::populateButton_clicked()
{
	// Avoid QVariantList extension because it doesn't work for column names
	// containing special characters
	resultEdit->setHtml("");
	m_columnList.clear();
	for (int i = 0; i < columnTable->rowCount(); ++i)
		m_columnList.append(qobject_cast<PopulatorColumnWidget*>(columnTable->cellWidget(i, 2))->column());

	QList<QVariantList> values;
	foreach (Populator::PopColumn i, m_columnList)
	{
		switch (i.action)
		{
			case Populator::T_AUTO:
				values.append(autoValues(i));
				break;
			case Populator::T_AUTO_FROM:
				values.append(autoFromValues(i));
				break;
			case Populator::T_NUMB:
				values.append(numberValues(i));
				break;
			case Populator::T_TEXT:
				values.append(textValues(i));
				break;
			case Populator::T_PREF:
				values.append(textPrefixedValues(i));
				break;
			case Populator::T_STAT:
				values.append(staticValues(i));
				break;
			case Populator::T_DT_NOW:
			case Populator::T_DT_NOW_UNIX:
			case Populator::T_DT_NOW_JULIAN:
			case Populator::T_DT_RAND:
			case Populator::T_DT_RAND_UNIX:
			case Populator::T_DT_RAND_JULIAN:
				values.append(dateValues(i));
				break;
			case Populator::T_IGNORE:
				break;
		};
	}

	if (!execSql("SAVEPOINT POPULATOR;", tr("Cannot create savepoint")))
	{
		execSql("ROLLBACK TO POPULATOR;", tr("Cannot roll back after error"));
		return;
	}

	qlonglong cntPre, cntPost;
	resultEdit->clear();

	cntPre = tableRowCount();
	QSqlQuery query(QSqlDatabase::database(SESSION_NAME));
	for (int i = 0; i < spinBox->value(); ++i)
	{
		QStringList slr;
		for (int j = 0; j < values.count(); ++j)
		{
			slr.append(Utils::literal(values.at(j).at(i).toString()));
		}
		QString sql = QString("INSERT ")
					  + (constraintBox->isChecked() ? "OR IGNORE" : "")
					  + " INTO "
					  + Utils::quote(m_schema)
					  + "."
					  + Utils::quote(m_table)
					  + " ("
					  + sqlColumns()
					  + ") VALUES ("
					  + slr.join(",")
					  + ");";

		query.prepare(sql);
		if (!query.exec())
		{
			QString errtext = tr("Cannot insert values")
							  + ":<br/><span style=\" color:#ff0000;\">"
							  + query.lastError().text()
							  + "<br/></span>" + tr("using sql statement:")
							  + "<br/><tt>" + sql;
			resultAppend(errtext);
			if (!constraintBox->isChecked()) { break; }
		}
		else { updated = true; }
	}

	if (!execSql("RELEASE POPULATOR;", tr("Cannot release savepoint")))
	{
		if (!execSql("ROLLBACK TO POPULATOR;", tr("Cannot roll back either")))
		{
			resultAppend(tr(
				"Database may be left with a pending savepoint."));
		}
		updated = false;
		return;
	}

	cntPost = tableRowCount();

	if (cntPre != -1 && cntPost != -1)
		resultAppend(tr("Row(s) inserted: %1").arg(cntPost-cntPre));
}