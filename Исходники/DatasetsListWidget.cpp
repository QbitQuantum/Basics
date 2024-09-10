DatasetsListWidget::DatasetsListWidget(DatasetsController *_ctrl)
: QWidget(), ctrl(_ctrl)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setMargin(0);
    tabs = new DatasetsTabWidget(this);
    l->addWidget(tabs);

    QToolButton *newTabButton = new QToolButton(this);
    tabs->setCornerWidget(newTabButton, Qt::TopRightCorner);
    newTabButton->setCursor(Qt::ArrowCursor);
    newTabButton->setAutoRaise(true);
    newTabButton->setText("+");
    newTabButton->setObjectName("+");
    newTabButton->setToolTip(tr("Add dataset"));
    QIcon addIcon = QIcon(QString(":U2Designer/images/add.png"));
    newTabButton->setIcon(addIcon);
    connect(newTabButton, SIGNAL(clicked()), SLOT(sl_newDataset()));
    connect(tabs, SIGNAL(tabCloseRequested(int)), SLOT(sl_deleteDataset(int)));
    connect(tabs, SIGNAL(si_contextMenu(const QPoint &, int)), SLOT(sl_contextMenu(const QPoint &, int)));
}