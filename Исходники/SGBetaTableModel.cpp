// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QVariant SGBetaTableModel::data(const QModelIndex& index, qint32 role) const
{

  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::SizeHintRole)
  {
    QStyleOptionComboBox comboBox;

    switch(index.column())
    {
      case BinNumber:
      {
        comboBox.currentText = QString("101");
        const QString header = headerData(BinNumber, Qt::Horizontal, Qt::DisplayRole).toString();
        if (header.length() > comboBox.currentText.length()) { comboBox.currentText = header; }
        break;
      }
      case Alpha:
      {
        comboBox.currentText = QString("10001");
        const QString header = headerData(BinNumber, Qt::Horizontal, Qt::DisplayRole).toString();
        if (header.length() > comboBox.currentText.length()) { comboBox.currentText = header; }
        break;
      }
      case Beta:
      {
        comboBox.currentText = QString("10001");
        const QString header = headerData(BinNumber, Qt::Horizontal, Qt::DisplayRole).toString();
        if (header.length() > comboBox.currentText.length()) { comboBox.currentText = header; }
        break;
      }
      case LineColor:
      {
        comboBox.currentText = QString("Dark Blue     ");
        const QString header = headerData(BinNumber, Qt::Horizontal, Qt::DisplayRole).toString();
        if (header.length() > comboBox.currentText.length())
        {
          comboBox.currentText = header;
        }
        break;
      }
      default:
        Q_ASSERT(false);
    }
    QFontMetrics fontMetrics(data(index, Qt::FontRole) .value<QFont > ());
    comboBox.fontMetrics = fontMetrics;
    QSize size(fontMetrics.width(comboBox.currentText), fontMetrics.height());
    return dream3dApp->style()->sizeFromContents(QStyle::CT_ComboBox, &comboBox, size);
  }
  else if (role == Qt::TextAlignmentRole)
  {
    return int(Qt::AlignRight | Qt::AlignVCenter);
  }
  else if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    int col = index.column();
    if (col == BinNumber)
    {
      return QVariant(m_BinNumbers[index.row()]);
    }
    else if (col == Alpha)
    {
      return QVariant(m_Alpha[index.row()]);
    }
    else if (col == Beta)
    {
      return QVariant(m_Beta[index.row()]);
    }
    else if (col == LineColor)
    {
      return QVariant(m_Colors[index.row()]);
    }
  }

  return QVariant();
}