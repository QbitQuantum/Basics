void VolumeListingDialog::updateTableRows() {
    tgtAssert(table_->columnCount() == metaDataKeys_.size() + 1 /*+1 for URL*/, "column count mismatch");

    QString filterAttribute;
    if (comboBoxFilterAttribute_->currentIndex() > 0)
        filterAttribute = comboBoxFilterAttribute_->currentText();

    std::vector<VolumeURL> filteredOriginsNew = getFilteredOrigins(filterTextBox_->text().trimmed(), filterAttribute);
    if (filteredOrigins_ == filteredOriginsNew)
        return;
    else
        filteredOrigins_ = filteredOriginsNew;

    table_->clearContents();
    table_->setRowCount(static_cast<int>(filteredOrigins_.size()));

    // disable sorting during insertion
    table_->setSortingEnabled(false);

    // iterate over filter origins create a row for each
    for (size_t i=0; i<filteredOrigins_.size(); i++) {
        VolumeURL& origin = filteredOrigins_.at(i);
        // fill row cells with meta data entries
        for (int m=0; m<metaDataKeys_.size(); m++) {
            std::string key = metaDataKeys_.at(m).toStdString();
            std::string cellText;
            const MetaDataBase* metaDate = origin.getMetaDataContainer().getMetaData(key);
            if (metaDate)
                cellText = metaDate->toString();

            // set cell content type according to type of meta data item
            QTableWidgetItem* cellItem = new QTableWidgetItem();
            if (dynamic_cast<const IntMetaData*>(metaDate))
                cellItem->setData(Qt::DisplayRole, static_cast<const IntMetaData*>(metaDate)->getValue());
            else if (dynamic_cast<const SizeTMetaData*>(metaDate))
                cellItem->setData(Qt::DisplayRole, static_cast<qulonglong>(static_cast<const SizeTMetaData*>(metaDate)->getValue()));
            else if (dynamic_cast<const FloatMetaData*>(metaDate))
                cellItem->setData(Qt::DisplayRole, static_cast<const FloatMetaData*>(metaDate)->getValue());
            else if (dynamic_cast<const DoubleMetaData*>(metaDate))
                cellItem->setData(Qt::DisplayRole, static_cast<const DoubleMetaData*>(metaDate)->getValue());
            else
                cellItem->setData(Qt::DisplayRole, QString::fromStdString(cellText));

            cellItem->setToolTip(QString::fromStdString(key) + ": " + QString::fromStdString(cellText));
            //cellItem->setTextAlignment(Qt::AlignLeft);
            cellItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            table_->setItem(static_cast<int>(i), m, cellItem);
        }

        // put URL into last cell
        QTableWidgetItem* urlItem = new QTableWidgetItem(QString::fromStdString(origin.getURL()));
        urlItem->setToolTip("URL: " + QString::fromStdString(origin.getURL()));
        //urlItem->setTextAlignment(Qt::AlignLeft);
        urlItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        table_->setItem(static_cast<int>(i), table_->columnCount()-1, urlItem);
    }

    table_->setSortingEnabled(true);

    updateGuiState();
}