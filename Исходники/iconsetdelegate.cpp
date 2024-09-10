void IconsetDelegate::paint(QPainter *APainter, const QStyleOptionViewItem &AOption, const QModelIndex &AIndex) const
{
	QString name = AIndex.data(IDR_STORAGE).toString();
	QString subdir = AIndex.data(IDR_SUBSTORAGE).toString();

	IconStorage *storage = FStorages.value(name).value(subdir);
	if (storage==NULL && !name.isEmpty() && !subdir.isEmpty())
	{
		storage = new IconStorage(name,subdir);
		FStorages[name].insert(subdir,storage);
	}

	if (storage != NULL)
	{
		QStyleOptionViewItemV4 indexOption = indexStyleOption(AOption,AIndex);

#if defined(Q_WS_WIN) && !defined(QT_NO_STYLE_WINDOWSVISTA)
		QStyle *style = indexOption.widget ? indexOption.widget->style() : QApplication::style();
		if (qobject_cast<QWindowsVistaStyle *>(style))
		{
			indexOption.palette.setColor(QPalette::All, QPalette::HighlightedText, indexOption.palette.color(QPalette::Active, QPalette::Text));
			indexOption.palette.setColor(QPalette::All, QPalette::Highlight, indexOption.palette.base().color().darker(108));
		}
#endif

		APainter->save();
		APainter->setClipping(true);
		APainter->setClipRect(indexOption.rect);

		drawBackground(APainter,indexOption);

		int space = 2;
		QRect drawRect = indexOption.rect.adjusted(space,space,-space,-space);

		if (!AIndex.data(IDR_HIDE_STORAGE_NAME).toBool())
		{
			QRect ceckRect(drawRect.topLeft(),checkButtonRect(indexOption,drawRect,AIndex.data(Qt::CheckStateRole)).size());
			drawCheckButton(APainter,indexOption,ceckRect,static_cast<Qt::CheckState>(AIndex.data(Qt::CheckStateRole).toInt()));
			drawRect.setLeft(ceckRect.right()+space);

			QString displayText = storage->storageProperty(FILE_STORAGE_NAME,name+"/"+subdir);
			QRect textRect(drawRect.topLeft(),indexOption.fontMetrics.size(Qt::TextSingleLine,displayText));

			QPalette::ColorGroup cg = indexOption.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
			if (cg == QPalette::Normal && !(indexOption.state & QStyle::State_Active))
				cg = QPalette::Inactive;
			if (indexOption.state & QStyle::State_Selected)
				APainter->setPen(indexOption.palette.color(cg, QPalette::HighlightedText));
			else
				APainter->setPen(indexOption.palette.color(cg, QPalette::Text));
			APainter->drawText(textRect,indexOption.displayAlignment,displayText);

			drawRect.setTop(textRect.bottom() + space);
			drawRect.setLeft(indexOption.rect.left() + space);
		}

		int maxRows = AIndex.data(IDR_ICON_ROW_COUNT).isValid() ? AIndex.data(IDR_ICON_ROW_COUNT).toInt() : DEFAULT_ICON_ROW_COUNT;

		int row = 0;
		int column = 0;
		int iconIndex = 0;
		int left = drawRect.left();
		int top = drawRect.top();
		QList<QString> iconKeys = storage->fileFirstKeys();
		while (drawRect.bottom()>top && drawRect.right()>left && iconIndex<iconKeys.count() && row<maxRows)
		{
// *** <<< eyeCU <<< ***
			bool filtered=false;
			for (QStringList::ConstIterator it=FFilter.constBegin(); it!=FFilter.constEnd(); ++it)
				if (iconKeys.at(iconIndex).endsWith(*it))
				{
					filtered=true;
					break;
				}
			if (!filtered)
			{
// *** >>> eyeCU >>> ***
			QIcon icon = storage->getIcon(iconKeys.at(iconIndex));
			if (!icon.isNull())
			{
				QPixmap pixmap = icon.pixmap(indexOption.decorationSize,QIcon::Normal,QIcon::On);
				APainter->drawPixmap(left,top,pixmap);
				left += indexOption.decorationSize.width()+space;
			}
			// *** <<< eyeCU >>> ***
			column++;

			if (left >= drawRect.right()-indexOption.decorationSize.width())
			{
				column = 0;
				left = drawRect.left();
				top += indexOption.decorationSize.height()+space;
			}
// *** <<< eyeCU <<< ***
			}
			iconIndex++;
// *** >>> eyeCU >>> ***
		}

		drawFocusRect(APainter,indexOption,indexOption.rect);

		APainter->restore();
	}
	else
	{
		QStyledItemDelegate::paint(APainter,AOption,AIndex);
	}
}