void OsgEarth::initialize()
{
    // TOOO not thread safe...
    if (initialized) {
        return;
    }
    initialized = true;

    qDebug() << "OsgEarth::initialize - initializing osgearth...";

    // increase cache (default is 300);
    // setenv("OSG_MAX_PAGEDLOD", "500", 0);

    // setenv("OSG_ASSIGN_PBO_TO_IMAGES", "on", 0);

    // Number of threads in the DatbasePager set up, inclusive of the number of http dedicated threads.
    osg::DisplaySettings::instance()->setNumOfDatabaseThreadsHint(6);
    osg::DisplaySettings::instance()->setNumOfHttpDatabaseThreadsHint(3);

    initializePathes();

    initWindowingSystem();

    initializeCache();

    // force early initialization of osgEarth capabilities
    // Doing this too early (before main window is displayed) causes rendering glitches (black holes)
    // Not sure why... See OSGViewport for when it is called (late...)
    osgEarth::Registry::capabilities();

    displayInfo();
}