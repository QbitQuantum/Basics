IpV6AdvancedWidget::IpV6AdvancedWidget(QWidget * parent)
: QWidget(parent), d(new IpV6AdvancedWidget::Private())
{
    d->ui.setupUi(this);
    layout()->setMargin(0);
    d->ui.tableViewAddresses->setModel(&d->model);
    d->ui.tableViewAddresses->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    d->ui.tableViewAddresses->horizontalHeader()->setStretchLastSection(true);

    IpV6Delegate *ipDelegate = new IpV6Delegate(this);
    IntDelegate *prefixDelegate = new IntDelegate (0, 128, this);
    d->ui.tableViewAddresses->setItemDelegateForColumn(0, ipDelegate);
    d->ui.tableViewAddresses->setItemDelegateForColumn(1, prefixDelegate);
    d->ui.tableViewAddresses->setItemDelegateForColumn(2, ipDelegate);

    d->ui.pushButtonAdd->setIcon(KIcon("list-add"));
    d->ui.pushButtonRemove->setIcon(KIcon("list-remove"));

    connect(d->ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(addIPAddress()));
    connect(d->ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(removeIPAddress()));

    connect(d->ui.tableViewAddresses->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this,
            SLOT(selectionChanged(QItemSelection)));

    connect(&d->model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(tableViewItemChanged(QStandardItem*)));
}