void NewGameDialog::configureBlackEngine()
{
	EngineConfigurationDialog dlg(EngineConfigurationDialog::ConfigureEngine, this);

	int i = selectedEngineIndex(Chess::Side::Black);
	const EngineConfiguration& config = m_engineManager->engineAt(i);
	dlg.applyEngineInformation(config);

	QSet<QString> names = m_engineManager->engineNames();
	names.remove(config.name());
	dlg.setReservedNames(names);

	if (dlg.exec() == QDialog::Accepted)
		m_engineManager->updateEngineAt(i, dlg.engineConfiguration());
}