void NotesModel::matchSelToMain()
{
    QModelIndexList lSelFiles (m_pCommonData->m_pFilesG->selectionModel()->selection().indexes());

    set<int> sSel;
    for (QModelIndexList::iterator it = lSelFiles.begin(), end = lSelFiles.end(); it != end; ++it)
    {
        int nCol (it->column());
        if (nCol > 0) // skip file name
        {
            sSel.insert(nCol - 1);
        }
    }

    QItemSelectionModel* pNotesSelModel (m_pCommonData->m_pNotesG->selectionModel());
    pNotesSelModel->clearSelection();
    bool bFirstFound (false);
    for (int i = 0, nNoteCnt = cSize(m_pCommonData->getCrtNotes()); i < nNoteCnt; ++i)
    {
        const Note* pNote (m_pCommonData->getCrtNotes()[i]);
        int nPos (m_pCommonData->findPos(pNote));
        if (sSel.count(nPos) > 0)
        {
            if (!bFirstFound)
            {
                bFirstFound = true;
                m_pCommonData->m_pNotesG->setCurrentIndex(index(i, 0));
            }
            pNotesSelModel->select(index(i, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        }
    }
}