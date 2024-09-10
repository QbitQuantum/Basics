bool CEditUndoStack::GroupUndoInsertChar (CRichEditCtrl* pCtrl, CEditUndo* pUndo) {
  DEFINE_FUNCTION("CEditUndoStack::GroupUndoInsertChar()");
  int SelStart;
  int SelEnd;

  do {
    SelStart = pUndo->GetSelStart();
    SelEnd   = pUndo->GetSelEnd();

    pCtrl->SetSel(pUndo->GetSelStart(), pUndo->GetSelStart()+1);
    pCtrl->ReplaceSel(_T(""));
    pCtrl->SetSel(pUndo->GetSelStart(), pUndo->GetSelEnd());
    DestroyPointer(pUndo);

    pUndo = m_UndoStack.GetAt(m_UndoStack.GetNumElements() - 1);
    if (pUndo == NULL) break;

    if (pUndo->GetAction() != EDITUNDO_INSERTCHAR) break;
    if (!__iscsym(pUndo->GetChar())) break;
    if (abs(pUndo->GetSelStart() - SelStart) >= 2) break;

    m_UndoStack.DeleteElement(m_UndoStack.GetNumElements() - 1, false);
  } while (pUndo != NULL);

  return (true);
}