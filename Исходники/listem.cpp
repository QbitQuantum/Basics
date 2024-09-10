    void ListEm::setupUI(ListStorage* listStorage,
                         QLogger* logger)
    {
        /**
          * Create the central widget
          * and set it.
          */
        QFrame* cW = new QFrame(this);
        setCentralWidget(cW);

        /**
          * Set the layout to central widget.
          */
        QVBoxLayout* layout = new QVBoxLayout(cW);
        cW->setLayout(layout);
        layout->setMargin(0);
        layout->setSpacing(0);

        /**
          * Let's create the web view which
          * will be used to display our page
          * with which we will be communicating with.
          */
        m_webView = createWebView(listStorage,
                                  logger);
        m_webView->load(QUrl("qrc:///html/list-view.html"));

        /** Add it to layout */
        layout->addWidget(m_webView);

        m_webView->show();
    }