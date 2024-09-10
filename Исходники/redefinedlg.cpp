void RedefineDlg::displayLine(const QString& info)
{
  this->enableButtonOk(false);
  QString txt;
  txt.setNum(m_typeColumn + 1);
  m_widget->label_actionCol->setText(i18n("Column ") + txt);
  m_widget->label_info->setText(info);
  m_maxCol = m_columnList.count();
  m_widget->tableWidget->setColumnCount(m_maxCol);

  QBrush brush;
  QColor colr;
  colr.setRgb(255, 0, 127, 100);
  brush.setColor(colr);
  brush.setStyle(Qt::SolidPattern);
  int row;
  m_columnTotalWidth = 0;
  m_maxWidth = 0;
  m_widget->tableWidget->setRowCount(2);
  for (int col = 0; col < m_maxCol; col++) {
    row = 1;
    txt = m_columnList[col];
    txt = txt.remove('"');

    QTableWidgetItem *item = new QTableWidgetItem;//  add items to UI
    item->setText(txt);
    m_widget->tableWidget->setItem(row, col, item);  // add items to UI here
    if (m_typeColumn == col) {
      item->setBackground(brush);
    }
    row = 0;
    if (col == m_quantityColumn) {
      QTableWidgetItem *item = new QTableWidgetItem;//        add items to UI
      item->setText(i18n("Quantity"));
      m_widget->tableWidget->setItem(row, col, item);
    } else if (col == m_priceColumn) {
      QTableWidgetItem *item = new QTableWidgetItem;//        add items to UI
      item->setText(i18n("Price"));
      m_widget->tableWidget->setItem(row, col, item);
    } else if (col == m_amountColumn) {
      QTableWidgetItem *item = new QTableWidgetItem;//        add items to UI
      item->setText(i18n("Amount"));
      m_widget->tableWidget->setItem(row, col, item);
    } else if (col == m_typeColumn) {
      QTableWidgetItem *item = new QTableWidgetItem;//        add items to UI
      item->setText(i18n("Type"));
      m_widget->tableWidget->setItem(row, col, item);
    } else if (col == m_detailColumn) {
      QTableWidgetItem *item = new QTableWidgetItem;//        add items to UI
      item->setText(i18n("Detail"));
      m_widget->tableWidget->setItem(row, col, item);
    }
  }
  m_widget->tableWidget->resizeColumnsToContents();
  for (int col = 0; col < m_maxCol; col++) {
    m_columnTotalWidth += m_widget->tableWidget->columnWidth(col);
  }
  if (m_columnTotalWidth > m_maxWidth) {
    m_maxWidth = m_columnTotalWidth;
  }
  updateWindow();
}