millionSec::millionSec()
{
    // Obtain a QMLDocument and load it into the qml variable, using build patterns.
    QmlDocument *qml = QmlDocument::create("asset:///home.qml");
    qml->setParent(this);
    qml->setContextProperty("home",this);


    NavigationPane *nav = qml->createRootObject<NavigationPane>();
    // If the QML document is valid, we process it.
    if (!qml->hasErrors()) {

        // Create the application Page from QMLDocument.
        //Page *appPage = qml->createRootObject<Page>();


        if (nav) {
            // Set the main scene for the application to the Page.
            Application::instance()->setScene(nav);
            //calculate();
            addApplicationCover();
        }
    }
}