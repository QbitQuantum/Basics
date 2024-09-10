Wt::WWidget* Tester::Title()
{
    Wt::WContainerWidget* container = new Wt::WContainerWidget();

    // Create a navigation bar with a link to a web page.
    Wt::WNavigationBar* navigation = new Wt::WNavigationBar(container);
    navigation->setTitle("LPeg Grammar Tester", "/");
    navigation->setResponsive(true);

    // Setup a Left-aligned menu.
    Wt::WMenu* leftMenu = new Wt::WMenu();
    navigation->addMenu(leftMenu);

    Wt::WPopupMenu* popup = new Wt::WPopupMenu();
    popup->setAutoHide(true, 250);
    popup->addItem("LPeg Documentation")->setLink(Wt::WLink("http://www.inf.puc-rio.br/~roberto/lpeg/lpeg.html"));
    Wt::WMenuItem* item = new Wt::WMenuItem("Documentation");
    item->setMenu(popup);
    leftMenu->addItem(item);

    popup = new Wt::WPopupMenu();
    popup->setAutoHide(true, 250);

    Wt::WMenuItem* pi = popup->addItem("date_time");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/date_time");
        HandleInternalPath(internalPath());
    }));

    pi = popup->addItem("common_log_format");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/clf");
        HandleInternalPath(internalPath());
    }));

    pi = popup->addItem("syslog");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/syslog");
        HandleInternalPath(internalPath());
    }));

    pi = popup->addItem("cbufd");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/cbufd");
        HandleInternalPath(internalPath());
    }));

    pi = popup->addItem("mysql");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/mysql");
        HandleInternalPath(internalPath());
    }));

    item = new Wt::WMenuItem("Modules");
    item->setMenu(popup);
    leftMenu->addItem(item);

    popup = new Wt::WPopupMenu();
    popup->setAutoHide(true, 250);

    pi = popup->addItem("Name-value lists");
    pi->setPathComponent("nvlist");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/nvlist");
        HandleInternalPath(internalPath());
    }));
    pi = popup->addItem("Split");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/split");
        HandleInternalPath(internalPath());
    }));
    pi = popup->addItem("CSV");
    pi->triggered().connect(std::bind([=]() {
        setInternalPath("/share/csv");
        HandleInternalPath(internalPath());
    }));
    item = new Wt::WMenuItem("Examples");
    item->setMenu(popup);
    leftMenu->addItem(item);

    return container;
}