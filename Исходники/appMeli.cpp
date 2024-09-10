AppMeli::AppMeli(bb::cascades::Application *app) :
		QObject(app), m_model(new QListDataModel<QObject*>()) {

	// create scene document from main.qml asset
	// set parent to created document to ensure it exists for the whole application lifetime

	QmlDocument *qml = QmlDocument::create("asset:///main.qml");
	qml->setParent(this);
	//mNav = qml->createRootNode<NavigationPane>();

	qmlRegisterType<ImageLoader>();
	m_model->setParent(this);

	qml->setContextProperty("appContext", this);

	// create root object for the UI
	mNav = qml->createRootObject<NavigationPane>();
	// set created root object as a scene
	app->setScene(mNav);

}