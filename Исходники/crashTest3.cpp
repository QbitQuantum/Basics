void CrashTestPlugin3::domenu(const QString &menu_name, V3DPluginCallback &callback, QWidget *parent)
{
	myCallback = &callback;
	sourceWindow = callback.currentImageWindow();
	sourceImage = callback.getImage(sourceWindow);

	myDialog = new QDialog(parent);
	QPushButton* processButton     = new QPushButton("process a black image test");
	QPushButton* restoreButton     = new QPushButton("Restore");

	QFormLayout *formLayout = new QFormLayout( myDialog );
	formLayout->addRow( processButton , restoreButton );

	myDialog->connect(processButton, SIGNAL(clicked()), this, SLOT( processBlackImage() ));
	myDialog->connect(restoreButton, SIGNAL(clicked()), this, SLOT( restore() ));

	copyImage();

	myDialog->exec();
}