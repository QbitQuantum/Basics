bool AddressWidget::eventFilter(QObject *object, QEvent *event)
{
	if (object == m_bookmarkLabel && m_bookmarkLabel && event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

		if (mouseEvent && mouseEvent->button() == Qt::LeftButton)
		{
			if (m_bookmarkLabel->isEnabled())
			{
				if (BookmarksManager::hasBookmark(getUrl()))
				{
					BookmarksManager::deleteBookmark(getUrl());
				}
				else
				{
					BookmarkInformation *bookmark = new BookmarkInformation();
					bookmark->url = getUrl().toString(QUrl::RemovePassword);
					bookmark->title = m_window->getTitle();
					bookmark->type = UrlBookmark;

					BookmarkPropertiesDialog dialog(bookmark, -1, this);

					if (dialog.exec() == QDialog::Rejected)
					{
						delete bookmark;
					}
				}

				updateBookmark();
			}

			return true;
		}
	}

	if (object != this && event->type() == QEvent::ContextMenu)
	{
		QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent*>(event);

		if (contextMenuEvent)
		{
			QMenu menu(this);
			QAction *action = menu.addAction(tr("Remove This Icon"), this, SLOT(removeIcon()));
			action->setData(object->objectName());

			menu.exec(contextMenuEvent->globalPos());

			contextMenuEvent->accept();

			return true;
		}
	}

	if (object == this && event->type() == QEvent::KeyPress && m_window)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Escape)
		{
			const QUrl url = m_window->getUrl();

			if (text().trimmed().isEmpty() || text().trimmed() != url.toString())
			{
				setText((url.scheme() == QLatin1String("about") && m_window->isUrlEmpty()) ? QString() : url.toString());

				if (!text().trimmed().isEmpty() && SettingsManager::getValue(QLatin1String("AddressField/SelectAllOnFocus")).toBool())
				{
					QTimer::singleShot(0, this, SLOT(selectAll()));
				}
			}
			else
			{
				m_window->setFocus();
			}
		}
	}

	return QLineEdit::eventFilter(object, event);
}