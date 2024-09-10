void ClassSpaceChecker::search(const QString & searchName, const QString & searchText, 
							bool useUncryptName, 
							bool ignoreInnerClass, 
							bool onlyAnonymousClass, 
							bool useAsPackageName) 
{
	if(classList_.size() <= 0)
		return;

	ui.tableWidgetResult->clearContents();
	ui.tableWidgetResult->setRowCount(0);
	ui.tableWidgetResult->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

	long totalSize = 0;
	int rowCount = 0;
	int methodCount = 0;
	QList<ClassFileContext*>::iterator it = classList_.begin();
	for(; it != classList_.end(); it++)
	{
		int col = 0;
		const ClassFileContext* ctx = *it;

		int markPos = ctx->originalName.indexOf("$");
		if(ignoreInnerClass && markPos > 0)
			continue;

		if(onlyAnonymousClass) 
		{
			QString right = ctx->originalName.mid(markPos + 1);
			int anonymousId = right.toUInt();
			if(anonymousId <= 0) 
				continue;
		}

		if(useAsPackageName)
		{
			int posTemp = ctx->originalName.indexOf(searchName);
			if(posTemp < 0)
				continue;
			posTemp = ctx->originalName.indexOf(".", posTemp + searchName.length() + 1);
			if(posTemp > 0)
				continue;
		}
		else 
		{
			if(searchName.isEmpty() == false)
			{
				if(useUncryptName)
				{
					if(ctx->originalName.contains(QRegExp(searchName, Qt::CaseInsensitive)) == false)
						continue;
				}
				else
				{
					if(ctx->className.contains(QRegExp(searchName, Qt::CaseInsensitive)) == false)
						continue;
				}
			}
		}

		if(searchText.isEmpty() == false)
		{
			if(ctx->javaFileFlag) 
			{
				QString decompiledBufferStr = ctx->decompiledBuffer;
				if(decompiledBufferStr.contains(QRegExp(searchText, Qt::CaseSensitive)) == false)
					continue;
			}
			else
			{
				if(ctx->decompiledBuffer.contains(searchText.toStdString().c_str()) == false)
					continue;
			}
		}

		QString space = QString::number(ctx->fileSize);

		ui.tableWidgetResult->insertRow(rowCount);

		QTableWidgetItem *itemOriginal = new QTableWidgetItem(ctx->className);
		itemOriginal->setFlags(itemOriginal->flags() & ~Qt::ItemIsEditable);
		itemOriginal->setData(Qt::UserRole, qVariantFromValue((void *)ctx));
		ui.tableWidgetResult->setItem(rowCount, col++, itemOriginal);

		QTableWidgetItem *itemSize = new QTableWidgetItem();
		itemSize->setData(Qt::DisplayRole, ctx->fileSize);
		itemSize->setFlags(itemSize->flags() & ~Qt::ItemIsEditable);
		ui.tableWidgetResult->setItem(rowCount, col++, itemSize);

		QString uncryptName = ctx->originalName;
		if(currentMapPath_.isEmpty())
			uncryptName = "-";
		QTableWidgetItem *itemUncrypt = new QTableWidgetItem(uncryptName);
		itemUncrypt->setFlags(itemUncrypt->flags() & ~Qt::ItemIsEditable);
		ui.tableWidgetResult->setItem(rowCount, col++, itemUncrypt);
		
		QTableWidgetItem *itemMethodCount = new QTableWidgetItem();
		itemMethodCount->setData(Qt::DisplayRole, ctx->methodCount);
		itemMethodCount->setFlags(itemMethodCount->flags() & ~Qt::ItemIsEditable);
		ui.tableWidgetResult->setItem(rowCount, col++, itemMethodCount);

		QTableWidgetItem *itemRefCount = new QTableWidgetItem();
		itemRefCount->setData(Qt::DisplayRole, ctx->referencedCount);
		itemRefCount->setFlags(itemRefCount->flags() & ~Qt::ItemIsEditable);
		ui.tableWidgetResult->setItem(rowCount, col++, itemRefCount);

		rowCount++;

		methodCount += ctx->methodCount;
		totalSize += ctx->fileSize;
	}

	QString resultStr;
	resultStr += "Total : ";
	resultStr += QString::number(rowCount);
	resultStr += " class found, ";
	resultStr += numberDot(QString::number(totalSize));
	resultStr += " bytes, ";
	resultStr += QString::number(methodCount);
	resultStr += " methods found";

	ui.lineEdit_Result->setText(resultStr);

	ui.tableWidgetResult->sortItems(0, Qt::AscendingOrder);
	ui.tableWidgetResult->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

	prevTotalResultStr_ = resultStr;
}