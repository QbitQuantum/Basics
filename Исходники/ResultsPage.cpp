///
//  Constructor
//
ResultsPage::ResultsPage(const MRIBrowser *mriBrowser, WContainerWidget *parent) :
    mMRIBrowser(mriBrowser),
    WContainerWidget(parent)
{
    setStyleClass("tabdiv");

    mResultsTable = new ResultsTable();

    WContainerWidget *browserContainer = new WContainerWidget();
    WContainerWidget *resultsContainer = new WContainerWidget;

    WText *showText = new WText("Show Results by User:"******"<user>");
    mUserComboBox->addItem("All");

    mSearchLineEdit = new WLineEdit("");
    mSearchLineEdit->setMinimumSize(150, WLength::Auto);
    mSearchLineEdit->resize(150, WLength::Auto);

    mSearchPushButton = new WPushButton("GO");
    WPushButton *clearButton = new WPushButton("Clear");
    WPushButton *refreshButton = new WPushButton("Refresh");

    userBox->addWidget(new WText("Search:"), 0, 2, AlignRight | AlignMiddle);
    userBox->addWidget(mSearchLineEdit, 0, 3, AlignLeft| AlignMiddle);
    userBox->addWidget(mSearchPushButton, 0, 4, AlignLeft | AlignMiddle);
    userBox->addWidget(clearButton, 0, 5, AlignLeft | AlignMiddle);
    userBox->addWidget(refreshButton, 0, 6, AlignRight | AlignMiddle);
    userBox->setColumnStretch(2, 1);
    userBox->setColumnStretch(6, 1);
    userBox->setColumnStretch(7, 3);

    mPipelineArgTable = new PipelineArgTable();
    mPipelineArgTable->resize(WLength::Auto, 150);
    mPipelineArgTable->setMinimumSize(WLength::Auto,
                                      WLength(150, WLength::Pixel));
    mPipelineArgTable->setMaximumSize(WLength::Auto,
                                      WLength(150, WLength::Pixel));

    mJobStatus = new JobStatus();
    WHBoxLayout *bottomLayout = new WHBoxLayout();
    bottomLayout->addWidget(mPipelineArgTable);
    bottomLayout->addWidget(mJobStatus);



    WGridLayout *browserLayout = new WGridLayout();
    browserLayout->addLayout(userBox, 0, 0);
    browserLayout->addWidget(mResultsTable, 1, 0);
    browserLayout->addLayout(bottomLayout, 2, 0);
    browserLayout->setRowStretch(0, -1);
    browserLayout->setRowStretch(1, 1);
    browserLayout->setRowStretch(2, -1);
    browserContainer->setLayout(browserLayout);


    mBackButton = new WPushButton("<- Back");

    WTabWidget *tabWidget = new WTabWidget();
    tabWidget->setStyleClass("toptabdiv");
    mMonitorLogTab = new MonitorLogTab(mriBrowser);
    mMonitorResultsTab = new MonitorResultsTab(mriBrowser);
    tabWidget->addTab(mMonitorResultsTab, "Results");
    tabWidget->addTab(mMonitorLogTab, "Logs");

    WGridLayout *resultsLayout = new WGridLayout();
    resultsLayout->addWidget(mBackButton, 0, 0, AlignLeft | AlignMiddle);
    resultsLayout->addWidget(tabWidget, 1, 0);
    resultsLayout->setRowStretch(0, -1);
    resultsLayout->setRowStretch(1, 1);
    resultsContainer->setLayout(resultsLayout);

    mStackedWidget = new WStackedWidget();
    mStackedWidget->addWidget(browserContainer);
    mStackedWidget->addWidget(resultsContainer);

    WGridLayout *layout = new WGridLayout();
    layout->addWidget(mStackedWidget, 0, 0);
    layout->setRowStretch(0, -1);
    setLayout(layout);

    mUserComboBox->activated().connect(SLOT(this, ResultsPage::userChanged));
    mSearchPushButton->clicked().connect(SLOT(this, ResultsPage::searchPushed));
    clearButton->clicked().connect(SLOT(this, ResultsPage::clearPushed));
    mResultsTable->resultSelected().connect(SLOT(this, ResultsPage::resultSelected));
    mResultsTable->resultClicked().connect(SLOT(this, ResultsPage::resultClicked));
    mBackButton->clicked().connect(SLOT(this, ResultsPage::backPushed));
    refreshButton->clicked().connect(SLOT(this, ResultsPage::refreshClicked));

    // All items in the tabbed widget need to be resized to 100% to
    // fill the contents.  This trick came from the Wt WTabWidget
    // documentation and took me a good half a day to figure out.
    mMonitorLogTab->resize(WLength(100, WLength::Percentage),
                           WLength(100, WLength::Percentage));
    mMonitorResultsTab->resize(WLength(100, WLength::Percentage),
                               WLength(100, WLength::Percentage));
}