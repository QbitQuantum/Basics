void CookiesContentsWidget::addCookie(const QNetworkCookie &cookie)
{
	const QString domain = (cookie.domain().startsWith('.') ? cookie.domain().mid(1) : cookie.domain());
	QStandardItem *domainItem = findDomain(domain);

	if (domainItem)
	{
		for (int i = 0; i < domainItem->rowCount(); ++i)
		{
			if (domainItem->child(i, 0)->text() == cookie.name() && domainItem->child(i, 0)->data(Qt::UserRole).toString() == cookie.path())
			{
				return;
			}
		}
	}
	else
	{
		domainItem = new QStandardItem(HistoryManager::getIcon(QUrl(QStringLiteral("http://%1/").arg(domain))), domain);
		domainItem->setToolTip(domain);

		m_model->appendRow(domainItem);

		if (sender())
		{
			m_model->sort(0);
		}
	}

	QStandardItem *cookieItem = new QStandardItem(QString(cookie.name()));
	cookieItem->setData(cookie.path(), Qt::UserRole);
	cookieItem->setData(cookie.domain(), (Qt::UserRole + 1));
	cookieItem->setToolTip(cookie.name());
	cookieItem->setFlags(cookieItem->flags() | Qt::ItemNeverHasChildren);

	domainItem->appendRow(cookieItem);
	domainItem->setText(QStringLiteral("%1 (%2)").arg(domain).arg(domainItem->rowCount()));
}