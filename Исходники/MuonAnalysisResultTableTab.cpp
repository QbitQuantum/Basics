/**
* Populates the items (fitted workspaces) into their table.
*
* @param fittedWsList :: a workspace list containing ONLY the workspaces that have parameter
*                        tables associated with it.
*/
void MuonAnalysisResultTableTab::populateFittings(const QStringList& fittedWsList)
{
  // Add number of rows  for the amount of fittings.
  m_uiForm.fittingResultsTable->setRowCount(fittedWsList.size());

  // Add check boxes for the include column on fitting table, and make text uneditable.
  for (int i = 0; i < m_uiForm.fittingResultsTable->rowCount(); i++)
  {
    m_uiForm.fittingResultsTable->setCellWidget(i,1, new QCheckBox);
    
    if( auto textItem = m_uiForm.fittingResultsTable->item(i, 0) )
    {
      textItem->setFlags(textItem->flags() & (~Qt::ItemIsEditable));
    }
  }

  // Get colors, 0=Black, 1=Red, 2=Green, 3=Blue, 4=Orange, 5=Purple. (If there are more than this then use black as default.)
  QMap<int, int> colors = getWorkspaceColors(fittedWsList);
  for (int row = 0; row < m_uiForm.fittingResultsTable->rowCount(); row++)
  {
    // Fill values and delete previous old ones.
    if (row < fittedWsList.size())
    {
      QTableWidgetItem *item = new QTableWidgetItem(fittedWsList[row]);
      int color(colors.find(row).data());
      switch (color)
      {
        case(1):
        item->setTextColor("red");
        break;
        case(2):
        item->setTextColor("green");
        break;
        case(3):
        item->setTextColor("blue");
        break;
        case(4):
        item->setTextColor("orange");
        break;
        case(5):
        item->setTextColor("purple");
        break;
        default:
        item->setTextColor("black");
      }
      m_uiForm.fittingResultsTable->setItem(row, 0, item);
    }
    else
      m_uiForm.fittingResultsTable->setItem(row,0, NULL);
  }
}