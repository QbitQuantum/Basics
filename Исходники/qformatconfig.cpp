/*!
	\brief Reset the subcontrols to reflect the data of the format scheme being edited
	
	The name can be a bit misleading at first, it has been chosen
	because it directly maps to the effect a "cancel" button would
	have on the widget
*/
void QFormatConfig::cancel()
{
	ui->m_table->clearContents();
	
	if ( m_currentScheme )
	{
		const int n = m_currentScheme->formatCount();
		
		ui->m_table->setRowCount(n);
		
		for ( int i = 0 ; i < n; ++i )
		{
			QString fid = m_currentScheme->id(i);
			const QFormat& fmt = m_currentScheme->formatRef(i);
			
			QTableWidgetItem *item;
			
			item = new QTableWidgetItem(fid);
			item->setFlags(Qt::ItemIsEnabled);
			ui->m_table->setItem(i, 0, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.weight == QFont::Bold ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Bold"));
			ui->m_table->setItem(i, 1, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.italic ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Italic"));
			ui->m_table->setItem(i, 2, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.underline ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Underline"));
			ui->m_table->setItem(i, 3, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.overline ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Overline"));
			ui->m_table->setItem(i, 4, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.strikeout ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Strikeout"));
			ui->m_table->setItem(i, 5, item);
			
			item = new QTableWidgetItem;
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			item->setCheckState(fmt.waveUnderline ? Qt::Checked : Qt::Unchecked);
			item->setToolTip(tr("Wave underline"));
			ui->m_table->setItem(i, 6, item);
			
			ui->m_table->setCellWidget(i, 7, new QSimpleColorPicker(fmt.foreground));
			ui->m_table->cellWidget(i, 7)->setToolTip(tr("Text color (aka foreground)"));
			//ui->m_table->cellWidget(i, 7)->setMaximumSize(22, 22);
			
			ui->m_table->setCellWidget(i, 8, new QSimpleColorPicker(fmt.background));
			ui->m_table->cellWidget(i, 8)->setToolTip(tr("Background color"));
			//ui->m_table->cellWidget(i, 8)->setMaximumSize(22, 22);
			
			ui->m_table->setCellWidget(i, 9, new QSimpleColorPicker(fmt.linescolor));
			ui->m_table->cellWidget(i, 9)->setToolTip(tr("Lines color (used by all lines formatting : underline, overline, ...)"));
			//ui->m_table->cellWidget(i, 9)->setMaximumSize(22, 22);
		}
	}
	
	ui->m_table->resizeColumnsToContents();
}