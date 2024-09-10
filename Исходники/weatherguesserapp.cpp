WeatherGuesserApp::WeatherGuesserApp()
{
    // We set up the application Organization and name, this is used by QSettings
    // when saving values to the persistent store, in this app the home page is kept in the settings.
    QCoreApplication::setOrganizationName("Example");
    QCoreApplication::setApplicationName("Weather Guesser");

    // Here we create a QMLDocument and load it, we are using build patterns.
    QmlDocument *qml = QmlDocument::create().load("main.qml");
    qml->setParent(this);

    if (!qml->hasErrors()) {

        // The application navigationPane is created from QML.
        mNavigation = qml->createRootNode<NavigationPane>();

        if (mNavigation) {
            // Create the cities and weather page, these are pages which is not part of the
            // NavigationPane, the application will handle navigation to these.
            createCitiesPage();
            createWeatherPage();

            // Set up the favorite and home page, load models and connects to the appropriate signals.
            setUpFavoritesPage();
            setUpHomePage();

            // Connect to custom signals that will trigger navigation, defined in QML.
            Page *continents = mNavigation->findChild<Page*>("continents");
            connect(continents, SIGNAL(showContinentCities(QString)), this,
                    SLOT(onShowContinentCities(QString)));

            Page *favorites = mNavigation->findChild<Page*>("favorites");
            connect(favorites, SIGNAL(showWeather(QString)), this, SLOT(onShowWeather(QString)));

            connect(mContinentCitiesPage, SIGNAL(showWeather(QString)), this,
                    SLOT(onShowWeather(QString)));

            // Finally the main scene for the application is set to NavigationPane.
            Application::setScene(mNavigation);
        }
    }
}