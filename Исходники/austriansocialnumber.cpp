void AustrianSocialNumberEdit::setCursorPosition(int currentLineEditId, int pos)
{
    qWarning() << "setPos" << currentLineEditId << pos;
    if (pos==-1 && currentLineEditId > 0) {
        QLineEdit *l = m_Edits.at(currentLineEditId-1);
        l->setFocus();
        l->setCursorPosition(l->text().size());
    } else if (pos > m_NbChars.at(currentLineEditId)) {
        if (currentLineEditId+1 < m_Edits.count()) {
            QLineEdit *l = m_Edits.at(currentLineEditId+1);
            l->setFocus();
            l->setCursorPosition(pos - m_NbChars.at(currentLineEditId));
        }
    } else {
        QLineEdit *l = m_Edits.at(currentLineEditId);
        l->setFocus();
        l->setCursorPosition(pos);
    }
}