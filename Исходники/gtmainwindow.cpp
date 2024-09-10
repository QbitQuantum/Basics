void GTMainWindow::createToolBars(){	
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->setFloatable(false);
	fileToolBar->setMovable(false);
	fileToolBar->setIconSize(QSize(25, 25));

	fileMenu =  new QMenu();
	fileMenu->addAction(newAct);

	fileMenu->addAction(openAct);

	fileMenu->addAction(saveAct);

	fileMenu->addAction(closeAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	QToolButton* toolButton = new QToolButton();
	toolButton->setIcon(QIcon(":/Resources/gt_icon.png"));
	toolButton->setMenu(fileMenu);
	toolButton->setPopupMode(QToolButton::InstantPopup);
	fileToolBar->addWidget(toolButton);

	fileToolBar->addSeparator();
	fileToolBar->addAction(newAct);

	fileToolBar->addAction(openAct);

	fileToolBar->addAction(saveAct);

	fileToolBar->addAction(closeAct);

	fileToolBar->addSeparator();

	//ui->gtStatusWidget->setParent(fileToolBar);
	//ui->gtStatusWidget->setVisible(false);
	//fileToolBar->addWidget(ui->gtStatusWidget);

	/*editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);*/
}