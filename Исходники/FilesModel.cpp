void FilesModel::fixSelection() // deselects cells that are selected but are on a different row from the "current" cell and selects the file name
{
    // it works OK when getFltHandlers() is empty
    QItemSelectionModel* pSelModel (m_pCommonData->m_pFilesG->selectionModel());
    QModelIndexList lstSel (pSelModel->selection().indexes());
    QModelIndex crt (m_pCommonData->m_pFilesG->selectionModel()->currentIndex());
    int nCrtRow (crt.row());
    int nCrtCol (crt.column());

    if (0 == nCrtCol)
    {
        for (QModelIndexList::iterator it = lstSel.begin(), end = lstSel.end(); it != end; ++it)
        {
            if (0 != it->column())
            {
                pSelModel->select(*it, QItemSelectionModel::Deselect);
            }
        }
    }
    else
    {
        set<int> sSelectableColumns;
        sSelectableColumns.insert(0);
        for (int i = 0, n = cSize(m_pCommonData->getCrtNotes()); i < n; ++i) // ttt2 poor performance
        {
            const Note* pNote (m_pCommonData->getCrtNotes()[i]);
            sSelectableColumns.insert(m_pCommonData->findPos(pNote) + 1);
        }

        for (QModelIndexList::iterator it = lstSel.begin(), end = lstSel.end(); it != end; ++it)
        {
            if ((it->row() != nCrtRow && 0 != it->column()) || 0 == sSelectableColumns.count(it->column()))
            {
                pSelModel->select(*it, QItemSelectionModel::Deselect);
            }
        }

        if (nCrtRow >= 0)
        {
            pSelModel->select(index(nCrtRow, 0), QItemSelectionModel::Select);
        }
    }
}