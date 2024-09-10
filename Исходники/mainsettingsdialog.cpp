void MainSettingsDialog::fillControllerMappingsTable()
{
    /*QList<QVariant> tempvariant = bindingValues(bind);
    QTableWidgetItem* item = new QTableWidgetItem();
    ui->buttonMappingTableWidget->setItem(associatedRow, 0, item);
    item->setText(temptext);
    item->setData(Qt::UserRole, tempvariant);
    */

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    ui->controllerMappingsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    ui->controllerMappingsTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    QHash<QString, QList<QVariant> > tempHash;

    settings->beginGroup("Mappings");

    QStringList mappings = settings->allKeys();
    QStringListIterator iter(mappings);
    while (iter.hasNext())
    {
        QString tempkey = iter.next();
        QString tempGUID;

        if (tempkey.contains("Disable"))
        {
            bool disableGameController = settings->value(tempkey, false).toBool();
            tempGUID = tempkey.remove("Disable");
            insertTempControllerMapping(tempHash, tempGUID);
            if (tempHash.contains(tempGUID))
            {
                QList<QVariant> templist = tempHash.value(tempGUID);
                templist.replace(2, QVariant(disableGameController));
                tempHash.insert(tempGUID, templist); // Overwrite original list
            }
        }
        else
        {
            QString mappingString = settings->value(tempkey, QString()).toString();
            if (!mappingString.isEmpty())
            {
                tempGUID = tempkey;
                insertTempControllerMapping(tempHash, tempGUID);
                if (tempHash.contains(tempGUID))
                {
                    QList<QVariant> templist = tempHash.value(tempGUID);
                    templist.replace(1, mappingString);
                    tempHash.insert(tempGUID, templist); // Overwrite original list
                }
            }
        }
    }

    settings->endGroup();

    QHashIterator<QString, QList<QVariant> > iter2(tempHash);
    int i = 0;
    while (iter2.hasNext())
    {
        ui->controllerMappingsTableWidget->insertRow(i);

        QList<QVariant> templist = iter2.next().value();
        QTableWidgetItem* item = new QTableWidgetItem(templist.at(0).toString());
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setData(Qt::UserRole, iter2.key());
        item->setToolTip(templist.at(0).toString());
        ui->controllerMappingsTableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem(templist.at(1).toString());
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setData(Qt::UserRole, iter2.key());
        //item->setToolTip(templist.at(1).toString());
        ui->controllerMappingsTableWidget->setItem(i, 1, item);

        bool disableController = templist.at(2).toBool();
        item = new QTableWidgetItem();
        item->setCheckState(disableController ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, iter2.key());
        ui->controllerMappingsTableWidget->setItem(i, 2, item);

        i++;
    }
}