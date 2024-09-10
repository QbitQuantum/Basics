FindChests::FindChests(const QList<World::Chest>& chests, QWidget* parent)
    : QDialog(parent), ui(new Ui::FindChests) {
    ui->setupUi(this);

    QHash<QString, QList<int>> roots;

    for (int i = 0; i < chests.length(); i++) {
        for (auto const& item : chests[i].items) {
            if (!roots[item.name].contains(i))
                roots[item.name].append(i);
        }
    }

    QHashIterator<QString, QList<int>> i(roots);
    auto root = model.invisibleRootItem();
    while (i.hasNext()) {
        i.next();
        auto item = new QStandardItem(i.key());
        item->setEditable(false);
        for (int num : i.value()) {
            auto child = new QStandardItem(chests[num].name.isEmpty() ?
                tr("Chest #%1").arg(num) : chests[num].name);
            child->setEditable(false);
            child->setData(QPointF(chests[num].x, chests[num].y), Qt::UserRole);
            item->appendRow(child);
        }
        root->appendRow(item);
    }

    model.sort(0, Qt::AscendingOrder);

    filter = new ItemsFilterProxyModel(this);
    filter->setSourceModel(&model);
    ui->treeView->setModel(filter);

    connect(ui->treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
        this, SLOT(chestSelected(const QModelIndex&, const QModelIndex&)));
}