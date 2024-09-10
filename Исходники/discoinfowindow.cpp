void DiscoInfoWindow::updateWindow()
{
	IDiscoInfo dinfo = FDiscovery->discoInfo(FStreamJid,FContactJid,FNode);

	int row = 0;
	ui.twtIdentity->clearContents();
	foreach(const IDiscoIdentity &identity, dinfo.identity)
	{
		ui.twtIdentity->setRowCount(row+1);
		ui.twtIdentity->setItem(row,0,new QTableWidgetItem(identity.category));
		ui.twtIdentity->setItem(row,1,new QTableWidgetItem(identity.type));
		ui.twtIdentity->setItem(row,2,new QTableWidgetItem(identity.name));
		row++;
	}
	ui.twtIdentity->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

	qSort(dinfo.features);
	ui.lwtFearures->clear();
	foreach(const QString &featureVar, dinfo.features)
	{
		IDiscoFeature dfeature = FDiscovery->discoFeature(featureVar);
		dfeature.var = featureVar;
		QListWidgetItem *listItem = new QListWidgetItem;
		listItem->setIcon(dfeature.icon);
		listItem->setText(dfeature.name.isEmpty() ? dfeature.var : dfeature.name);
		if (FDiscovery->hasFeatureHandler(featureVar))
		{
			QFont font = ui.lwtFearures->font();
			font.setBold(true);
			listItem->setData(Qt::FontRole,font);
		}
		listItem->setData(Qt::UserRole,dfeature.var);
		listItem->setData(Qt::UserRole+1,dfeature.description);
		ui.lwtFearures->addItem(listItem);
	}
	onCurrentFeatureChanged(ui.lwtFearures->currentItem(), NULL);

	if (FDataForms)
	{
		if (FFormMenu)
		{
			FFormMenu->deleteLater();
			FFormMenu = NULL;
		}
		if (!dinfo.extensions.isEmpty())
		{
			FFormMenu = new Menu(ui.pbtExtensions);
			for (int index=0; index<dinfo.extensions.count(); index++)
			{
				IDataForm form = FDataForms->localizeForm(dinfo.extensions.at(index));
				Action *action = new Action(FFormMenu);
				action->setData(ADR_FORM_INDEX,index);
				action->setText(!form.title.isEmpty() ? form.title : FDataForms->fieldValue("FORM_TYPE",form.fields).toString());
				connect(action,SIGNAL(triggered(bool)),SLOT(onShowExtensionForm(bool)));
				FFormMenu->addAction(action);
			}
		}
		ui.pbtExtensions->setMenu(FFormMenu);
		ui.pbtExtensions->setEnabled(FFormMenu!=NULL);
	}

	if (!dinfo.error.isNull())
	{
		ui.lblError->setText(tr("Error: %1").arg(dinfo.error.errorMessage()));
		ui.twtIdentity->setEnabled(false);
		ui.lwtFearures->setEnabled(false);
		ui.lblError->setVisible(true);
	}
	else
	{
		ui.twtIdentity->setEnabled(true);
		ui.lwtFearures->setEnabled(true);
		ui.lblError->setVisible(false);
	}

	ui.twtIdentity->horizontalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);
	ui.twtIdentity->horizontalHeader()->setResizeMode(1,QHeaderView::ResizeToContents);
	ui.twtIdentity->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);

	ui.pbtUpdate->setEnabled(true);
}