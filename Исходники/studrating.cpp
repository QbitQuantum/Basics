studrating::studrating(QWidget *parent, Qt::WindowFlags flags): QMainWindow(parent, flags), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	manager = new StudRatingManager(this);
	dbFilePath = QString();
	disciplinModel = new QStringListModel(this);
	ui->disciplinsListView->setModel(disciplinModel);
	
	
	createDbDialog = new CreateDbDialog(this);
	studentListDialog = new StudentListDialog(this);
	addDateDialog = new AddDateDialog(this);
	
	htmlGenerator = new HtmlGenerator(this);
	
	settings = new QSettings( QSettings::NativeFormat, QSettings::UserScope, APP_NAME, QString(), this);
	readSettings();
	
	if(!dbFilePath.isEmpty())
	{
		if(manager->loadDB(dbFilePath))
		{
			ui->dbFilePathEdit->setText(dbFilePath);
			ui->aboutDbTextEdit->setPlainText(manager->getAboutDB());
			ui->label_14->setVisible(false);
			setWindowTitle(APP_NAME + "-" + VERSION + " - " + dbFilePath);
		}
		else
		{
			QMessageBox::warning(this, trUtf8("Загрузка базы данных"), trUtf8("Не возможно загрузить файл ") + dbFilePath);
			dbFilePath.clear();
		}
	}
	
	createIcon();
	if(!dbFilePath.isEmpty())
	{
		if(manager->groupsIsEmpty() || manager->disciplinsIsEmpty())
		{
			for(int i = 3; i <= 5; i++)
			{
				Qt::ItemFlags flags =  ui->contentsWidget->item(i)->flags();
				ui->contentsWidget->item(i)->setFlags(flags ^ Qt::ItemIsEnabled);
			}
		}
	}
	else
	{
		for(int i = 1; i <= 5; i++)
		{
			Qt::ItemFlags flags =  ui->contentsWidget->item(i)->flags();
			ui->contentsWidget->item(i)->setFlags(flags ^ Qt::ItemIsEnabled);
		}
	}
	
	ui->pagesWidget->setCurrentIndex(currentPageIndex);
	ui->contentsWidget->setCurrentRow(currentPageIndex);
	
	connect(ui->actionAboutQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}