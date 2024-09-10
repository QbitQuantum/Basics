  /*! \brief Constructor.
   */
  GitViewApplication(const WEnvironment& env) 
    : WApplication(env)
  {
    useStyleSheet("gitview.css");
    setTitle("Git model example");

    const char *gitRepo = getenv("GITVIEW_REPOSITORY_PATH");

    WGridLayout *grid = new WGridLayout();
    grid->addWidget(new WText("Git repository path:"), 0, 0);
    grid->addWidget(repositoryEdit_ = new WLineEdit(gitRepo ? gitRepo : "")
		    , 0, 1, AlignLeft);
    grid->addWidget(repositoryError_ = new WText(), 0, 2);
    grid->addWidget(new WText("Revision:"), 1, 0);
    grid->addWidget(revisionEdit_ = new WLineEdit("master"), 1, 1, AlignLeft);
    grid->addWidget(revisionError_ = new WText(), 1, 2);

    repositoryEdit_->setTextSize(30);
    revisionEdit_->setTextSize(20);
    repositoryError_->setStyleClass("error-msg");
    revisionError_->setStyleClass("error-msg");

    repositoryEdit_->enterPressed()
      .connect(this, &GitViewApplication::loadGitModel);
    revisionEdit_->enterPressed()
      .connect(this, &GitViewApplication::loadGitModel);

    WPushButton *b = new WPushButton("Load");
    b->clicked().connect(this, &GitViewApplication::loadGitModel);
    grid->addWidget(b, 2, 0, AlignLeft);

    gitView_ = new WTreeView();
    gitView_->resize(300, WLength::Auto);
    gitView_->setSortingEnabled(false);
    gitView_->setModel(gitModel_ = new GitModel(this));
    gitView_->setSelectionMode(SingleSelection);
    gitView_->selectionChanged().connect(this, &GitViewApplication::showFile);

    sourceView_ = new SourceView(DisplayRole, 
				 GitModel::ContentsRole, 
				 GitModel::FilePathRole);
    sourceView_->setStyleClass("source-view");

    if (environment().javaScript()) {
      /*
       * We have JavaScript: We can use layout managers so everything will
       * always fit nicely in the window.
       */
      WVBoxLayout *topLayout = new WVBoxLayout();
      topLayout->addLayout(grid, 0, AlignTop | AlignLeft);

      WHBoxLayout *gitLayout = new WHBoxLayout();
      gitLayout->setLayoutHint("table-layout", "fixed");
      gitLayout->addWidget(gitView_, 0);
      gitLayout->addWidget(sourceView_, 1);
      topLayout->addLayout(gitLayout, 1);

      root()->setLayout(topLayout);
      root()->setStyleClass("maindiv");
    } else {
      /*
       * No JavaScript: let's make the best of the situation using regular
       * CSS-based layout
       */
      root()->setStyleClass("maindiv");
      WContainerWidget *top = new WContainerWidget();
      top->setLayout(grid, AlignTop | AlignLeft);
      root()->addWidget(top);
      root()->addWidget(gitView_);
      gitView_->setFloatSide(Left);
      gitView_->setMargin(6);
      root()->addWidget(sourceView_);
      sourceView_->setMargin(6);
    }
  }