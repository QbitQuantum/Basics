void FixtureManager::slotAutoFunction()
{
#if 0
	QTreeWidgetItem* item;
	t_fixture_id fxi_id;
	Fixture* fxi;

	item = m_tree->currentItem();
	if (item == NULL)
		return;

	fxi_id = item->text(KColumnID).toInt();
	fxi = _app->doc()->fixture(fxi_id);
	Q_ASSERT(fxi != NULL);

	// Loop over all channels
	for (int i = 0; i < fxi->channels(); i++)
	{
		QLCChannel* channel = fxi->channel(i);
		Q_ASSERT(channel != NULL);

		QListIterator <QLCCapability*> 
			cap_it(*channel->capabilities());

		// Loop over all capabilities
		while (cap_it.hasNext() == true)
		{
			QLCCapability* cap = cap_it.next();
			Q_ASSERT(cap != NULL);

			Scene* sc = static_cast<Scene*> 
				(_app->doc()->newFunction(Function::Scene,
							  fxi_id));
			sc->setName(channel->name() + " - " + cap->name());

			// Set the unused channels to NoSet and zero.
			for (int j = 0; j < fxi->channels(); j++)
				sc->set(j, 0, Scene::NoSet);

			// Set only the capability
			sc->set(i, (t_value) ((cap->min() + cap->max()) / 2),
				Scene::Set);
		}
	}
#endif
}