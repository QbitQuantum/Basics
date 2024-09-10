bool CTextBrowser::eventFilter(QObject * o, QEvent * e)
{
	QWidget * scrollBar = ui->_textView->verticalScrollBar();
	if (o == scrollBar && e->type() == QEvent::Paint)
	{
		const int character = ui->_textView->cursorForPosition({ui->_textView->width() / 2, ui->_textView->height() / 2}).position();
		int currentChapterItemIndex = -1;

		for (int i = ui->_chaptersList->count() - 1; i >= 0; --i)
		{
			const int chapterStartCharacterIndex = ui->_chaptersList->item(i)->data(Qt::UserRole).toInt();
			if (chapterStartCharacterIndex < character)
			{
				currentChapterItemIndex = i;
				break;
			}
		}

		for (int i = 0, count = ui->_chaptersList->count(); i < count; ++i)
		{
			auto item = ui->_chaptersList->item(i);
			QFont f = item->font();
			f.setBold(i == currentChapterItemIndex);
			item->setFont(f);
			if (i == currentChapterItemIndex)
			{
				item->setTextColor(_backgroundColor);
				item->setBackgroundColor(_textColor);
			}
			else
			{
				item->setTextColor(_textColor);
				item->setBackgroundColor(_backgroundColor);
			}
		}

		if (currentChapterItemIndex >= 0)
			ui->_chaptersList->scrollToItem(ui->_chaptersList->item(currentChapterItemIndex));
	}
	else if (o == ui->_textView->viewport() && e->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(e);
		if (!_firstCharacterIndexForFragment.empty())
		{
			_controller.goToWord(wordIndexForGlobalCoordinates(static_cast<QWidget*>(o)->mapToGlobal(mouseEvent->pos())));
			accept();
		}
	}

	return QDialog::eventFilter(o, e);
}