void CapabilityWizard::slotCreateCapabilities()
{
	int start = m_startSpin->value();
	int gap = m_gapSpin->value();
	int amount = m_amountSpin->value();
	QString name = m_nameEdit->text();
	t_value min = start;
	t_value max = min + gap;
	QLCCapability* cap;

	/* Destroy existing capabilities */
	foreach (QLCCapability* cap, m_caps)
		delete cap;
	m_caps.clear();

	/* Create new capabilities */
	for (int i = 0; i < amount; i++)
	{
		/* Create a name with the optional hash mark */
		QString modname(name);
		modname.replace("#", QString("%1").arg(i + 1));

		/* Create a new capability and add it to our list */
		cap = new QLCCapability(min, max, modname);
		m_caps << cap;

		/* Bail out when the maximum DMX value has been reached */
		if (max == 255)
			break;

		/* Increment for the next round */
		min = max + 1;
		max = min + gap;

		/* Bail out if next round would overflow */
		if (max < min)
			break;
	}

	/* Replace capabilities in the list widget */
	m_list->clear();
	foreach (cap, m_caps)
	{
		QListWidgetItem* item;
		item = new QListWidgetItem(m_list);
		item->setText(QString("[%1 - %2] %3").arg(cap->min())
				.arg(cap->max()).arg(cap->name()));

		if (m_channel->searchCapability(cap->min()) != NULL ||
		    m_channel->searchCapability(cap->max()) != NULL)
		{
			/* Disable the item to indicate overlapping */
			item->setFlags(0);
		}
	}