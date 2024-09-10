void SelectSiteDialog::initializeTable()
{
    model = new QStandardItemModel(importedSites.size(), 1, this);
    QStandardItem *item;

    QStringList verticalHeader;

    int row = 0;
    foreach(QSharedPointer<Site> site, importedSites)
    {
        verticalHeader.append(QString::number(row + 1));

        item = new QStandardItem(site.data()->siteDetails.Csc);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(QVariant(QString::number(site.data()->siteDetails.SwpId)), DataType::SWP_ID);
        item->setCheckable(true);
        item->setTextAlignment(Qt::AlignJustify);
        item->setCheckState(Qt::Unchecked);
        item->setBackground(QColor(Qt::white));
        item->setForeground(QColor(Qt::black));
        model->setItem(row, 0, item);

        row++;
    }