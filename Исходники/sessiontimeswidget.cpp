QTableWidgetItem* SessionTimesWidget::setItem(int row, int col, QString text, Qt::ItemFlags flags, int align,
        QColor textColor, QBrush background)
{
    if (ui->timesTableWidget->rowCount() <= row)
    {
        ui->timesTableWidget->insertRow(row);

//        for (int i = 0; i < ui->timesTableWidget->columnCount();  ++i)
//        {
//            if (i != col)
//                ui->timesTableWidget->setItem(row, i, new QTableWidgetItem());
//        }
    }

    QTableWidgetItem *item = ui->timesTableWidget->item(row, col);
    if (!item)
    {
        item = new QTableWidgetItem(text);
        item->setFlags(flags);
        ui->timesTableWidget->setItem(row, col, item);
    }
    item->setTextAlignment(align);
    item->setBackground(background);
    item->setText(text);
    item->setTextColor(textColor);

    return item;
}