void EngineManagementWidget::configureEngine(const QModelIndex& index)
{
	// Map the index from the filtered model to the original model
	int row = m_filteredModel->mapToSource(index).row();
	const EngineConfiguration& config = m_engineManager->engineAt(row);

	QSet<QString> names = m_engineManager->engineNames();
	names.remove(config.name());

	auto dlg = new EngineConfigurationDialog(
		EngineConfigurationDialog::ConfigureEngine, this);
	dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg->applyEngineInformation(config);
	dlg->setReservedNames(names);

	connect(dlg, &EngineConfigurationDialog::accepted, [=]()
	{
		m_engineManager->updateEngineAt(row, dlg->engineConfiguration());
		m_hasChanged = true;
	});
	dlg->open();
}