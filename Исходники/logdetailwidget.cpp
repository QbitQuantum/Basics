void LogDetailWidget::showEditHistory()
{
	QModelIndex index = ui.aaView->currentIndex();
	if(index.row() <0) return;

	QAbstractItemModel* model = ui.aaView->model();

	QString timestamp = model->data(model->index(index.row(), 0), Qt::DisplayRole).toString();
	QString compName = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
	QString type = model->data(model->index(index.row(), 4), Qt::DisplayRole).toString();
	QString value = model->data(model->index(index.row(), 5), Qt::DisplayRole).toString();

	QWidget *histWidget = new QWidget;
	histWidget->resize(QSize(800,600));
	QVBoxLayout *boxlayout = new QVBoxLayout;
	QScrollArea* area = new QScrollArea;
	QGridLayout *gridLayout = new QGridLayout;
	QLabel* fileLabel = new QLabel;
	fileLabel->setText("Source Code File: " + compName);
	gridLayout->addWidget(fileLabel, 0, 0, 1, -1);
	histWidget->setLayout(boxlayout);
	boxlayout->addWidget(area);
	area->setLayout(gridLayout);
	
	LogEvent pre_e;
	bool isFirst = true;
	int row = 1;
	for(int i=0; i<logMan.events.size(); i++)
	{
		LogEvent e = logMan.events[i];
		if(!e.isHasAcc) continue;
		
		if(e.acc.parent_name == compName.toStdString() && e.acc.type == type.toStdString())
		{
			if(isFirst)
			{
				QLabel* timeLabel = new QLabel;
				timeLabel->setText(QString::fromStdString(e.timestamp));
				QLabel* edit = new QLabel;
				edit->setText("First Time Open");
				gridLayout->addWidget(timeLabel, row, 0, 1, 1);
				gridLayout->addWidget(edit, row, 1, 1, 1);
				isFirst = false;
			}
			else
			{
				QLabel* timeLabel = new QLabel;
				timeLabel->setText(QString::fromStdString(e.timestamp));
				gridLayout->addWidget(timeLabel, row, 0, 1, 1);

				string s1 = pre_e.acc.value;
				replaceAll(s1, "\\n", "\n");
				replaceAll(s1, "\\t", "\t");

				string s2 = e.acc.value;
				replaceAll(s2, "\\n", "\n");
				replaceAll(s2, "\\t", "\t");

				QString str1 = QString::fromStdString(s1);
				QString str2 = QString::fromStdString(s2);

				diff_match_patch dmp;
				QList<Diff> res =  dmp.diff_main(str1,str2, true);
				dmp.diff_cleanupSemantic(res);
				if(res.size() == 1 && res[0].operation == Operation::EQUAL)
				{
					QLabel* edit = new QLabel;
					edit->setText("No Difference");
					gridLayout->addWidget(edit, row, 1, 1, 1);
				}
				else
				{
					QTextEdit* edit = new QTextEdit;
					edit->setText(dmp.diff_toString(res));
					gridLayout->addWidget(edit, row, 1, 1, 1);
				}			
				
			}

			pre_e = e;
			row++;
		}
	}

	histWidget->show();
}