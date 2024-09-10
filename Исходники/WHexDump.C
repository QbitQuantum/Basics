void
WHexDump::init() {
    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout;
    setLayout(vbox);

    Wt::WContainerWidget *actionsBox = new Wt::WContainerWidget;
    vbox->addWidget(actionsBox);
    {
        new Wt::WText("Goto: ", actionsBox);
        wAddressEdit_ = new Wt::WLineEdit(actionsBox);
        wAddressEdit_->enterPressed().connect(this, &WHexDump::handleGoto);

        new Wt::WBreak(actionsBox);
        new Wt::WText("Search: ", actionsBox);
        wSearchEdit_ = new Wt::WLineEdit(actionsBox);
        wSearchEdit_->keyPressed().connect(this, &WHexDump::resetSearch);
        wSearchNext_ = new Wt::WPushButton("Find", actionsBox);
        wSearchNext_->clicked().connect(this, &WHexDump::handleSearch);
        wSearchResults_ = new Wt::WText("Enter a big-endian hexadecimal value", actionsBox);
        
    }

    Wt::WContainerWidget *tableContainer = new Wt::WContainerWidget;
    vbox->addWidget(tableContainer, 1 /*stretch*/);
    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout;        // so the table scrolls horizontally
    tableContainer->setLayout(hbox);

    model_ = new HexDumpModel;

    tableView_ = new Wt::WTableView;
    tableView_->setModel(model_);
    tableView_->setRowHeaderCount(1);                   // this must be first property set
    tableView_->setHeaderHeight(28);
    tableView_->setSortingEnabled(false);
    tableView_->setAlternatingRowColors(false);         // true interferes with our blacking out unmapped addresses
    tableView_->setColumnResizeEnabled(true);
    tableView_->setSelectionMode(Wt::SingleSelection);
    tableView_->setEditTriggers(Wt::WAbstractItemView::NoEditTrigger);
    tableView_->setColumnWidth(addressColumn, Wt::WLength(6, Wt::WLength::FontEm));
    tableView_->setColumnWidth(sep1Column, Wt::WLength(1, Wt::WLength::FontEm));
    tableView_->setColumnWidth(sep2Column, Wt::WLength(1, Wt::WLength::FontEm));
    for (size_t i=0; i<bytesPerRow; ++i) {
        int extra = 7==i%8 && i+1<bytesPerRow ? 1 : 0;
        tableView_->setColumnWidth(bytesColumn + i, Wt::WLength(2+extra, Wt::WLength::FontEm));
        tableView_->setColumnWidth(asciiColumn + i, Wt::WLength(2+extra, Wt::WLength::FontEm));
    }
    tableView_->clicked().connect(boost::bind(&WHexDump::handleClick, this, _1));
    hbox->addWidget(tableView_);
}