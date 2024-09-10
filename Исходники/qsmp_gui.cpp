int main(int argc, char **argv)
{
  using namespace qsmp;
  using boost::bind;
  using boost::filesystem::recursive_directory_iterator;
  namespace io = boost::iostreams;
    qInstallMsgHandler(&QsmpQtMsgHandler);

    time_t current_time = std::time(NULL);
    LOG("Seed") << current_time;
    srand(current_time);

    QApplication app(argc, argv);
    app.setApplicationName("SMPMediaPlayer");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationName("Foobar NZ");
    app.setOrganizationDomain("foobar.co.nz");

    //Cache::lease();

    std::string path = (argc > 1) ? argv[1] : "";

    std::vector<Media> paths;
    std::copy(recursive_directory_iterator(path),
              recursive_directory_iterator(),
              valueOutputFilterIterator<recursive_directory_iterator::value_type>(
                  testExtension(
                      equals(".mp3",boost::is_iequal())
                    ),
                  std::back_inserter(paths)));

    sort(paths,MetadataType_FileName,SortingOrder_Ascending);

    typedef boost::iterator_range<std::vector<Media>::iterator> Range_t;

    PlayerHistory history;
    Player player(bind(&PlayerHistory::GetPlayerNext,&history));
    history.SetNextCallback(bind(&chooseRandom<Range_t>,boost::ref(paths)));
    history.SetPlayer(&player);

    QSplitter* view_splitter = new QSplitter;
    QLayout*  view_layout = new QHBoxLayout;
    QWidget*  dummy_view_widget = new QWidget;
    QLayout*  dummy_view_layout = new QVBoxLayout;
    ViewTree* views = new ViewTree(dummy_view_layout);

    view_layout->addWidget(view_splitter);
    view_splitter->addWidget(views);
    view_splitter->addWidget(dummy_view_widget);
    dummy_view_widget->setLayout(dummy_view_layout);

    views->model()->AddNewView("History", new LayoutWidget<QVBoxLayout>(new HistoryView(&history),
                                                                        new PlayerControl(&player, &history)));
    views->model()->AddNewView("Cache", new CacheView("40bc33055c2f91d8e5690907b573eee95e5c6107"));

#ifdef WIN32
    HotkeyWindow window;

    window.RegisterHotkeys();

    QObject::connect(&window, SIGNAL(OnPrevious()), &history, SLOT(Previous()));
    QObject::connect(&window, SIGNAL(OnNext()), &history, SLOT(Next()));
    QObject::connect(&window, SIGNAL(OnPlayPause()), &player, SLOT(PlayPause()));
    QObject::connect(&window, SIGNAL(OnStop()), &player, SLOT(Stop()));
#else
    QWidget window;
#endif

    window.setLayout(view_layout);
    window.show();

    //LuaTcpServer lua;

    return app.exec();
}