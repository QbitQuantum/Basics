void BookmarkWidget::setup()
{
    regExp.setPatternSyntax(QRegExp::FixedString);
    regExp.setCaseSensitivity(Qt::CaseInsensitive);

    QLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    searchField = new Utils::FancyLineEdit(this);
    searchField->setFiltering(true);
    setFocusProxy(searchField);

    Utils::StyledBar *toolbar = new Utils::StyledBar(this);
    toolbar->setSingleRow(false);
    QLayout *tbLayout = new QHBoxLayout();
    tbLayout->setMargin(4);
    tbLayout->addWidget(searchField);
    toolbar->setLayout(tbLayout);

    vlayout->addWidget(toolbar);

    searchField->installEventFilter(this);
    connect(searchField, &Utils::FancyLineEdit::textChanged,
            this, &BookmarkWidget::filterChanged);

    treeView = new TreeView(this);
    vlayout->addWidget(treeView);

    filterBookmarkModel = new QSortFilterProxyModel(this);
    treeView->setModel(filterBookmarkModel);

    treeView->setDragEnabled(true);
    treeView->setAcceptDrops(true);
    treeView->setAutoExpandDelay(1000);
    treeView->setDropIndicatorShown(true);
    treeView->viewport()->installEventFilter(this);
    treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(treeView, &TreeView::expanded, this, &BookmarkWidget::expand);
    connect(treeView, &TreeView::collapsed, this, &BookmarkWidget::expand);
    connect(treeView, &TreeView::activated, this, &BookmarkWidget::activated);
    connect(treeView, &TreeView::customContextMenuRequested,
            this, &BookmarkWidget::customContextMenuRequested);

    filterBookmarkModel->setFilterKeyColumn(0);
    filterBookmarkModel->setDynamicSortFilter(true);
    filterBookmarkModel->setSourceModel(bookmarkManager->treeBookmarkModel());

    expandItems();
}