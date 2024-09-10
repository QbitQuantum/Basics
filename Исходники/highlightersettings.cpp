void HighlighterSettings::saveImpl()
{
	Config cfg;
	cfg.beginGroup(QLatin1String("highlighter"));
	cfg.setValue("enableAutoHighlights", ui.enableAutoHighlights->isChecked());

	int count = cfg.beginArray(QLatin1String("regexps"));
	for (int i = 0; i < m_items.size(); i++) {
		cfg.setArrayIndex(i);
		HighlighterItemList *item = m_items.at(i);
		cfg.setValue(QLatin1String("regexp"), item->regexp());
	}
	for (int i = count - 1; i >= m_items.size(); --i)
		cfg.remove(i);
	cfg.endGroup();
}