QSharedItemSelectionModel::QSharedItemSelectionModel(QAbstractItemModel *model, QItemSelectionModel *shared, QObject *parent) :
    QItemSelectionModel(model, parent), d(new QSharedItemSelectionModelPrivate(this))
{
    d->shared = shared;
    connect(d->shared, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(sharedSelectionChanged(QItemSelection,QItemSelection)));
}