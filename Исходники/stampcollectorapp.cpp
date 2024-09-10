StampCollectorApp::StampCollectorApp()
{
    // The entire UI is a drill down list, which means that when an item is selected
    // a navigation takes place to a Content View with a large stamp image and a descriptive text.
    // The main.qml contain the navigation pane and the first page (the list).
    QmlDocument *qml = QmlDocument::create().load("main.qml");
    qml->setParent(this);
    mNav = qml->createRootNode<NavigationPane>();

    // We get the ListView from QML, so that we can connect to the selctionChange signal and set
    // up a DataModel for JSON data.
    ListView *stampList = mNav->findChild<ListView*>("stampList");
    setUpStampListModel(stampList);
    QObject::connect(stampList, SIGNAL(selectionChanged(const QVariantList, bool)), this,
            SLOT(onSelectionChanged(const QVariantList, bool)));

    // The second page, with a detailed description and large stamp image is set up in QML
    // Navigation to this page is handled in the onSelectionChanged Slot function.
    QmlDocument *contentQml = QmlDocument::create().load("ContentPage.qml");
    contentQml->setParent(this);
    mQmlContext = contentQml->documentContext();

    // Set up a context property to the navigation pane so that it is possible to navigate back to the list
    // and create the content page.
    mQmlContext->setContextProperty("_nav", mNav);
    mContentPage = contentQml->createRootNode<Page>();

    // Create the application scene and we are done.
    Application::setScene(mNav);
}