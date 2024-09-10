void ezQtDataDirsDlg::FillList()
{
  if (m_Config.m_DataDirs.IsEmpty())
    m_iSelection = -1;

  if (m_iSelection != -1)
    m_iSelection = ezMath::Clamp<ezInt32>(m_iSelection, 0, m_Config.m_DataDirs.GetCount() - 1);

  ListDataDirs->blockSignals(true);

  ListDataDirs->clear();

  for (auto dd : m_Config.m_DataDirs)
  {
    QListWidgetItem* pItem = new QListWidgetItem(ListDataDirs);
    pItem->setFlags(Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable /*| Qt::ItemFlag::ItemIsUserCheckable*/);

    QString sPath = QString::fromUtf8(dd.m_sDataDirSpecialPath.GetData());

    pItem->setText(sPath);
    ListDataDirs->addItem(pItem);

    if (dd.m_bHardCodedDependency)
    {
      QColor col;
      col.setNamedColor("Orange");
      pItem->setTextColor(col);
      pItem->setToolTip("This data directory is a hard dependency and cannot be removed.");
      pItem->setData(Qt::UserRole + 1, false); // can remove ?
    }
    else
    {
      pItem->setData(Qt::UserRole + 1, true); // can remove ?
    }
  }

  ListDataDirs->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

  if (m_iSelection == -1)
    ListDataDirs->clearSelection();
  else
    ListDataDirs->setItemSelected(ListDataDirs->item(m_iSelection), true);

  ListDataDirs->blockSignals(false);

  on_ListDataDirs_itemSelectionChanged();
}