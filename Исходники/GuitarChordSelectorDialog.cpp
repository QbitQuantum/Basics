void
GuitarChordSelectorDialog::slotNewFingering()
{
    Guitar::Chord newChord;
    newChord.setRoot(m_chord.getRoot());
    newChord.setExt(m_chord.getExt());
    
    GuitarChordEditorDialog* chordEditorDialog = new GuitarChordEditorDialog(newChord, m_chordMap, this);
    //QListWidgetItem *tmpItem = 0; (unused)
    QList<QListWidgetItem*> tmpItemList;
    
    if (chordEditorDialog->exec() == QDialog::Accepted) {
        m_chordMap.insert(newChord);
        // populate lists
        //
        tmpItemList = m_rootNotesList->findItems(newChord.getRoot(), Qt::MatchExactly);
        if (tmpItemList.isEmpty() ) {
            m_rootNotesList->addItem(newChord.getRoot());
            m_rootNotesList->sortItems(Qt::AscendingOrder );
        }
        
        tmpItemList = m_rootNotesList->findItems(newChord.getExt(), Qt::MatchExactly);
        if (tmpItemList.isEmpty() ) {
            m_chordExtList->addItem(newChord.getExt());
            m_chordExtList->sortItems(Qt::AscendingOrder );
        }
    }    

    delete chordEditorDialog;
    
    refresh();
}