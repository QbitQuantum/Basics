void ResultWidget::fillInTable(int startIdx, QStringList data)
{
    auto safeSetTableText = [&](int _row, int _col, QString _text)
    {
        QTableWidgetItem* tItem = ui->lowerTable->item(_row, _col);
        if(tItem == nullptr)
        {
            tItem =new QTableWidgetItem();
            ui->lowerTable->setItem(_row, _col, tItem);
        }
        tItem->setText(_text);
        tItem->setTextAlignment(Qt::AlignCenter);
        if(_text == "OK")
            tItem->setTextColor(Qt::darkGreen);
        else if(_text == "NG")
            tItem->setTextColor(Qt::red);
    };

    int itemCounter = startIdx;
    for(int i = 2; i <= 6; i++)
    {
      for(int j = 1; j <= 20; j++)
      {
          safeSetTableText(i, j, data[itemCounter]);
          itemCounter++;
      }
    }

//    ui->lowerTable->resizeColumnsToContents();
//    ui->lowerTable->resizeRowsToContents();
}