void ListingTracePane::updateListingTrace()
{
    // tableWidget depends on whether we are in the OS or a program
    QTableWidget *tableWidget;
    if (Sim::trapped) {
        tableWidget = ui->listingPepOsTraceTableWidget;
        ui->listingPepOsTraceTableWidget->show();
        ui->listingTraceTableWidget->hide();
    }
    else {
        tableWidget = ui->listingTraceTableWidget;
        ui->listingPepOsTraceTableWidget->hide();
        ui->listingTraceTableWidget->show();
    }

    for (int i = highlightedItemList.size() - 1; i >= 0; i--) {
        highlightedItemList.at(i)->setBackgroundColor(Qt::white);
        highlightedItemList.at(i)->setTextColor(Qt::black);
        highlightedItemList.removeLast();
    }
    if (Pep::memAddrssToAssemblerListing->contains(Sim::programCounter)) {
        QTableWidgetItem *highlightedItem = tableWidget->item(Pep::memAddrssToAssemblerListing->value(Sim::programCounter), 1);
        highlightedItem->setBackgroundColor(QColor(56, 117, 215));
        highlightedItem->setTextColor(Qt::white);
        highlightedItemList.append(highlightedItem);

        tableWidget->scrollToItem(highlightedItem);
    }
    tableWidget->horizontalScrollBar()->setValue(tableWidget->horizontalScrollBar()->minimum());
}