QObject *QuickGenerator::generateHelper() const
{
	ServicePointer<ApplicationWindow> app;
	QString filePath = ThemeManager::path(QLatin1String("declarative"),
										  QLatin1String("meego"));
	QUrl url = QUrl::fromLocalFile(filePath + QLatin1Char('/') + m_component);
	QDeclarativeComponent component(app->engine(), url);
	qDebug() << url << component.isLoading() << component.isError() << component.errorString();
	QObject *settingsPage = component.beginCreate(app->engine()->rootContext());
	if (m_creator) {
		QObject *object = m_creator->create();
		object->setParent(settingsPage);
		settingsPage->setProperty("object", qVariantFromValue(object));
	}
	component.completeCreate();
	return settingsPage;
}