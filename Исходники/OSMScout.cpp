int main(int argc, char* argv[])
{
#ifdef Q_WS_X11
  QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
#endif

  QGuiApplication app(argc,argv);
  SettingsRef     settings;
  MainWindow      *window;
  int             result;

#ifdef __UBUNTU__
  QString appId = getenv("APP_ID");
  appId = appId.split("_")[0];
#else
  QString appId = "osmscout.fransschreuder";
#endif
  app.setOrganizationName(appId);
  app.setOrganizationDomain(appId);
  app.setApplicationName(appId.split(".")[0]);


  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
          QLibraryInfo::location(QLibraryInfo::TranslationsPath));

  app.installTranslator(&qtTranslator);

  QTranslator myappTranslator;
  myappTranslator.load("osmscout_" + QLocale::system().name(), ":/po");

  app.installTranslator(&myappTranslator);

  //qRegisterMetaType<RenderMapRequest>();
  qRegisterMetaType<DatabaseLoadedResponse>();

  qmlRegisterType<MapWidget>("net.sf.libosmscout.map", 1, 0, "Map");
  qmlRegisterType<Location>("net.sf.libosmscout.map", 1, 0, "Location");
  qmlRegisterType<LocationListModel>("net.sf.libosmscout.map", 1, 0, "LocationListModel");
  qmlRegisterType<RouteStep>("net.sf.libosmscout.map", 1, 0, "RouteStep");
  qmlRegisterType<RoutingListModel>("net.sf.libosmscout.map", 1, 0, "RoutingListModel");
  qmlRegisterType<MapListModel>("net.sf.libosmscout.map", 1, 0, "MapListModel");
  qmlRegisterType<DownloadListModel>("net.sf.libosmscout.map", 1, 0, "DownloadListModel");
  qmlRegisterType<DownloadDirListModel>("net.sf.libosmscout.map", 1, 0, "DownloadDirListModel");

  qmlRegisterSingletonType<Theme>("net.sf.libosmscout.map", 1, 0, "Theme", ThemeProvider);
  qmlRegisterType<DownloadManager>("net.sf.libosmscout.map", 1, 0, "DownloadManager");
  qmlRegisterType<UnityScreen>("net.sf.libosmscout.map", 1, 0, "UnityScreen");

  osmscout::log.Debug(true);

  QThread thread;

  if (!DBThread::InitializeInstance()) {
    std::cerr << "Cannot initialize DBThread" << std::endl;
  }

  DBThread* dbThread=DBThread::GetInstance();

  window=new MainWindow(settings,
                        dbThread);
  dbThread->connect(&thread, SIGNAL(started()), SLOT(Initialize()));
  dbThread->connect(&thread, SIGNAL(finished()), SLOT(Finalize()));

  dbThread->moveToThread(&thread);
  thread.start();

  result=app.exec();

  delete window;

  thread.quit();
  thread.wait();

  DBThread::FreeInstance();

  return result;
}